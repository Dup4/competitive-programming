#include <bits/stdc++.h>
using namespace std;
using pII = pair<int, int>;
using ll = long long;
#define dbg(x...) do { cout << "\033[32;1m" << #x << " -> "; err(x); } while (0) 
void err() { cout << "\033[39;0m" << endl; } 
template <class T, class... Ts> void err(const T& arg, const Ts&... args) { cout << arg << ' '; err(args...); }
#define fi first
#define se second
const int N = 5e5 + 10;
int n, m, q, l[N], r[N], v[N]; ll ans[N];
vector <vector<pII>> query;

struct BIT {
	ll a[N];
	void init() { memset(a, 0, sizeof a); }
	void update(int x, ll v) {
		if (x == 0) return; 
		for (; x < N; x += x & -x)
			a[x] += v;
	}
	ll query(int x) {
		ll res = 0;
		for (; x > 0; x -= x & -x)
			res += a[x];	
		return res; 
	}
	ll query(int l, int r) {
		if (l > r) return 0;
		return query(r) - query(l - 1);
	}
}bit;

struct ODT {
	struct node {
		int l, r, id; 
		mutable ll v;
		node(int l, int r = -1, int id = 0, ll v = 0) : l(l), r(r), id(id), v(v) {}
		bool operator < (const node& other) const {
			return l < other.l; 
		}
	};
	using IT = set<node>::iterator;
	set <node> se; 
	void init() { se.clear(); } 
	IT split(int pos) {
		IT it = se.lower_bound(node(pos));
		if (it != se.end() && it->l == pos) 
			return it;
		--it;
		int l = it->l, r = it->r, id = it->id; ll v = it->v; 
		se.erase(it);
		se.insert(node(l, pos - 1, id, v)); 
		return se.insert(node(pos, r, id, v)).first;
	}
	void assign(int l, int r, int id, ll v) {
		IT itr = split(r + 1);
		IT itl = split(l);
		for (IT it = itl; it != itr; ++it) {
			bit.update(it->id, 1ll * (it->r - it->l + 1) * -it->v); 
		}
		se.erase(itl, itr);
		bit.update(id, 1ll * (r - l + 1) * v);
		se.insert(node(l, r, id, v));  
	}
}odt;


int main() {
	while (scanf("%d%d%d", &n, &m, &q) != EOF) {
		query.clear(); query.resize(n + 1); 
		for (int i = 1; i <= n; ++i) {
			scanf("%d%d%d", l + i, r + i, v + i);
		}
		for (int i = 1, x, y; i <= q; ++i) {
			scanf("%d%d", &x, &y);
			query[y].push_back(pII(x, i)); 
		}
		bit.init(); odt.init();
		odt.se.insert(ODT::node(1, m, 0, 0)); 
		for (int i = 1; i <= n; ++i) {
			odt.assign(l[i], r[i], i, v[i]);
			for (auto &it : query[i])
				ans[it.se] = bit.query(it.fi, n); 
		}
		for (int i = 1; i <= q; ++i)
			printf("%lld\n", ans[i]);
	}
	return 0;
}
