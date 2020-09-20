#include <bits/stdc++.h>
using namespace std;
#define endl "\n" 
#define fi first
#define se second
#define SZ(x) ((int)(x).size())
#define mkp make_pair
#define all(x) (x).begin(), (x).end()
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
constexpr int N = 1e2 + 10; 
int n, m, vis[N][N];
vector <vector<int>> g;

bool valid(int x, int y) {
	if (x < 0 || x >= n || y < 0 || y >= m) return false;
	return true;
}

int Move[][2] = {
	-1, 0,
	1, 0,
	0, -1,
	0, 1,
};

void dfs(int x, int y, int z) {
	if (vis[x][y]) return;
	vis[x][y] = 1;
//	g[x][y] = 0;
	for (int i = 0; i < 4; ++i) {
		int nx = x + Move[i][0];
		int ny = y + Move[i][1];
		if (valid(nx, ny) && (g[nx][ny] == 0 || g[nx][ny] == z)) {
			dfs(nx, ny, z);
		}
	}
}

int calc() {
	vector <int> vec(61);
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			vec[g[i][j]] = 1;
		}
	}
	vec[0] = 0;
	return accumulate(all(vec), 0);
}

class Solution {
public:
    bool isPrintable(vector<vector<int>>& targetGrid) {
		n = SZ(targetGrid);
		m = SZ(targetGrid[0]);
		g = targetGrid;
		int cnt = calc();
		while (cnt) {
			for (int i = 60; i >= 1; --i) {
				int cnt = 0;
				int E9 = 1e9;
				int x[2] = {E9, -E9}, y[2] = {E9, -E9};
				//memset(vis, 0, sizeof vis);
				for (int j = 0; j < n; ++j) {
					for (int k = 0; k < m; ++k) {
						if (g[j][k] == i) {
							chmin(x[0], j);
							chmax(x[1], j);
							chmin(y[0], k);
							chmax(y[1], k);
						}
					}
				}
				bool ok = 1;
				for (int j = x[0]; j <= x[1]; ++j) {
					for (int k = y[0]; k <= y[1]; ++k) {
						if (g[j][k] != 0 && g[j][k] != i) {
							ok = 0;
						}
					}
				}
				if (ok) {
					for (int j = x[0]; j <= x[1]; ++j) {
						for (int k = y[0]; k <= y[1]; ++k) {
							g[j][k] = 0;
						}
					}
				}
			//	if (cnt == 1) {
			//		for (int j = 0; j < n; ++j) {
			//			for (int k = 0; k < m; ++k) {
			//				if (g[j][k] == i) {
			//					g[j][k] = 0;
			//				}
			//			}
			//		}	
			//	}
			}
			int now = calc();
			if (now == cnt) return false;
			cnt = now;
		}
		return true;
    }
};

void run() {

}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	cout << fixed << setprecision(20);
	int _T = nextInt();
	while (_T--) run(); 
//    for (int kase = 1; kase <= _T; ++kase) {
//        cout << "Case #" << kase << ": ";
//        run();
//    }
//	while (cin >> n) run();
//	run();
	return 0;
}
