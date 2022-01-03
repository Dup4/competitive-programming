#include <bits/stdc++.h>
#define fi first
#define se second
#define SZ(x) ((int)x.size())
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
inline int rd() { int x; cin >> x; return x; }
template <class T> inline void rd(T &x) { cin >> x; }
template <class T> inline void rd(vector <T> &vec) { for (auto &it : vec) cin >> it; }  
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
template <class T1, class T2> T1 gcd(T1 a, T2 b) { return b ? gcd(b, a % b) : a; }
inline ll qpow(ll base, ll n) { assert(n >= 0); ll res = 1; while (n) { if (n & 1) res = res * base % mod; base = base * base % mod; n >>= 1; } return res; }
//head
constexpr int N = 5e4 + 10;
int n, m, d[N], cnt[N]; 
vector <vector<int>> G;
bitset <N / 5 + 5> b[N]; 
void Toposort() {
	memset(d, 0, sizeof d);
	for (int u = 1; u <= n; ++u) {
		for (auto &v : G[u]) {
			++d[v];
		}
	}
	queue <int> q;
	for (int i = 1; i <= n; ++i) {
		if (d[i] == 0)
			q.push(i);
	}
	while (!q.empty()) {
		int u = q.front(); q.pop();
		for (auto &v : G[u]) {
			b[v] |= b[u];
			if (--d[v] == 0)
				q.push(v);
		}
	}
	for (int i = 1; i <= n; ++i)
		cnt[i] += b[i].count();
} 
inline ll sqr(ll x) { return x * x; }
void run() {
	G.clear(); G.resize(n + 1);
	for (int i = 1, u, v; i <= m; ++i) {
		cin >> u >> v;
		G[u].push_back(v);
	}
	memset(cnt, 0, sizeof cnt);
	for (int i = 0; i < 5; ++i) {
		for (int j = 1; j <= n; ++j) {
			b[j].reset();
			if (j % 5 == i) 
				b[j][j / 5] = 1;
		}
		Toposort();
	}
	ll res = 0;
	for (int i = 1; i <= n; ++i) 
		res += sqr(cnt[i]);
	pt(res);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	cout << fixed << setprecision(20);
	while (cin >> n >> m) run();
	return 0;
}