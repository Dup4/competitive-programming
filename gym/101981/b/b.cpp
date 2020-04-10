#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pLI = pair<ll, int>;
#define fi first
#define se second
#define dbg(x...) do { cout << "\033[32;1m" << #x << " -> "; err(x); } while (0) 
void err() { cout << "\033[39;0m" << endl; } 
template <class T, class... Ts> void err(const T& arg, const Ts&... args) { cout << arg << ' '; err(args...); }
const int N = 3e5 + 10;
const ll INF = 2e18;
int n, C, a[N]; ll S[N];

struct Line {
	mutable ll k, m, p;
	mutable int cnt; 
	bool operator < (const Line& o) const { return k < o.k; }
	bool operator < (ll x) const { return p < x; }
};

struct LineContainer : multiset<Line, less<>> {
	ll div(ll a, ll b) { return a / b - ((a ^ b) < 0 && a % b); }
	bool isect(iterator x, iterator y) {
		if (y == end()) { x->p = INF; return false; }
		if (x->k == y->k) x->p = x->m > y->m ? INF : -INF;
		else x->p = div(y->m - x->m, x->k - y->k);
		return x->p >= y->p; 
	}
	void add(ll k, ll m, int cnt) { 
		auto z = insert({k, m, 0, cnt}), y = z++, x = y;
		while (isect(y, z)) z = erase(z);
		if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
		while ((y = x) != begin() && (--x)->p >= y->p)
			isect(x, erase(y));
	}
	pLI query(ll x) {
		if (empty()) return pLI(INF, n + 1);
		auto it = lower_bound(x);
		assert(it != end());
		return pLI(-(*it).k * x - (*it).m, it->cnt); 
	} 
}lc[2];

//0 前i个位置的最值
//1 前i个位置，并且第i个位置是集结点的最值

namespace WQS {
	pLI check(ll k) {
		lc[0].clear();
		lc[1].clear();
		lc[0].add(0, 0, 0);
		for (int i = 1; i <= n; ++i) {
			//第i个位置是集结点的最值
			pLI it;
			it = lc[0].query(a[i]);
			ll now = it.fi + 1ll * i * a[i] - S[i] + k;
			lc[1].add(-(-a[i]), -(now - S[i] + 1ll * i * a[i]), it.se + 1);
			//前i个位置的最值
			it = lc[1].query(i);
			now = it.fi + S[i];
			lc[0].add(-(-i), -(now + S[i]), it.se);
		//	if (i == n) dbg(it.se);
			if (i == n) return pLI(now, it.se);
		}
	}
	void gao() {
		ll l = 0, r = S[n] + 1, pos = 0;
		while (r - l >= 0) {
			ll mid = (l + r) >> 1;
			//dbg(l, mid, r);
			if (check(mid).se <= C) {
				pos = mid;
				r = mid - 1;
			} else {
				l = mid + 1;
			}
		}
	//	dbg(pos);
		printf("%lld\n", check(pos).fi - pos * C);
	}
}

int main() {
	while (scanf("%d%d", &n, &C) != EOF) {
		S[0] = 0;
		for (int i = 1; i <= n; ++i) scanf("%d", a + i), S[i] = S[i - 1] + a[i];
		WQS::gao();	
	}
	return 0;
}
