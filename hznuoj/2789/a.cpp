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
constexpr int N = 5e5 + 10; 
constexpr ll INFLL = 0x3f3f3f3f3f3f3f3f;
int n, m, son[N], fa[N], fac[N], inv[N]; 
vector <vector<int>> G;
ll f[N], g[N];

inline int C(int n, int m) {
	if (n < m) return 0;
	return 1ll * fac[n] * inv[n - m] % mod * inv[m] % mod;
}

void dfs(int u) {
	son[u] = 1;
	for (auto &v : G[u]) if (v != fa[u]) {
		fa[v] = u;
		dfs(v);
		son[u] += son[v];
		f[u] += f[v] + son[v]; 
	}
}

void dfs1(int u) {
	for (auto &v : G[u]) if (v != fa[u]) {
		g[v] += g[u] + (n - son[v]);
		g[v] += f[u] - f[v] - son[v];
		dfs1(v);
	}
}

void run() {
	rd(n, m);
	G.clear(); G.resize(n + 1);
	for (int i = 1, u, v; i < n; ++i) {
		rd(u, v);
		G[u].push_back(v);
		G[v].push_back(u);
	}
	memset(son, 0, sizeof son);
	memset(f, 0, sizeof f);
	memset(g, 0, sizeof g);
	dfs(1);
	dfs1(1);
	ll Min = INFLL;
	for (int i = 1; i <= n; ++i) {
		chmin(Min, f[i] + g[i]);
	}
	pt(Min % mod * C(n - 1, m - 1) % mod);
}

int main() {
	fac[0] = 1;
	for (int i = 1; i < N; ++i) fac[i] = 1ll * fac[i - 1] * i % mod;
	inv[N - 1] = qpow(fac[N - 1], mod - 2);
	for (int i = N - 1; i >= 1; --i) inv[i - 1] = 1ll * inv[i] * i % mod;
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
