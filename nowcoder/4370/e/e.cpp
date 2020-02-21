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
constexpr int N = 1e6 + 10; 
int n, m, A, B, C, P, sx, sy, ex, ey, x[N];
int Move[][2] = {1, 0, 0, 1};
inline bool ok(int x, int y) { return x >= 1 && x <= n && y >= 1 && y <= m; }
struct UFS {
	int fa[N], rk[N];
	void init(int n) {
		memset(fa, 0, sizeof (fa[0]) * (n + 5));
		memset(rk, 0, sizeof (rk[0]) * (n + 5));
	}
	int find(int x) { return fa[x] == 0 ? x : fa[x] = find(fa[x]); }
	bool merge(int x, int y) {
		int fx = find(x), fy = find(y);
		if (fx != fy) {
			if (rk[fx] > rk[fy]) swap(fx, fy);
			fa[fx] = fy;
			if (rk[fx] == rk[fy]) ++rk[fy];
			return true;
		}
		return false;
	}
	bool same(int x, int y) { return find(x) == find(y); }
}ufs;

inline int id(int x, int y) { return (x - 1) * m + y; }

void run() {
	vector <vector<pII>> E(10010);
	rd(n, m, sx, sy, ex, ey, x[1], x[2], A, B, C, P);
	for (int i = 3; i <= n * m; ++i) {
		x[i] = (A * x[i - 1] + B * x[i - 2] + C) % P;
	}
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			for (int k = 0; k < 2; ++k) {
				int nx = i + Move[k][0];
				int ny = j + Move[k][1];
				if (ok(nx, ny)) {
					int u = id(i, j), v = id(nx, ny);
					E[x[u] * x[v]].push_back({u, v});
				}
			}	
		}
	}
	ufs.init(n * m);
	ll res = 0;
	for (int i = 10000; i >= 0; --i) {
		for (auto &it : E[i]) {
			res += i * ufs.merge(it.fi, it.se);
		}
	}
	pt(res);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	cout << fixed << setprecision(20);
	int _T = nextInt();
//	while (_T--) run(); 
    for (int kase = 1; kase <= _T; ++kase) {
        cout << "Case #" << kase << ": ";
        run();
    }
//	while (cin >> n) run();
	return 0;
}
