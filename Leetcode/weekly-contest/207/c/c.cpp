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
int n, m; 
ll f[N][N][2];

int Move[][2] = {
	-1, 0,
	0, -1
};

bool ok(int x, int y) {
	if (x < 0 || x >= n || y < 0 || y >= m) return false;
	return true;
}

class Solution {
public:
    int maxProductPath(vector<vector<int>>& grid) {
		n = SZ(grid);
		m = SZ(grid[0]);
		memset(f, -1, sizeof f);
		if (grid[0][0] >= 0) f[0][0][0] = grid[0][0];
		else f[0][0][1] = abs(grid[0][0]);
		int zero = grid[0][0] == 0;
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; ++j) {
				zero += grid[i][j] == 0;
				if (i || j) {
					int p = (grid[i][j] < 0);
					for (int k = 0; k < 2; ++k) {
						int nx = i + Move[k][0];
						int ny = j + Move[k][1];
						if (ok(nx, ny) && grid[nx][ny] != 0) {
							if (f[nx][ny][0] != -1) {
								chmax(f[i][j][p], f[nx][ny][0] * abs(grid[i][j]));
							}
							if (f[nx][ny][1] != -1) {
								chmax(f[i][j][p ^ 1], f[nx][ny][1] * abs(grid[i][j]));
							}
						}
					}
				}
			//	dbg(i, j, f[i][j][0], f[i][j][1]);
			}
		}
		int res = -1;
		if (zero) res = 0;
		if (f[n - 1][m - 1][0] != -1) res = f[n - 1][m - 1][0] % mod;
		return res;
    }
};

void run() {
	int n, m;
	rd(n, m);
	vector <vector<int>> vec(n, vector<int>(m));
	for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) rd(vec[i][j]);
	pt((new Solution())->maxProductPath(vec));

}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	cout << fixed << setprecision(20);
	int _T = 1;
	//nextInt();
	while (_T--) run(); 
//    for (int kase = 1; kase <= _T; ++kase) {
//        cout << "Case #" << kase << ": ";
//        run();
//    }
//	while (cin >> n) run();
//	run();
	return 0;
}
