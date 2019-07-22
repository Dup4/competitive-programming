#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 300010
int n, m, k;
ll a[N];
ll f[20]; 

int main() {
	while (scanf("%d%d%d", &n, &m, &k) != EOF) {
		for (int i = 1; i <= n; ++i) scanf("%lld", a + i);
		ll res = 0;
		for (int i = 0; i < m; ++i) f[i] = 0;
	    f[0] = -k; 	
		for (int i = 1; i <= n; ++i) {
			a[i] += a[i - 1]; 
			for (int j = 0; j < m; ++j) {
				if (m - i % m >= m - j) {
					res = max(res, a[i] - f[j] - 1ll * k * (i / m + 1));
				} else {
					res = max(res, a[i] - f[j] - 1ll * k * (i / m + 2));
				}
			}
			f[i % m] = min(f[i % m], a[i] - 1ll * k * (i / m + 1));
		}
		printf("%lld\n", res);
	}
	return 0;
}
