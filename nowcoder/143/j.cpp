#include <bits/stdc++.h>
using namespace std;

#define N 1000010
#define ll long long
#define ll long long
ll n, p2, p3;
ll f[N];

ll DFS(int x) {
	if (x <= 0) {
		return 0;
	}
	if (f[x] != -1) {
		return f[x];
	}
	return f[x] = min(p2 + DFS(x - 2), p3 + DFS(x - 3));
}

int main() {
	while (scanf("%lld%lld%lld", &n, &p2, &p3) != EOF) {
		memset(f, -1, sizeof f);
		if (n <= 1000000) {
			printf("%lld\n", DFS(n));
		} else {
			ll res = 1e18;
			ll m;
			for (int i = 0; i < 1000000; ++i) {
				m = n - i;
				res = min(res, p2 * (m / 2) + DFS(i + m % 2));
				res = min(res, p3 * (m / 3) + DFS(i + m % 3));
			}
			printf("%lld\n", res);
		}
	}
	return 0;
}
