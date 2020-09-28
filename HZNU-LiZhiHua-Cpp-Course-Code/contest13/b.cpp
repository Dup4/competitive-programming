#include <iostream>
using namespace std;

bool ok(int x) {
	return ((x % 4 == 0) && (x % 100)) || (x % 400 == 0);
}
int mon[][13] {
	{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
	{0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
};
class Date {
public :
	int y, m, d;
	Date() {}
	Date(int y, int m, int d) : y(y), m(m), d(d) {}
	int getWeekday() {
		if (y < 2000 || y >= 10000 || m < 1 || m > 12 || d < 1 || d > mon[ok(y)][m]) {
			return -1;
		}
		int tot = d; 
		for (int i = 2000; i < y; ++i) {
			tot += ok(i) ? 366 : 365;
		}
		for (int i = 1; i < m; ++i) {
			tot += mon[ok(y)][i];
		}
		return (5 + tot - 1) % 7 + 1;
	}
};

int main() {
    int year, month, day;
    while(cin >> year >> month >> day) {
        if(year == 0 && month == 0 && day == 0)
	    break;
	Date d(year, month, day);
	cout << d.getWeekday() << endl;
    }
    return 0;
}
