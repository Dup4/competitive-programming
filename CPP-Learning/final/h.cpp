#include <iostream>
using namespace std;
const double PI = 3.14159;

#define db double
class Circle {
public :
	db r;
	Circle(db r) {
		this->r = r;
	}
	bool operator < (const Circle &other) const {
		return r < other.r;
	}
	bool operator <= (const Circle &other) const {
		return r <= other.r;
	}
	bool operator == (const Circle &other) const {
		return r == other.r;
	}
	bool operator != (const Circle &other) const {
		return r != other.r;
	}
	bool operator > (const Circle &other) const {
		return r > other.r;
	}
	bool operator >= (const Circle &other) const {
		return r >= other.r;
	}
};

int main() {
    double radius1, radius2;
    cin >> radius1 >> radius2;
    Circle c1(radius1);
    Circle c2(radius2);
    cout << boolalpha;
    cout << (c1 < c2) << endl;
    cout << (c1 <= c2) << endl;
    cout << (c1 == c2) << endl;
    cout << (c1 != c2) << endl;
    cout << (c1 > c2) << endl;
    cout << (c1 >= c2) << endl;
    return 0;
}
