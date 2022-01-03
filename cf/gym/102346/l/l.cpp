#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll C(int n, int m) {
	ll res = 1;
	for (int i = n; i > n - m; --i) res = res * i;
	for (int i = 1; i <= m; ++i) res = res / i;
	return res;
}

int main() {
	for (int i = 1; i <= 20; ++i) {
		int cnt = 0;
		for (int j = 0; j <= i; ++j) {
			cnt += C(i, j) % 2;
		}
		printf("%d %d\n", i, cnt);
	}
	return 0;
}
