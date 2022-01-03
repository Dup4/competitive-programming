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
constexpr int N = 2e5 + 10; 
int n, q, a[N << 1], b[N], s[N], f[N], g[N], id[N];
vector <vector<int>> G[2]; 

namespace Tree {
	int fa[N], deep[N], sze[N], son[N], top[N], in[N], out[N], Sta[N << 1];
	void dfs(int u) {
		son[u] = 0; sze[u] = 1;
		for (auto &v : G[0][u]) {
			if (v == fa[u]) continue;
			fa[v] = u;
			deep[v] = deep[u] + 1;
			dfs(v);
			sze[u] += sze[v];
			if (!son[u] || sze[v] > sze[son[u]]) son[u] = v;
		}
	}
	void gettop(int u, int tp) {
		in[u] = ++*in;
		top[u] = tp;
		if (son[u]) gettop(son[u], tp);
		for (auto &v : G[0][u]) {
			if (v != son[u] && v != fa[u])
				gettop(v, v);
		}
		out[u] = *in;
	}
	int querylca(int u, int v) {
		while (top[u] != top[v]) {
			if (deep[top[u]] < deep[top[v]]) swap(u, v);
			u = fa[top[u]];
		}
		if (deep[u] > deep[v]) swap(u, v);
		return u;
	}
	int querydis(int u, int v) { return deep[u] + deep[v] - 2 * deep[querylca(u, v)]; } 
	void init() {
		fa[1] = 0; deep[1] = 0; *in = 0;
		dfs(1); gettop(1, 1);
	}
	int ceil(int a, int b) { return (a + b - 1) / b; }
	int op(int a, int b, int u) {
		if (!a || !b) return a | b;
		int dis_a = querydis(a, u), dis_b = querydis(b, u);
		int t_a = ceil(dis_a, s[a]), t_b = ceil(dis_b, s[b]);
		if (t_a == t_b) {
			if (id[a] < id[b]) return a;
			return b;
		} else {
			if (t_a < t_b) return a;
			return b;
		}
	}
	void dp(int u, int fa) {
		if (s[u] != -1) f[u] = u;
		for (auto &v : G[1][u]) {
			if (v == fa) continue;
			dp(v, u);
		    f[u] = op(f[u], f[v], u); 	
		}
	}
	void dp1(int u, int fa) { 
		if (s[u] != -1) g[u] = u;
		for (auto &v : G[1][u]) {
			if (v == fa) continue;
			g[v] = op(g[v], op(g[u], f[u], u), v);
			dp1(v, u);
		}
	}
	void gao() {
		int k = *a;
		sort(a + 1, a + 1 + k, [&](int x, int y) {
			return in[x] < in[y];		
		});
		for (int i = k; i > 1; --i) {
			a[++*a] = querylca(a[i], a[i - 1]);
		}
		sort(a + 1, a + 1 + a[0], [&](int x, int y) {
			return in[x] < in[y];		
		});
		a[0] = unique(a + 1, a + 1 + a[0]) - a - 1;
		for (int i = 1, top = 0; i <= a[0]; ++i) {
			while (top && out[Sta[top]] < in[a[i]]) --top;
			if (top) {
				G[1][Sta[top]].push_back(a[i]);
				G[1][a[i]].push_back(Sta[top]);
			}
			Sta[++top] = a[i];
		}
		dp(a[1], a[1]);
		dp1(a[1], a[1]);
		for (int i = 1; i <= *b; ++i) {
			int res = op(f[b[i]], g[b[i]], b[i]);
			cout << id[res] << " \n"[i == *b];
		}
	}
}

void run() {
	G[0].clear(); G[0].resize(n + 1);
	G[1].clear(); G[1].resize(n + 1);
	memset(s, -1, sizeof s);
	memset(f, 0, sizeof f);
	memset(g, 0, sizeof g);
	for (int i = 1, u, v; i < n; ++i) {
		rd(u, v);
		G[0][u].push_back(v);
		G[0][v].push_back(u);
	}
	Tree::init();
	rd(q);
	while (q--) {
		int k, m; rd(k, m);
		*a = 0; *b = 0;  
		for (int i = 1, x; i <= k; ++i) {
			rd(x); rd(s[x]);
			a[++*a] = x;
		    id[x] = i;	
		}
		for (int i = 1, x; i <= m; ++i) {
			rd(x);
			b[++*b] = x; 
			a[++*a] = x;
		}
		sort(a + 1, a + 1 + *a);
		*a = unique(a + 1, a + 1 + *a) - a; 
		Tree::gao();
		for (int i = 1; i <= *a; ++i) {
			G[1][a[i]].clear();
			s[a[i]] = -1; 
			f[a[i]] = g[a[i]] = 0;
		}
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	cout << fixed << setprecision(20);
	while (cin >> n) run();
//    for (int kase = 1; kase <= _T; ++kase) {
//        cout << "Case #" << kase << ":\n";
//        run();
//    }
	return 0;
}
