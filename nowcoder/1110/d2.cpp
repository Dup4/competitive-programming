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
constexpr int N = 3e2 + 10, M = 10; 
int n, m, q, black[N], d[N];
vector <vector<int>> G;
bitset <N> B[N];
int gao() {
	for (int i = 1; i <= n; ++i) B[i].reset(), B[i][i] = 1;
	memset(d, 0, sizeof d);
	for (int u = 1; u <= n; ++u) if (!black[u])
		for (auto &v : G[u]) if (!black[v]) ++d[v];
	queue <int> que;
	for (int u = 1; u <= n; ++u) if (!black[u] && d[u] == 0) 
		que.push(u);
	while (!que.empty()) {
		int u = que.front(); que.pop();
		for (auto &v : G[u]) {
			if (!black[v]) {
				B[v] |= B[u];
				if (--d[v] == 0) que.push(v);
			}
		}
	}
	int res = 0;
	for (int u = 1; u <= n; ++u) if (!black[u])
		res += B[u].count() - 1;
	return res;
}
void run() {
	G.clear(); G.resize(n + 1);
	memset(black, 0, sizeof black);
	for (int i = 1, u, v; i <= m; ++i) {
		cin >> u >> v;
		G[v].push_back(u); 
	}
	while (q--) {
		int x = rd();
		black[x] ^= 1;
		pt(gao());
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	cout << fixed << setprecision(20);
	while (cin >> n >> m >> q) run();
	return 0;
}
