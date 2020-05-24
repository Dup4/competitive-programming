#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define SZ(x) ((int)(x).size())
#define mkp make_pair
#define all(x) (x).begin(), (x).end()
#define endl "\n" 
using db = double;
using ll = long long;
using ull = unsigned long long; 
using pII = pair <int, int>;
using pLL = pair <ll, ll>;
using u128 = __int128;
constexpr int mod = 1e9 + 7;
template <class T1, class T2> inline void chadd(T1 &x, T2 y, int Mod = mod) { x += y; while (x >= Mod) x -= Mod; while (x < 0) x += Mod; } 
template <class T1, class T2> inline void chmax(T1 &x, T2 y) { if (x < y) x = y; }
template <class T1, class T2> inline void chmin(T1 &x, T2 y) { if (y < x) x = y; }
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
constexpr int N = 1e6 + 10; 
int n, fa[N], f[N], g[N], h[N]; ll a[N];
vector <vector<int>> G;

struct frac {
	u128 x, y;
	frac(u128 _x = 0, u128 _y = 0) {
		x = _x;
		y = _y;
		u128 g = __gcd(x, y);
		x /= g;
		y /= g;
	}
	bool operator < (frac &other) const {
		return x * other.y < y * other.x;
	}
};

frac res;

void dfs(int u) {
	f[u] = g[u] = 0;
	for (auto &v : G[u]) if (v != fa[u]) {
		fa[v] = u;
		dfs(v);
		if (a[v] == 1) {
			int _f = f[v] + 1;
			if (_f > f[u]) { 
				g[u] = f[u];
				f[u] = _f;
			} else if (_f > g[u]) {
				g[u] = _f;
			}
		}
	}
	chmin(res, frac(a[u], f[u] + g[u] + 1));
}

void dfs1(int u) {
	for (auto &v : G[u]) if (v != fa[u]) {
		if (a[u] == 1) {
			int _h = h[u] + 1;
			chmax(h[v], _h);
			if (a[v] == 1 && f[u] == f[v] + 1) {
				chmax(h[v], g[u] + 1);
			} else {
				chmax(h[v], f[u] + 1);
			}
			chmin(res, frac(a[v], f[v] + h[v] + 1));
		} else {
			h[v] = 0;
		}	
		dfs1(v);
	}
}

void run() {
	rd(n);
	G.clear(); G.resize(n + 1);
	for (int i = 2, u, v; i <= n; ++i) {
		rd(u, v);
		G[u].push_back(v);
		G[v].push_back(u);
	}
	int zero = 0, one = 0, Min = 2e9;
	for (int i = 1; i <= n; ++i) {
		rd(a[i]);
		zero += (a[i] == 0);
		one += (a[i] == 1);
		chmin(Min, a[i]);
	}
	if (zero) return pt("0/1");
	if (one == 0) {
		cout << Min << "/1" << endl;
	} else {
		res = frac(1, 1);
		dfs(1);
		dfs1(1);
		//dbg(f[4], g[4], h[4]);
		cout << ll(res.x) << "/" << ll(res.y) << endl;
	}
}

int main() {
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
