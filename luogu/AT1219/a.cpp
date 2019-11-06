#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 2e5 + 10;
int n, q, a[N];

struct Hash {
	int a[N], tot;
	void init() { tot = 0; }
	void add(int x) { a[++tot] = x; }
	void gao() { sort(a + 1, a + 1 + tot); tot = unique(a + 1, a + 1 + tot) - a - 1; }
	int get(int x) { return lower_bound(a + 1, a + 1 + tot, x) - a; }
}hs;

namespace Mo {
	int S, bl, ce, L[N], R[N], blo[N], cnt[N], cnt_bf[N];
	ll ans[N], res; 
	struct E {
		int l, r, id;
		bool operator < (const E &other) const {
			if (blo[l] == blo[other.l]) {
				return r < other.r;
			}
			return l < other.l;
		}
	}e[N];
	void init() {
		memset(cnt_bf, 0, sizeof cnt_bf);
		ce = 0;
		S = sqrt(n); bl = (n + S - 1) / S;
	   	for (int i = 1; i <= bl; ++i) {
			L[i] = R[i - 1] + 1;
			R[i] = min(L[i] + S - 1, n);
		}	
		for (int i = 1; i <= n; ++i) {
			blo[i] = (i - 1) / S + 1;
		}
	}
	void addquery(int l, int r, int id) {
		e[++ce] = {l, r, id};
	}
	ll bf(int l, int r) {
		ll res = 0;
		for (int i = l; i <= r; ++i) {
			++cnt_bf[a[i]];
			res = max(res, 1ll * hs.a[a[i]] * cnt_bf[a[i]]);
		}
		for (int i = l; i <= r; ++i) {
			--cnt_bf[a[i]]; 
		}
		return res;
	}
	void add(int x) {
		++cnt[a[x]];
		res = max(res, 1ll * hs.a[a[x]] * cnt[a[x]]);
	}
	void gao() {
		sort(e + 1, e + 1 + q);
		for (int i = 1, lp = 1, l = 0, r = 0; i <= bl; ++i) {
			memset(cnt, 0, sizeof cnt);
			r = R[i];
			res = 0;
			while (blo[e[lp].l] == i) {
				l = R[i] + 1;
				if (e[lp].r - e[lp].l <= S) {
					ans[e[lp].id] = bf(e[lp].l, e[lp].r);
					++lp;
					continue; 
				}
				while (e[lp].r > r) add(++r);
				ll now = res;
				while (l > e[lp].l) add(--l);
				ans[e[lp].id] = res;
				res = now;
				while (l <= R[i]) --cnt[a[l++]];
				++lp; 
			}
		}
		for (int i = 1; i <= ce; ++i) {
			printf("%lld\n", ans[i]);
		}
	}
};

int main() {
	while (scanf("%d%d", &n, &q) != EOF) {
		hs.init(); Mo::init();
		for (int i = 1; i <= n; ++i) {
			scanf("%d", a + i);
			hs.add(a[i]);
		}	
		hs.gao();
		for (int i = 1; i <= n; ++i) a[i] = hs.get(a[i]);
		for (int i = 1, l, r; i <= q; ++i) {
			scanf("%d%d", &l, &r);
			Mo::addquery(l, r, i);
		}
		Mo::gao();
	}		
	return 0;
}
