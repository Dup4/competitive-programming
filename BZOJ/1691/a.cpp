#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define pii pair <int, int>
#define fi first
#define se second
const int N = 1e5 + 10;
int n, m; 
pii a[N], b[N];

int main() {
	while (scanf("%d%d", &n, &m) != EOF) {
		for (int i = 1; i <= n; ++i) scanf("%d%d", &a[i].fi, &a[i].se);
		for (int i = 1; i <= m; ++i) scanf("%d%d", &b[i].fi, &b[i].se);
		sort(a + 1, a + 1 + n);
		sort(b + 1, b + 1 + m);
		int pos = 1;
		ll res = 0;
		multiset <ll> se;
		for (int i = 1; i <= m; ++i) {
			while (pos <= n && a[pos].fi <= b[i].fi) {
				se.insert(a[pos].se);
				++pos;
			}
			multiset <ll>::iterator pos = se.upper_bound(b[i].se);
			if (pos != se.begin()) {
				--pos;
				se.erase(pos);
				res += b[i].fi;
			}
		}
		printf("%lld\n", res);
	}
	return 0;
}
