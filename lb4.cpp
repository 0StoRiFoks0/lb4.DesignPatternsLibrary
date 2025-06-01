#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

// FLYWEIGHT
class Shape {
public:
    virtual void draw(int x, int y) = 0;
    virtual ~Shape() = default;
};

class Circle : public Shape {
private:
    string color;  // внутрішній стан
public:
    Circle(string clr) : color(clr) {}

    void draw(int x, int y) override {
        cout << "Circle color: " << color << ", at (" << x << ", " << y << ")\n";
    }
};

class ShapeFactory {
private:
    map<string, Shape*> shapes;
public:
    Shape* getCircle(const string& color) {
        if (shapes.find(color) == shapes.end()) {
            shapes[color] = new Circle(color);
        }
        return shapes[color];
    }

    ~ShapeFactory() {
        for (auto& pair : shapes)
            delete pair.second;
    }
};

// ADAPTER 
class OldPrinter {
public:
    void oldPrint() {
        cout << "Old printer is printing...\n";
    }
};

class IPrinter {
public:
    virtual void print() = 0;
    virtual ~IPrinter() = default;
};

class PrinterAdapter : public IPrinter {
private:
    OldPrinter* oldPrinter;
public:
    PrinterAdapter(OldPrinter* op) : oldPrinter(op) {}

    void print() override {
        oldPrinter->oldPrint();
    }
};

// BRIDGE
class DrawingAPI {
public:
    virtual void drawCircle(double x, double y, double radius) = 0;
    virtual ~DrawingAPI() = default;
};

class DrawingAPI1 : public DrawingAPI {
public:
    void drawCircle(double x, double y, double radius) override {
        cout << "API1.circle at (" << x << ", " << y << ") radius: " << radius << "\n";
    }
};

class DrawingAPI2 : public DrawingAPI {
public:
    void drawCircle(double x, double y, double radius) override {
        cout << "API2.circle at (" << x << ", " << y << ") radius: " << radius << "\n";
    }
};

class ShapeBridge {
protected:
    DrawingAPI* drawingAPI;
public:
    ShapeBridge(DrawingAPI* api) : drawingAPI(api) {}
    virtual void draw() = 0;
    virtual ~ShapeBridge() = default;
};

class CircleShape : public ShapeBridge {
private:
    double x, y, radius;
public:
    CircleShape(double x, double y, double r, DrawingAPI* api)
        : ShapeBridge(api), x(x), y(y), radius(r) {}

    void draw() override {
        drawingAPI->drawCircle(x, y, radius);
    }
};

// FACADE
class CPU {
public:
    void start() { cout << "CPU started\n"; }
};

class Memory {
public:
    void load() { cout << "Memory loaded\n"; }
};

class HardDrive {
public:
    void read() { cout << "Hard Drive read\n"; }
};

class ComputerFacade {
private:
    CPU cpu;
    Memory memory;
    HardDrive hardDrive;
public:
    void startComputer() {
        cpu.start();
        memory.load();
        hardDrive.read();
    }
};

// MAIN 
int main() {
    cout << "==== FLYWEIGHT ====\n";
    ShapeFactory shapeFactory;
    Shape* redCircle = shapeFactory.getCircle("Red");
    redCircle->draw(10, 20);
    Shape* anotherRedCircle = shapeFactory.getCircle("Red");
    anotherRedCircle->draw(30, 40);

    cout << "\n==== ADAPTER ====\n";
    OldPrinter* old = new OldPrinter();
    IPrinter* adapter = new PrinterAdapter(old);
    adapter->print();
    delete adapter;
    delete old;

    cout << "\n==== BRIDGE ====\n";
    ShapeBridge* circle1 = new CircleShape(5, 10, 15, new DrawingAPI1());
    ShapeBridge* circle2 = new CircleShape(7, 14, 21, new DrawingAPI2());
    circle1->draw();
    circle2->draw();
    delete circle1;
    delete circle2;

    cout << "\n==== FACADE ====\n";
    ComputerFacade computer;
    computer.startComputer();

    cout << "\nPress any key to exit...\n";
    system("pause");
    return 0;
}
