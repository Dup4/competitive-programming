#include <bits/stdc++.h>
using namespace std;

int f(int x) {
	int res = 0;
	while (x) {
		res += x % 10;
		x /= 10;
	}
	return res;
}

int g(int x) {
	for (int i = x; ; ++i) {
		if (f(i) % 4 == 0) {
			return i;
		}
	}
}

int main() {
	int a;
	while (cin >> a) {
		cout << g(a) << "\n";
	}
	return 0;
}
