#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N = 1e5 + 10;

int n;
ll k;
ll a[N], b[N];

bool check(ll x) {
	ll cnt = 0, remind = 0;
	for (int i = 1; i <= n; ++i) {
		b[i] = a[i];
		if (b[i] >= x - remind) {
			cnt++;
			b[i] -= x - remind;
			remind = 0;
		}
		cnt += b[i] / x;
		remind = b[i] % x;
		if (cnt >= k) return true;
	}
	return cnt >= k;
}

int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		scanf("%d %lld", &n, &k);
		for (int i = 1; i <= n; ++i) {
			scanf("%lld", a + i);
		}
		ll l = 1, r = 1e17, res = 0;
		while (r - l >= 0) {
			ll mid = (l + r) >> 1;
			if (check(mid)) {
				res = mid;
				l = mid + 1;
			} else {
				r =  mid - 1;
			}
		}
		printf("%lld\n", res * k);
	}	
	return 0;
}
