#include <bits/stdc++.h>
using namespace std;
#define debug(...) { printf("#  "); printf(__VA_ARGS__); puts(""); }
#define fi first
#define se second
#define endl "\n" 
using ll = long long;
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
template <class T> inline void out(T s) { cout << s << "\n"; }
template <class T> inline void out(vector <T> &vec) { for (auto &it : vec) cout << it << " "; cout << endl; } 
inline ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }
inline ll qpow(ll base, ll n) { ll res = 1; while (n) { if (n & 1) res = res * base % mod; base = base * base % mod; n >>= 1; } return res; }
constexpr int N = 1e5 + 10;
constexpr int M = 23;
int n, fa[N][M], dep[N]; ll x[N], f[N][M], res;
vector <vector<int>> G;
void DFS(int u) {
	for (int i = 1; i < M; ++i) {
		fa[u][i] = fa[fa[u][i - 1]][i - 1];
		f[u][i] = gcd(f[u][i - 1], f[fa[u][i - 1]][i - 1]);	
	}
	for (auto &v : G[u]) if (v != fa[u][0]) {
		fa[v][0] = u;
		f[v][0] = gcd(x[u], x[v]);
		dep[v] = dep[u] + 1;
		DFS(v);
	}
}
void run() {
	G.clear(); G.resize(n + 1);
	for (int i = 1; i <= n; ++i) cin >> x[i];
	for (int i = 1, u, v; i < n; ++i) {
		cin >> u >> v;
		G[u].push_back(v);
		G[v].push_back(u);
	}
	fa[1][0] = 1;
	f[1][0] = x[1]; 
	dep[1] = 0;
	DFS(1);
	res = 0;
	for (int i = 1; i <= n; ++i) {
		int u = i; ll g = x[i];  
		while(1) {
			int v = u;
			for (int j = M - 1; j >= 0; --j) {
				if (f[v][j] == 0 || (g && f[v][j] % g == 0)) {
					v = fa[v][j]; 
				}
			}
			res += g % mod * (dep[u] - dep[v] + 1) % mod;
			res %= mod;
			if (v == 1) break;
			u = fa[v][0]; 
			g = gcd(g, x[u]); 
		}
	}
	cout << res << endl;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	cout << fixed << setprecision(20);
	while (cin >> n) run();
	return 0;
}
