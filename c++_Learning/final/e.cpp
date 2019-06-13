#include <iostream>
#include <cmath>
using namespace std;

#include <algorithm>
#define db double
db PI = acos(-1.0);
inline bool isValid(db s1, db s2, db s3) {
	db a[3] = {s1, s2, s3};
	sort(a, a + 3);
	if (a[0] + a[1] <= a[2]) {
		return false;
	}
	return true;
}
db computeArea(db r = 1) {
	return PI * r * r;
}
db computeArea(db width, db height) {
	return width * height;
}
db computeArea(db s1, db s2, db s3) {
	if (!isValid(s1, s2, s3)) {
		return 0;
	}
	db p = (s1 + s2 + s3) * 1.0 / 2;
	return sqrt(p * (p - s1) * (p - s2) * (p - s3));
}

int main() {
    double radius;
    cin >> radius;
    double width, height;
    cin >> width >> height;    
    double side1, side2, side3;
    cin >> side1 >> side2 >> side3;
    cout << computeArea(radius) << endl;
    cout << computeArea(width, height) << endl; 
    cout << computeArea(side1, side2, side3) << endl;
    return 0;
}
