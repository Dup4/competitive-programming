#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 1e6 + 10;
int pri[N], check[N], mu[N], Mu[N], tot, n, m;
void init() {
	memset(check, 0, sizeof check);
	tot = 0;
	mu[1] = 1;
	for (int i = 2; i < N; ++i) {
		if (!check[i]) {
			pri[++tot] = i;
			mu[i] = -1;
		}
		for (int j = 1; j <= tot; ++j) {
			if (1ll * i * pri[j] >= N) break;
			check[i * pri[j]] = 1;
			if (i % pri[j] == 0) {
				mu[i * pri[j]] = 0;
				break;
			} else {
				mu[i * pri[j]] = -mu[i];
			}
		}
	}
	memset(Mu, 0, sizeof Mu);
	for (int i = 1; i < N; ++i) {
		for (int j = i; j < N; j += i) {
			Mu[j] += mu[i] * mu[j / i];
		}
	}
}

int main() {
	init();
	int _T; cin >> _T;
	while (_T--) {
		scanf("%d%d", &n, &m);
		if (n > m) swap(n, m);
		ll res = 0;
		for (int T = 1; T <= n; ++T) {
			ll A = 0, B = 0;
			for (int i = 1; i <= n / T; ++i) A += mu[i * T];
			for (int i = 1; i <= m / T; ++i) B += mu[i * T];
			res += A * B * Mu[T];
		}
		printf("%lld\n", res);
	}
	return 0;
}
