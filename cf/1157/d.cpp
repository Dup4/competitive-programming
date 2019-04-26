#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 100010
int n;
ll k, f[N];

int main() {
	while (scanf("%lld%d", &k, &n) != EOF) {
		ll must = 1ll * n * (n + 1) / 2;
		if (must > k) {
			puts("NO");
		} else {
			k -= must;
			f[0] = 1e9; 
			ll base = 0;
			for (int i = 1; i <= n; ++i) {
				++base;
				if (k >= (n - i + 1)) {
					int need = min(2ll * f[i - 1] - base, k / (n - i + 1));
					base += need;
					k -= 1ll * (n - i + 1) * need;
				}
				f[i] = base;
			}
			if (k > 0) {
				puts("NO");
				continue;
			}
			puts("YES");
			for (int i = 1; i <= n; ++i) {
				printf("%lld%c", f[i], " \n"[i == n]);
			}
		}
	}
	return 0;
}
