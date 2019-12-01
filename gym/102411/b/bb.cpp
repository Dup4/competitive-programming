#include <bits/stdc++.h>

using namespace std;

int main() {
	double Pi = acos(-1.0);
	double k = 2 / 50000;
	double i = 0;
	while (true) {
		++i;
		double j = i;
		while (j > 2 * Pi) j -= 2 * Pi;
		if (j < k) {
			printf("%lf %lf %lf\n", i, j, sin(i));
			break;
		}
	}
	return 0;
}
