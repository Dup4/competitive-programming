#include <bits/stdc++.h>
using namespace std;
using db = double;
int main() {
	int n, op, r, x, y; cin >> n;
	db res = 0;
	for (int i = 1; i <= n; ++i) {
		cin >> op;
		switch (op) {
			case 1 :
				cin >> r;
				res += 3 * r * r;
				break;
			case 2 :
				cin >> x >> y;
				res += x * y * 1.0 / 2;
				break;
			case 3 :
				cin >> x >> y;
				res += x * y;	
				break;
		}
	}
	printf("%.1f\n", res);
	return 0;
}
