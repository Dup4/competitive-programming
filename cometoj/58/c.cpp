#include <bits/stdc++.h>
using namespace std;

#define ll long long 
const ll INF = 1e18;
const int N = 1e5 + 10;
int n, K, a[N], b[N];
ll c[N], d[N];

int main() {
	while (scanf("%d%d", &n, &K) != EOF) {
		for (int i = 1; i <= n; ++i) scanf("%d%d", a + i, b + i);
		ll res = INF;
		for (int i = 2; i <= n; ++i) c[i - 1] = a[i] * b[i - 1];
		--n;
		for (int i = 1; i <= n; ++i) d[i] = d[i - 1] + c[i];
		res = min(d[n], d[n] * K * K);
		ll Min = INF;
		for (int i = 1; i <= n; ++i) {
			res = min(res, d[i - 1] * K * K + c[i] * K + d[n] - d[i]);
			res = min(res, c[i] * K + d[i - 1] * K * K + Min + d[n] - d[i]);
			Min = min(Min, d[i - 1] + c[i] * K - d[i] * K * K);
		}
		printf("%lld\n", res);
	}
	return 0;
}
