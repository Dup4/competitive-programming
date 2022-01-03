#include <bits/stdc++.h>
#define fi first
#define se second
#define SZ(x) int((x).size())
#define endl "\n" 
using namespace std;
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
int n;
vector <vector<int>> G;

struct LCA {
	int fa[N], deep[N], dis[N], sze[N], son[N], top[N]; 
	void dfs(int u) {
		sze[u] = 1; son[u] = 0;
		for (auto &v : G[u]) {
			if (v == fa[u]) continue;
			fa[v] = u; deep[v] = deep[u] + 1; dis[v] = dis[u] + 1;
			dfs(v);
			sze[u] += sze[v];
			if (!son[u] || sze[v] > sze[son[u]]) son[u] = v; 
		}
	}
	void gettop(int u, int tp) {
		top[u] = tp;
		if (son[u]) gettop(son[u], tp);
		for (auto &v : G[u]) {
			if (v != son[u] && v != fa[u]) {
				gettop(v, v);
			}
		}
	}
	void init(int rt) {
		fa[rt] = rt;
		dfs(rt);
		gettop(rt, rt);
	} 
	int querylca(int u, int v) {
		while (top[u] != top[v]) {
			if (deep[top[u]] < deep[top[v]]) {
				swap(u, v);
			}
			u = fa[top[u]];
		}
		if (deep[u] > deep[v]) swap(u, v);
		return u;
	}
	int querydis(int u, int v) { return dis[u] + dis[v] - 2 * dis[querylca(u, v)]; }
}lca;

void run() {
	G.clear(); G.resize(n + 1);
	for (int i = 1, u, v; i < n; ++i) {
		rd(u, v);
		G[u].push_back(v);
		G[v].push_back(u);
	}
	lca.init(1);
	int q; rd(q);
	while (q--) {
		int x, y, a, b, k;
		rd(x, y, a, b, k);
		int len[3] = {
			lca.querydis(a, b),
			lca.querydis(a, x) + lca.querydis(y, b) + 1,
			lca.querydis(a, y) + lca.querydis(x, b) + 1
		};
		int ok = 0;
		for (int i = 0; i < 3; ++i) {
			if (k >= len[i] && abs(k - len[i]) % 2 == 0) {
				ok = 1;
				pt("YES");
				break;
			}
		}
		if (!ok) pt("NO");
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	cout << fixed << setprecision(20);
//	int _T = nextInt();
//	while (_T--) run(); 
	while (cin >> n) run();
//    for (int kase = 1; kase <= _T; ++kase) {
//        cout << "Case #" << kase << ":\n";
//        run();
//    }
	return 0;
}
