#include <iostream>
#include <string>
#include <cmath>
using namespace std;
const double PI = 3.14159;

class Shape {
	public :
		Shape() {}
		virtual double getArea() = 0;
		virtual double getPerimeter() = 0;
		virtual void show() = 0;
		virtual string getClassName() = 0;
};
class Circle : public Shape {
	public :
		double radius;
		Circle(double radius) :Shape(), radius(radius) {}
		double getArea() {
			return PI * radius * radius;
		}
		double getPerimeter() {
			return PI * 2 * radius;
		}
		void show() {
			cout << "Radius:" << radius << endl;
		}
		string getClassName() {
			return "Circle";
		}
};
class Rectangle : public Shape {
	public :
		double width, height;
		Rectangle(double width, double height) : Shape(), width(width), height(height) {}
		double getArea() {
			return width * height;
		}
		double getPerimeter() {
			return 2 * width * height;
		}
		void show() {
			cout << "Width:" << width << ", Height:" << height << endl; 
		}
		string getClassName() {
			return "Rectangle";
		}
};
class Triangle : public Shape {
	public :
		double side[3];
		Triangle(double side1, double side2, double side3) : Shape() {
			side[0] = side1;
			side[1] = side2;
			side[2] = side3;
		}
		double getArea() {
			double p = getPerimeter() * 1.0 / 2;
			return sqrt(p * (p - side[0]) * (p - side[1]) * (p - side[2]));
		}
		double getPerimeter() {
			return side[0] + side[1] + side[2];
		}
		void show() {
			cout << "Side:" << side[0] << ", " << side[1] << ", " << side[2] << endl;
		}
		string getClassName() {
			return "Triangle";
		}
};


int main() {
    double radius, width, height, side1, side2, side3;
    cin >> radius;
    Circle circle(radius);
    cin >> width >> height;
    Rectangle rectangle(width, height);
    cin >> side1 >> side2 >> side3;
    Triangle triangle(side1, side2, side3);
    cout << circle.getClassName() << ":" << endl;
    circle.show();
    cout << "Area:" << circle.getArea();
    cout << ", Perimeter:" << circle.getPerimeter() << endl;
    cout << rectangle.getClassName() << ":" << endl;
    rectangle.show();
    cout << "Area:" << rectangle.getArea();
    cout << ", Perimeter:" << rectangle.getPerimeter() << endl;
    cout << triangle.getClassName() << ":" << endl;
    triangle.show();
    cout << "Area:" << triangle.getArea();
    cout << ", Perimeter:" << triangle.getPerimeter() << endl;
    return 0;
}
