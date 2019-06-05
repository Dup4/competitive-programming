#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 300010
int n, k;
ll a[N], sum[N]; 

int main() {
	while (scanf("%d%d", &n, &k) != EOF) {
		sum[0] = 0;
		for (int i = 1; i <= n; ++i) {
			scanf("%lld", a + i);
			sum[i] = sum[i - 1] + a[i];
		}
		if (k == 1) {
			printf("%lld\n", sum[n]);
		} else if (k == 2) {
			ll res = -1e18;
			for (int i = 1; i < n; ++i) {
				res = max(res, sum[i] + 2ll * (sum[n] - sum[i]));
			}
			printf("%lld\n", res);
		} else {
			ll res = -1e18;
			ll base = 0;
			for (int i = 2; i < k; ++i) {
				base += 1ll * i * a[i]; 
			}
			for (int i = 1; i + k - 2 < n; ++i) {
				ll tmp = sum[i] + base + 1ll * k * (sum[n] - sum[i + k - 2]);
				res = max(res, tmp);
				base -= 2ll * a[i + 1];
				base += 1ll * (k - 1) * a[i + k - 1]; 
				base -= sum[i + k - 2] - sum[i + 1]; 
			}
			printf("%lld\n", res);
		}
	}
	return 0;
}

