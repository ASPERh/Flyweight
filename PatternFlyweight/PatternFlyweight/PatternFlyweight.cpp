#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

class CircleFlyweight {
private:
    string color;
    int radius;

public:
    CircleFlyweight(const string& color, int radius) : color(color), radius(radius) {}

    const string& getColor() const {
        return color;
    }

    int getRadius() const {
        return radius;
    }

    void draw(int x, int y) const {
        cout << "Рисуем круг с цветом: " << color << ", радиусом: " << radius
            << ", на позиции (" << x << ", " << y << ")\n";
    }
};

class CircleFactory {
private:
    unordered_map<string, CircleFlyweight*> circles;

public:
    ~CircleFactory() {
        for (auto& pair : circles) {
            delete pair.second;
        }
    }

    CircleFlyweight* getCircle(const string& color, int radius) {
        string key = color + to_string(radius);
        if (circles.find(key) == circles.end()) {
            circles[key] = new CircleFlyweight(color, radius);
        }
        return circles[key];
    }
};

class Circle {
private:
    CircleFlyweight* flyweight;
    int x;
    int y;

public:
    Circle(CircleFlyweight* flyweight, int x, int y) : flyweight(flyweight), x(x), y(y) {}

    void draw() const {
        flyweight->draw(x, y);
    }
};

int main() {
    setlocale(LC_ALL, "Russian");
    CircleFactory circleFactory;

    vector<Circle> circles;
    circles.push_back(Circle(circleFactory.getCircle("Красный", 5), 10, 20));
    circles.push_back(Circle(circleFactory.getCircle("Синий", 10), 30, 40));
    circles.push_back(Circle(circleFactory.getCircle("Красный", 5), 50, 60));
    circles.push_back(Circle(circleFactory.getCircle("Зеленый", 15), 70, 80));
    circles.push_back(Circle(circleFactory.getCircle("Синий", 10), 90, 100));

    for (const auto& circle : circles) {
        circle.draw();
    }

    return 0;
}