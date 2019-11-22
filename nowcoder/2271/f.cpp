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
constexpr int N = 5e2 + 10, M = 5e4 + 1100;
int n, W, a[N], fa[N], dep[N], f[2][N][M], g[2][M];  
//0 不选　1 选
vector <vector<pII>> G;
void dfs(int u) {
	dep[u] = 1; 
	f[0][u][0] = 0; 
	for (auto &it : G[u]) {
		int v = it.fi, w = it.se;
		if (v == fa[u]) continue;
		fa[v] = u;
		dfs(v);
		dep[u] += dep[v];
		for (int i = 0; i <= dep[u] * W; ++i) {
			for (int j = 0; j < 2; ++j) {
				g[j][i] = f[j][u][i];
			}
		}
		for (int i = 0; i <= dep[v] * W; ++i) {
			for (int j = 0; j <= dep[u] * W; ++j) {
				if (g[0][j] != -1 && (f[0][v][i] != -1 || f[1][v][i] != -1)) {
					chmax(f[0][u][i + j], g[0][j] + max(f[0][v][i], f[1][v][i]));
				}
				if (g[0][j] != -1 && f[0][v][i] != -1) {
					chmax(f[1][u][i + j + w], g[0][j] + f[0][v][i] + a[u] + a[v]);
				}
			}
		}	
	}
}
void run() {
	for (int i = 1; i <= n; ++i) a[i] = rd();
	G.clear(); G.resize(n + 1);
	for (int i = 1, u, v, w; i < n; ++i) {
		u = rd(), v = rd(), w = rd();
		G[u].push_back(pII(v, w));
		G[v].push_back(pII(u, w));
	}
	memset(f, -1, sizeof f); 
	dfs(1);
	ll A = 0, B = 1;
	for (int i = 1; i <= n; ++i) {
		for (int j = W; j < M; ++j) {
			for (int k = 0; k < 2; ++k) {
				ll tot = f[k][i][j];
				if (tot != -1) {
					if (tot * B > A * j) {
						A = tot;
						B = j;
					}
				}
			}
		}
	}
	pt(A * 1.0 / B);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	cout << fixed << setprecision(2);
	while (cin >> n >> W) run();
	return 0;
}
