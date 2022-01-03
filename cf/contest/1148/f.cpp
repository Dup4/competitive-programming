#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 300010
int n;
ll a[N], b[N]; 

int main() {
	while (scanf("%d", &n) != EOF) {
		ll sum = 0;
		for (int i = 1; i <= n; ++i) {
			scanf("%lld%lld", a + i, b + i);
			sum += a[i];
		}
		if (sum < 0) {
			for (int i = 1; i <= n; ++i) {
				a[i] = -a[i];
			}
		}
		ll ans = 0;
		for (int i = 61; i >= 0; --i) {
			ll s = 0;
			for (int j = 1; j <= n; ++j) {
				if (b[j] == (1ll << i)) {
					s += a[j];
				}
			}
			if (s > 0) {
				ans |= (1ll << i);
			}
			for (int j = 1; j <= n; ++j) {
				if ((b[j] >> i) & 1) {
					b[j] ^= (1ll << i); 
					if (s > 0) {
						a[j] = -a[j];
					}
				}
			}
		}
		printf("%lld\n", ans); 
	}
	return 0;
}

