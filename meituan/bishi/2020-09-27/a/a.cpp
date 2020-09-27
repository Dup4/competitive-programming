#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pLL = pair<ll, ll>;
#define fi first
#define se second
pLL a[3];
ll x;

int main() {
	scanf("%lld%lld%lld%lld%lld%lld%lld", &a[0].fi, &a[1].fi, &a[2].fi, &x, &a[0].se, &a[1].se, &a[2].se);
	sort(a, a + 3, [&](pLL a, pLL b) {
		return a.se > b.se;		
	});
	ll res = 0;
	for (int i = 0; i < 3; ++i) {
		int col = min(a[i].fi, x);
		x -= col;
		res += a[i].se * col;
	}
	cout << res << endl;
	return 0;
}
