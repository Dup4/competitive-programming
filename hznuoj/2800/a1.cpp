#include <bits/stdc++.h>
using namespace std;
#define endl "\n" 
#define fi first
#define se second
#define SZ(x) ((int)(x).size())
#define mkp make_pair
#define all(x) (x).begin(), (x).end()
using db = double;
using ll = long long;
using ull = unsigned long long; 
using pII = pair <int, int>;
using pLL = pair <ll, ll>;
constexpr int mod = 1e9 + 7;
template <class T1, class T2> inline void chadd(T1 &x, T2 y, int Mod = mod) { x += y; while (x >= Mod) x -= Mod; while (x < 0) x += Mod; } 
template <class T1, class T2> inline void chmax(T1 &x, T2 y) { if (x < y) x = y; }
template <class T1, class T2> inline void chmin(T1 &x, T2 y) { if (x > y) x = y; }
inline int nextInt() { int x; cin >> x; return x; }
void rd() {}
template <class T, class... Ts> void rd(T& arg, Ts&... args) { cin >> arg; rd(args...); }
#define dbg(x...) do { cout << "\033[32;1m" << #x << " -> "; err(x); } while (0) 
void err() { cout << "\033[39;0m" << endl; } 
template <class T, class... Ts> void err(const T& arg, const Ts&... args) { cout << arg << ' '; err(args...); }
template <template<typename...> class T, typename t, typename... A> 
void err(const T <t> &arg, const A&... args) { for (auto &v : arg) cout << v << ' '; err(args...); }
void ptt() { cout << endl; }
template <class T, class... Ts> void ptt(const T& arg, const Ts&... args) { cout << ' ' << arg; ptt(args...); }
template <class T, class... Ts> void pt(const T& arg, const Ts&... args) { cout << arg; ptt(args...); }
void pt() {}
template <template<typename...> class T, typename t, typename... A>
void pt(const T <t> &arg, const A&... args) { for (int i = 0, sze = arg.size(); i < sze; ++i) cout << arg[i] << " \n"[i == sze - 1]; pt(args...); }
inline ll qpow(ll base, ll n) { assert(n >= 0); ll res = 1; while (n) { if (n & 1) res = res * base % mod; base = base * base % mod; n >>= 1; } return res; }
//head
constexpr int N = 1e5 + 10; 
int n, q, a[N], _w[N];
struct BIT { 
	int a[N];
	void init() { memset(a, 0, sizeof a); }
	void update(int x, int v) { for (; x < N; a[x] += v, x += x & -x); }
	int query(int x) { int res = 0; for (; x > 0; res += a[x], x -= x & -x); return res; }
	int query(int l, int r) { return query(r) - query(l - 1); }
}bit[20];
vector <vector<pII>> G;
ll tot[N];

int fa[N], deep[N], dis[N], sze[N], son[N], top[N], in[N], fin[N], out[N]; 
void dfs(int u) {
	sze[u] = 1; son[u] = 0;
	for (auto &it : G[u]) {
		int v = it.fi, w = it.se;
		if (v == fa[u]) continue;
		_w[v] = w;
		fa[v] = u; deep[v] = deep[u] + 1; dis[v] = dis[u] + w;
		dfs(v);
		sze[u] += sze[v];
		if (!son[u] || sze[v] > sze[son[u]]) son[u] = v; 
	}
}

void gettop(int u, int tp) {
	in[u] = ++*in; fin[*in] = u;
	top[u] = tp;
	if (son[u]) gettop(son[u], tp);
	for (auto &it : G[u]) {
		int v = it.fi;
		if (v != son[u] && v != fa[u]) {
			gettop(v, v);
		}
	}
	out[u] = *in;
}

void init(int rt) {
	_w[rt] = 0;
	fa[rt] = rt;
	dis[rt] = 0; 
	*in = 0;
	dfs(rt);
	gettop(rt, rt);
} 

void run() {
	rd(n);	
	G.clear(); G.resize(n + 1);
	for (int i = 1, u, v, w; i < n; ++i) {
		rd(u, v, w);
		G[u].push_back(pII(v, w));
		G[v].push_back(pII(u, w));
	}
	for (int i = 0; i < 20; ++i) bit[i].init();
	init(1);
	for (int i = 1; i <= n; ++i) {
		int it = top[i];
		while (it != 1) {
			tot[fa[it]] += _w[it];
			it = top[fa[it]];
		}
	}
	rd(q);
	for (int i = 1, op, x, y; i <= q; ++i) {
		rd(op, x);
		if (op == 1) {
			rd(y);
			for (int j = 0; j < 20; ++j) {
				bit[j].update(in[x], ((y >> j) & 1) - ((a[x] >> j) & 1));
			}
			int it = top[x];
			while (it != 1) {
				tot[fa[it]] -= _w[it] ^ a[x];
				tot[fa[it]] += _w[it] ^ y;
				it = top[fa[it]];
			}
			a[x] = y;
		} else {
			ll res = tot[x];
			if (x != 1) {
				int _sze = n - sze[x];
				for (int j = 0; j < 20; ++j) {
					if ((_w[x] >> j) & 1) {
						res += (1ll << j) * (_sze - bit[j].query(1, n) + bit[j].query(in[x], out[x]));
					} else {
						res += (1ll << j) * (bit[j].query(1, n) - bit[j].query(in[x], out[x]));
					}
				}
			}
		//	pt(res);
			if (son[x]) {
				int v = son[x];
				int _sze = sze[v];
				for (int j = 0; j < 20; ++j) {
					if ((_w[v] >> j) & 1) {
						res += (1ll << j) * (_sze - bit[j].query(in[v], out[v]));
					} else {
						res += (1ll << j) * bit[j].query(in[v], out[v]);
					}
				}
			}
			pt(res);
		}
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	cout << fixed << setprecision(20);
	int _T = 1;
	while (_T--) run(); 
//    for (int kase = 1; kase <= _T; ++kase) {
//        cout << "Case #" << kase << ": ";
//        run();
//    }
//	while (cin >> n) run();
//	run();
	return 0;
}
