#include <bits/stdc++.h>
using namespace std;
#define debug(...) { printf("#  "); printf(__VA_ARGS__); puts(""); }
#define fi first
#define se second
#define endl "\n" 
using ll = long long;
using ull = unsigned long long; 
using pII = pair <int, int>;
using pLL = pair <ll, ll>;
using VI = vector <int>;
using VL = vector <ll>;
constexpr int mod = 1e9 + 7;
template <class T1, class T2> inline void chadd(T1 &x, T2 y) { x += y; while (x >= mod) x -= mod; while (x < 0) x += mod; } 
template <class T1, class T2> inline void chmax(T1 &x, T2 y) { if (x < y) x = y; }
template <class T1, class T2> inline void chmin(T1 &x, T2 y) { if (x > y) x = y; }
inline int rd() { int x; cin >> x; return x; }
template <class T> inline void rd(T &x) { cin >> x; }
template <class T> inline void rd(vector <T> &vec) { for (auto &it : vec) cin >> it; }
template <class T> inline void pt(T s) { cout << s << "\n"; }
template <class T> inline void pt(vector <T> &vec) { for (auto &it : vec) cout << it << " "; cout << endl; } 
inline ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }
inline ll qpow(ll base, ll n) { ll res = 1; while (n) { if (n & 1) res = res * base % mod; base = base * base % mod; n >>= 1; } return res; }
constexpr int N = 1e5 + 10;
int n, fa[N], a[N]; ll f[N], g[N], h[N], tot, res;
vector <vector<int>> G;
void dfs(int u) {
	int bk = h[a[u]];
	res -= bk;
	h[a[u]] = tot;
	res += h[a[u]];
	f[u] = res;
	++g[a[u]];
	if (g[a[u]] == 1) ++tot;
	for (auto &v : G[u]) dfs(v);
	--g[a[u]];
	if (g[a[u]] == 0) --tot;
	res -= h[a[u]];
	h[a[u]] = bk;
	res += bk;
}
void run() {
	tot = 0; res = 0;
	memset(f, 0, sizeof (f[0]) * (n + 1));
	memset(g, 0, sizeof (g[0]) * (n + 1));
	memset(h, 0, sizeof (h[0]) * (n + 1));
	G.clear(); G.resize(n + 1);
	fa[1] = 1;
	for (int i = 2; i <= n; ++i) {
		cin >> fa[i];
		G[fa[i]].push_back(i);
	}
	for (int i = 1; i <= n; ++i) cin >> a[i];
	dfs(1);
	for (int i = 2; i <= n; ++i) {
		cout << f[i] << endl;
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	cout << fixed << setprecision(20);
	while (cin >> n) run();
	return 0;
}
