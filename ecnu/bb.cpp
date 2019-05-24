#include <bits/stdc++.h>
using namespace std;

#define ll long long
ll qmod(ll base, ll n) {
	ll res = 1;
	while (n) {
		if (n & 1) {
			res = res * base;
		}
		base = base * base;
		n >>= 1;
	}
	return res;
}

int main() {
	int tot = 0;
	for (int a = 1; a <= 10; ++a) {
		for (int b = 1; b <= 10; ++b) {
			for (int c = 1; c <= 10; ++c) {
				for (int d = 1; d <= 10; ++d) {
					if (a != c && qmod(a, b) == qmod(c, d)) {
						printf("%d %d %d %d\n", a, b, c, d);
					}
					if (qmod(a, b) == qmod(c, d)) {
						++tot;
					}
				}
			}
		}
	}
	cout << tot << endl;
	return 0;
}
