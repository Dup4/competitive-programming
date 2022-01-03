#pragma GCC optimize("Ofast,unroll-loops,no-stack-protector,fast-math")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#include <bits/stdc++.h>
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
#define dbg(x...) do { cout << "\033[32;1m" << #x << " -> "; err(x); } while (0) 
void err() { cout << "\033[39;0m" << endl; } 
template <class T, class... Ts> void err(const T& arg, const Ts&... args) { cout << arg << ' '; err(args...); }
template <template<typename...> class T, typename t, typename... A> 
void err(const T <t> &arg, const A&... args) { for (auto &v : arg) cout << v << ' '; err(args...); }
inline void pt() { cout << endl; } 
template <class T, class... Ts> void pt(const T& arg, const Ts&... args) { cout << arg << ' '; pt(args...); }
template <template<typename...> class T, typename t, typename... A> 
void pt(const T <t> &arg, const A&... args) { for (auto &v : arg) cout << v << ' '; pt(args...); }
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }
inline ll qpow(ll base, ll n) { ll res = 1; while (n) { if (n & 1) res = res * base % mod; base = base * base % mod; n >>= 1; } return res; }
//head
constexpr int N = 5e5 + 10;
int n, d[N], fa[N], ans[N], rt; ll c[3][N], f[N][3][3], res; 
vector <vector<int>> G;
void dfs(int u) {
	for (auto &v : G[u]) if (v != fa[u]) {
		for (int i = 0; i < 3; ++i) {
			for (int j = 0; j < 3; ++j) {
				if (i == j) continue;
				int p = 3 - i - j;
				chmin(f[v][j][p], f[u][i][j] + c[p][v]);
			}
		}
		fa[v] = u;
		dfs(v);
	}
}

void get(int p, int &col) {
	ans[p] = col;
	for (int i = 0; i < 3; ++i) {
		if (i != col) {
			if (f[p][i][col] == res) {
				res -= c[col][p];
				col = i; 
				return;
			}
		}
	}
}

bool ok() {
	for (int i = 1; i <= n; ++i) {
		if (d[i] == 1) rt = i;
		if (d[i] > 2) return false;
	}
	return true;
}

void dfs2(int u, int fa) {
	for (auto &v : G[u]) if (v != fa) {
		ans[v] = 3 - ans[u] - ans[fa];
		dfs2(v, u);
	}
}

void run() {
	for (int i = 0; i < 3; ++i)
		for (int j = 1; j <= n; ++j)
			cin >> c[i][j];
	memset(d, 0, sizeof d);
	G.clear(); G.resize(n + 1);
	for (int i = 1, u, v; i < n; ++i) {
		cin >> u >> v;
		G[u].push_back(v);
		G[v].push_back(u);
		++d[u]; ++d[v];
	}
	if (!ok()) return pt(-1);
	memset(f, 0x3f, sizeof f);
	for (int i = 0; i < 3; ++i) 
		for (int j = 0; j < 3; ++j)
			if (i != j)
				f[rt][i][j] = c[j][rt];
	fa[rt] = 0;
	dfs(rt);
	res = 1e18;
	for (int i = 1; i <= n; ++i) {
		if (d[i] == 1 && i != rt) {
			for (int j = 0; j < 3; ++j)
				for (int k = 0; k < 3; ++k)
					if (j != k) {
						if (f[i][j][k] < res) {
							res = f[i][j][k];
							ans[i] = k, ans[G[i][0]] = j;
						}
					}
			dfs2(G[i][0], i);
			break;
		}
	}
	pt(res);
	for (int i = 1; i <= n; ++i)
		cout << ans[i] + 1 << " \n"[i == n];
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	cout << fixed << setprecision(20);
	while (cin >> n) run();
	return 0;
}
