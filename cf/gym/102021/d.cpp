#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 1e6 + 10;
int n;
ll a[N], b[N];

int main() {
	while (scanf("%d", &n) != EOF) {
		for (int i = 1; i <= n; ++i) scanf("%lld", b + i);
		ll l = 0, r = b[1];
		a[2] = b[1];
		for (int i = 3; i <= n + 1; ++i) {
			a[i] = b[i - 1] - a[i - 1];
			if (i & 1) l = max(l, -a[i]);
			else r = min(r, a[i]);
		}
		printf("%lld\n", max(0ll, r - l + 1));
	}
	return 0;
}
