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
int n, p[N], d[N], del[N];
vector <vector<int>> G;
void run() {
	memset(d, 0, sizeof d);
	memset(del, 0, sizeof del);
	G.clear(); G.resize(n + 1);
	for (int i = 1; i <= n; ++i) cin >> p[i];
	for (int i = 1, u, v; i < n; ++i) {
		cin >> u >> v;
		G[u].push_back(v);
		G[v].push_back(u);
		d[u] += p[v];
		d[v] += p[u];
	}
	set <pII> se;
	for (int i = 1; i <= n; ++i) se.insert(pII(d[i], i));
	ll res = 0;
	while (!se.empty()) {
		pII now = *se.begin(); se.erase(now);
		res += now.fi;
		del[now.se] = 1;
		for (auto &v : G[now.se]) if (!del[v]) {
			se.erase(pII(d[v], v));
			d[v] -= p[now.se];
			se.insert(pII(d[v], v));
		} 
	}
	pt(res);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	cout << fixed << setprecision(20);
	while (cin >> n) run();
	return 0;
}
