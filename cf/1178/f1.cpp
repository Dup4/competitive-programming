#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 510
const ll p = 998244353;
int n, m, a[N];
ll f[N][N]; 

void add(ll &x, ll y) {
	x += y;
	if (x >= p) x -= p;
}

ll dp(int l, int r) {
	if (l > r) return 1;
	if (f[l][r] != -1) return f[l][r];
	if (l == r) return f[l][r] = 1;
	f[l][r] = 0;
//	for (int i = l; i < r; ++i) {
//		add(f[l][r], dp(l, i) * dp(i + 1, r) % p);
//	}
	for (int i = l; i <= r; ++i) {
		add(f[l][r], dp(l, i - 1) * dp(i + 1, r) % p);
	}
	return f[l][r];
}

int main() {
	while (scanf("%d%d", &n, &m) != EOF) {
		memset(f, -1, sizeof f);
		for (int i = 1; i <= n; ++i) scanf("%d", a + i);
		printf("%lld\n", dp(1, n)); 
	}
	return 0;
}
