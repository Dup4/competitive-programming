#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ll;
ll m;
ll qmod(ll base, ll n) {
	ll res = 1;
	while (n) {
		if (n & 1) res = res * base;
		base = base * base;
		n >>= 1;
	}
	return res;
}

int get(int n) {
	ll sum = 0;
	for (int i = 1; ; ++i) {
		sum += qmod(i, n - 1);
		if (sum == m) return i;
		if (sum > m) return -1;
	}
}

void gao() {
	for (int n = 3; n <= 54; ++n) {
		int s = get(n);
		if (s != -1) {
			printf("%d %d\n", n, s); 
			return;
		} 
	}
	puts("impossible");
}

int main() {
	while (scanf("%lld", &m) != EOF) {
		gao();
	}
	return 0;
}
