#include <bits/stdc++.h>
#define debug(...) { printf("#  "); printf(__VA_ARGS__); puts(""); }
#define fi first
#define se second
#define endl "\n" 
using namespace std;
using db = double;
using ll = long long;
using ull = unsigned long long; 
using pII = pair <int, int>;
using pLL = pair <ll, ll>;
constexpr int mod = 1e9 + 7;
template <class T1, class T2> inline void chadd(T1 &x, T2 y) { x += y; while (x >= mod) x -= mod; while (x < 0) x += mod; } 
template <class T1, class T2> inline void chmax(T1 &x, T2 y) { if (x < y) x = y; }
template <class T1, class T2> inline void chmin(T1 &x, T2 y) { if (x > y) x = y; }
inline int rd() { int x; cin >> x; return x; }
template <class T> inline void rd(T &x) { cin >> x; }
template <class T> inline void rd(vector <T> &vec) { for (auto &it : vec) cin >> it; }
inline void pt() { cout << endl; }
template <class T, class... Ts> void pt(const T& arg, const Ts&... args) { cout << arg << " "; pt(args...); }
template <class T> inline void pt(const T &s) { cout << s << "\n"; }
template <class T> inline void pt(const vector <T> &vec) { for (auto &it : vec) cout << it << " "; cout << endl; } 
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }
inline ll qpow(ll base, ll n) { ll res = 1; while (n) { if (n & 1) res = res * base % mod; base = base * base % mod; n >>= 1; } return res; }
constexpr int N = 5e5 + 10;
int n, k, fa[N]; ll f[N][2], g[N]; 
vector <vector<pII>> G;
void dfs(int u) {
	f[u][0] = f[u][1] = 0;
	for (auto &it : G[u]) {
		int v = it.fi, w = it.se;
		if (v == fa[u]) continue;
		fa[v] = u;
		dfs(v);
		g[v] = f[v][1] + w - f[v][0];
		f[u][0] += f[v][0]; 
		f[u][1] += f[v][0]; 
	}
	vector <int> id;
	for (auto &it : G[u]) if (it.fi != fa[u]) id.push_back(it.fi);
	sort(id.begin(), id.end(), [&](int x, int y) { return g[x] > g[y]; });
	for (int i = 0, sze = id.size(); i < k && i < sze; ++i) {
		int v = id[i];
		if (g[v] < 0) break;
		if (i < k - 1) f[u][1] += g[v];
		f[u][0] += g[v];
	}
}
void run() {
	cin >> n >> k;
	G.clear(); G.resize(n + 1); 
	for (int i = 1, u, v, w; i < n; ++i) {
		cin >> u >> v >> w;
		G[u].emplace_back(v, w);
		G[v].emplace_back(u, w);
	}
	fa[1] = 1;
	dfs(1);
	pt(max(f[1][0], f[1][1]));
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	cout << fixed << setprecision(20);
	int _T; cin >> _T;
	while (_T--) run();
	return 0;
}
