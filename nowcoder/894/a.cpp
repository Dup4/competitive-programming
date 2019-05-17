#include <bits/stdc++.h>
using namespace std;

#define db double
db PI = acos(-1.0);

int main() {
	int s;
	while (scanf("%d", &s) != EOF) {
		db a = s * 1.0 / PI;
		printf("%.3f\n", 2.0 * sqrt(a));
	}
	return 0;
}
