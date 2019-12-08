#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 10;
int L, R, pri[N], check[N];
void sieve() {
	memset(check, 0, sizeof check);
	for (int i = 2; i < N; ++i) {
		if (!check[i]) {
			pri[++*pri] = i;
		}
		for (int j = 1; j <= *pri; ++j) {
			if (1ll * i * pri[j] >= N) break;
			check[i * pri[j]] = 1;
			if (i % pri[j] == 0) break;
		}
	}
}

bool prime(int x) {
	if (x < N) return !check[x];
	for (int i = 2; 1ll * i * i <= x; ++i) {
		if (x % i == 0)
			return false;
	}
	return true;
}

bool ok(int l, int r) {
	int tot = r - l + 1;
	int p = 0;
	for (int i = l; i <= r; ++i) {
		if (prime(i)) {
			++p;
		}
	}
	return p * 3 < tot;
}

int main() {
	sieve();
	int _T; scanf("%d", &_T);
	while (_T--) {
		scanf("%d%d", &L, &R);
		if (R - L + 1 > 40) {
			puts("Yes");
		} else {
			puts(ok(L, R) ? "Yes" : "No");
		}
	}
	return 0;
}
