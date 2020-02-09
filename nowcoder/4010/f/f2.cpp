#include <bits/stdc++.h>
using namespace std;
using pII = pair<int, int>;
using ll = long long;
#define dbg(x...) do { cout << "\033[32;1m" << #x << " -> "; err(x); } while (0) 
void err() { cout << "\033[39;0m" << endl; } 
template <class T, class... Ts> void err(const T& arg, const Ts&... args) { cout << arg << ' '; err(args...); }
#define fi first
#define se second
const int N = 1e6 + 10;
int n, q, fa[N], sze[N], son[N], top[N], in[N], out[N], val[N]; 
ll res[N], tot;
vector <vector<pII>> G;

struct BIT {
	ll a[N];
	void init() { memset(a, 0, sizeof a); }
	void update(int x, int v) {
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
		return query(r) - query(l - 1);
	}
}bit;

void dfs(int u) {
	sze[u] = 1;
	son[u] = 0;
	for (auto &it : G[u]) if (it.fi != fa[u]) {
		int v = it.fi, w = it.se;
		fa[v] = u;
		val[v] = w;
		dfs(v);
		sze[u] += sze[v];
		if (!son[u] || sze[v] > sze[son[u]]) son[u] = v;	
	}
}

void gettop(int u, int tp) {
	in[u] = ++*in;
	top[u] = tp;
	if (son[u]) gettop(son[u], tp);
	for (auto &it : G[u]) {
		int v = it.fi;
		if (v == fa[u] || v == son[u]) continue;
		gettop(v, v);
	}
	out[u] = *in;
}

int main() {
	while (scanf("%d", &n) != EOF) {
		*in = 0;
		G.clear(); G.resize(n + 1);
		for (int i = 1, u, v, w; i < n; ++i) {
			scanf("%d%d%d", &u, &v, &w);
			G[u].push_back(pII(v, w));
			G[v].push_back(pII(u, w));
		}
		bit.init();
		memset(res, 0, sizeof res);
		tot = 0;
		fa[1] = 0;
		dfs(1); 
		gettop(1, 1);
		scanf("%d", &q);
		int rt = 1; 
		for (int _q = 1, op, x, v; _q <= q; ++_q) {
			scanf("%d%d", &op, &v);
			if (op == 1) {
				scanf("%d", &x);
				bit.update(in[v], x); 
				tot += x;
				int it = top[v];
				while (it != 1) {
					res[fa[it]] += 1ll * val[it] * x;
					it = top[fa[it]]; 
				}
			} else {
				rt = v;
			}
			ll ans = res[rt];
			if (n > 1) {
				ans += 1ll * val[son[rt]] * bit.query(in[son[rt]], out[son[rt]]);
				ans += 1ll * (tot - bit.query(in[rt], out[rt])) * val[rt];
			}
			printf("%lld\n", ans);
		}
	}
	return 0;
}
