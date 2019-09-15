#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int mod = 1e9 + 7;
const int N = 3e3 + 10;
int fac[N], inv[N]; 
int cnt[20], f[20], g[20], ans, n, x, y, s, k; 
ll qpow(ll base, ll n) {
	ll res = 1;
	while (n) {
		if (n & 1) res = res * base % mod;
		base = base * base % mod;
		n >>= 1;
	}
	return res;
}

int exp(int a, int b) {
	int q = 1;
	while (b--) q *= a;
	return q;
}

void dfs(int t, int p) {
	if (t > y) {
		if (k - s == x) {
			ll sum = fac[n]; sum = sum * inv[x] % mod; 
			for (int i = 1; i <= y; ++i) g[i] = f[i];
			sort(g + 1, g + 1 + y);
			int num = 0;
			for (int i = 1; i <= y; ++i) {
				if (i == 1 || g[i] != g[i - 1]) {
					sum = sum * inv[num] % mod; 
					num = 1;
				} else ++num;
			}
			sum = sum * inv[num] % mod;
			ans = (ans + sum) % mod;
		//	printf("\n");
		}
		return;
	}
	for (int i = p; k * exp(i, y - t + 1) - s - i * (y - t + 1) <= x ; ++i) {
		f[t] = i; k *= i; s += i;
		dfs(t + 1, i);
		k /= i; s -= i;
	}
}

int main() {
	fac[0] = 1;
	for (int i = 1; i < N; ++i) fac[i] = 1ll * fac[i - 1] * i % mod;
	inv[N - 1] = qpow(fac[N - 1], mod - 2);
	for (int i = N - 1; i >= 1; --i) inv[i - 1] = 1ll * inv[i] * i % mod;
	int T;
	cnt[0] = 1;
	for (int i = 1; i <= 15; ++i) cnt[i] = cnt[i - 1] * 2;
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		ans = 0;
		for (y = 2; cnt[y] - 2 * y <= n - y; ++y) {
			x = n - y; s = 0; k = 1;
			dfs(1, 2);
		}
		printf("%d\n", ans);
	}
	return 0;
}

