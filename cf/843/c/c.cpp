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
int n, sze[N], f[N], fa[N], rt; 
vector <int> G[N];

struct E { int x, y, z; };
vector <E> vec;

void dfs(int u) {
	sze[u] = 1;
	for (auto &v : G[u]) {
		if (v == fa[u]) continue;
		fa[v] = u;
		dfs(v);
		sze[u] += sze[v];
		chmax(f[u], sze[v]);
	}
	chmax(f[u], n - sze[u]);
	if (f[u] <= n / 2) rt = u;
}

int gSon;
void dfs2(int u, int rt, int top) {
	if (u != rt) {
		vec.push_back({top, gSon, u});
		vec.push_back({u, fa[u], rt});
		gSon = u;
	}
	for (auto &v : G[u]) {
		if (v != fa[u])
			dfs2(v, rt, top);
	}
}

void gao(int u, int fa) {
	for (auto &v : G[u]) if (v != fa) {
		gSon = v;
		dfs2(v, v, u);
		vec.push_back({u, gSon, v});
	}
}

void run() {
	for (int i = 1, u, v; i < n; ++i) {
		rd(u, v);
		G[u].push_back(v);
		G[v].push_back(u); 
	}
	dfs(1);
	int x = 0;
	for (int i = 1; i <= n; ++i) {
		if (i != rt && sze[i] * 2 == n) {
			x = i;
		}
	}
	if (!x) {
		fa[rt] = 0;
		dfs(rt);
		gao(rt, 0);
	} else {
		fa[rt] = x;
		dfs(rt);
		gao(rt, fa[rt]);
		fa[x] = rt;
		dfs(x);
		gao(x, fa[x]);
	}
	pt(SZ(vec));
	for (auto &it : vec)
		pt(it.x, it.y, it.z);
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
