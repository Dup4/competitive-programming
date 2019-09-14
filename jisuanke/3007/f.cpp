#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 5e5 + 10;
int n; ll k, sum, a[N], xl, xr;
ll gaol() {
	ll l = 1, r = xl, res = 1;
	while (r - l >= 0) {
		ll mid = (l + r) >> 1;
		ll need = 0;
		for (int i = 1; i <= n; ++i) 
			if (a[i] < mid)
				need += mid - a[i];
		if (need <= k) {
			l = mid + 1;
			res = mid;
		} else {
			r = mid - 1;
		}
	}
	return res;
}

ll gaor() {
	ll l = xr, r = 1e9, res = 1e9;
	while (r - l >= 0) {
		ll mid = (l + r) >> 1;
		ll need = 0;
		for (int i = 1; i <= n; ++i)
			if (a[i] > mid)
				need += a[i] - mid;
		if (need <= k) {
			r = mid - 1;
			res = mid;
		} else {
			l = mid + 1;
		}
	}
	return res;
}

int main() {
	while (scanf("%d%lld", &n, &k) != EOF) {
		sum = 0;
		for (int i = 1; i <= n; ++i) scanf("%lld", a + i), sum += a[i];
		xl = sum / n, xr = (sum + n - 1) / n;
		ll ml = gaol(), mr = gaor();
		printf("%lld\n", mr - ml);
	}
	return 0;
}
