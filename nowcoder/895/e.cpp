#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 200010
#define pli pair <ll, int>
#define fi first
#define se second
int n, m;
ll d[N], h[N];
multiset <pli> se; 
vector < vector <int> > k;

int main() {
	while (scanf("%d%d", &n, &m) != EOF) {
		k.clear();
		k.resize(n + 1);
		for (int i = 1; i <= n; ++i) {
			scanf("%lld", h + i);
		}
		for (int i = 1; i <= m; ++i) {
			scanf("%lld", d + i); 
			d[i + m] = d[i];
			d[i] += d[i - 1];
		}
		for (int i = m + 1; i <= 2 * m; ++i) {
			d[i] += d[i - 1];
		} 
		for (int i = 1, x, tot; i <= n; ++i) {
			scanf("%d", &tot);
			k[i].clear();
			for (int j = 1; j <= tot; ++j) {
				scanf("%d", &x);
				k[i].push_back(x); 
			}
		}
		se.clear();
		ll lazy = 0;
		ll res = 0;
		int now = 0;
		se.insert(pli(h[1], 1));
		while (!se.empty()) {
			ll Min = (*se.begin()).fi;
		   	Min += lazy; 
			ll cnt = Min / d[m]; 
			int pos = lower_bound(d + now, d + 1 + 2 * m, Min % d[m] + d[now]) - d;
			lazy -= cnt * d[m] + d[pos] - d[now]; 
			res += cnt * m + pos - now - 1;
			now = pos % m;
			while (!se.empty()) {
				pli tmp = *se.begin();
				if (tmp.fi + lazy <= 0) {
					pos = tmp.se;
					se.erase(*se.begin());
					for (auto it : k[pos]) {
						se.insert(pli(h[it] - lazy, it));
					}
				} else {
					break;
				}
			}
		}
		printf("%lld\n", res + 1); 
	}
	return 0;
}
