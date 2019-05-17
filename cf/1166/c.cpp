#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 200010
int n, a[N];

int main() {
	while (scanf("%d", &n) != EOF) {
		for (int i = 1; i <= n; ++i) {
			scanf("%d", a + i);
			if (a[i] < 0) {
				a[i] = -a[i];
			}
		}
		sort(a + 1, a + 1 + n);
		ll res = 0;
		for (int i = 1; i <= n; ++i) {
			ll x = a[i];
			int pos = upper_bound(a + 1, a + 1 + n, 2 * x) - a - 1;
			res += pos - i;
		}
		printf("%lld\n", res);
	}
	return 0;
}
