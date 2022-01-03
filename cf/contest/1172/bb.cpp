#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 200010
const ll p = 998244353;
int n, d[N];
ll fac[N];


int main() {
	fac[0] = 1;
	for (int i = 1; i < N; ++i) {
		fac[i] = fac[i - 1] * i % p;
	}
	while (scanf("%d", &n) != EOF) {
		memset(d, 0, sizeof d);
		ll res = 1;
		for (int i = 1, u, v; i < n; ++i) {
			scanf("%d%d", &u, &v);
			++d[u];
			++d[v];
		}
		for (int i = 1; i <= n; ++i) {
			res = res * fac[d[i]] % p;
		}
		printf("%lld\n", res * n % p);
	}
	return 0;
}
