#include "pch.h"
#include <iostream>
#include <gtest/gtest.h>
#include <cmath>
#include <string>

using namespace std;

class Shape {
public:
    virtual void draw() = 0;
    virtual double getArea() = 0;
    virtual ~Shape() = default;
};

class Circle : public Shape {
    double radius;
public:
    Circle(double r = 1.0) : radius(r) {}
    void draw() override {
        cout << "Drawing Circle\n";
    }
    double getArea() override {
        return 3.1416 * radius * radius;
    }
};



class ShapeFactory {
public:
    static Shape* getShape(const string& shapeType, double a = 1.0, double b = 2.0) {
        if (shapeType == "CIRCLE") return new Circle(a);
        else if (shapeType == "RECTANGLE") return new Rectangle(a, b);
        else if (shapeType == "SQUARE") return new Square(a);
        else return nullptr;
    }
};

// Unit tests for area calculation

TEST(ShapeAreaTest, CircleArea) {
    double radius = 2.0;
    Shape* shape = new Circle(radius);
    EXPECT_NEAR(shape->getArea(), 3.1416 * radius * radius, 1e-5);
    delete shape;
}

TEST(ShapeAreaTest, RectangleArea) {
    double width = 3.0, height = 4.0;
    Shape* shape = new Rectangle(width, height);
    EXPECT_DOUBLE_EQ(shape->getArea(), width * height);
    delete shape;
}

TEST(ShapeAreaTest, SquareArea) {
    double side = 5.0;
    Shape* shape = new Square(side);
    EXPECT_DOUBLE_EQ(shape->getArea(), side * side);
    delete shape;
}

TEST(ShapeFactoryTest, CreateCircle) {
    Shape* shape = ShapeFactory::getShape("CIRCLE", 2.0);
    ASSERT_NE(shape, nullptr);
    shape->draw(); // Prints "Drawing Circle"
    EXPECT_NEAR(shape->getArea(), 3.1416 * 4.0, 1e-5);
    delete shape;
}

TEST(ShapeFactoryTest, CreateRectangle) {
    Shape* shape = ShapeFactory::getShape("RECTANGLE", 3.0, 4.0);
    ASSERT_NE(shape, nullptr);
    shape->draw(); // Prints "Drawing Rectangle"
    EXPECT_DOUBLE_EQ(shape->getArea(), 12.0);
    delete shape;
}

TEST(ShapeFactoryTest, CreateSquare) {
    Shape* shape = ShapeFactory::getShape("SQUARE", 5.0);
    ASSERT_NE(shape, nullptr);
    shape->draw(); // Prints "Drawing Square"
    EXPECT_DOUBLE_EQ(shape->getArea(), 25.0);
    delete shape;
}

TEST(ShapeFactoryTest, InvalidShapeReturnsNull) {
    Shape* shape = ShapeFactory::getShape("TRIANGLE");
    ASSERT_EQ(shape, nullptr);
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
