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
constexpr int N = 10, INF = 1e9; 
int n, a[N], b[N][N], use[N][N]; 

int Move[][2] = {
	0, 1,
	1, 0,
	-1, 0,
	0, -1,
	1, 1,
	-1, 1,
	1, -1,
	-1, -1
};

bool valid(int x, int y) {
	if (x < 1 || x > n || y < 1 || y > n) return 0;
	return 1;
}

int get(int t) {
	memset(use, 0, sizeof use);
	int x = 0, y = 0;
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			if (b[i][j] == 1) {
				x = i, y = j;
			}
		}
	}
	int res = 0;
	use[x][y] = 1;
	for (int i = 1; i < n * n; ++i) {
		int Min = INF, _x = -1, _y = -1;
		for (int j = 0; j < t; ++j) {
			for (int k = 1; ; ++k) {
				int nx = x + Move[j][0] * k;
				int ny = y + Move[j][1] * k;
				if (!valid(nx, ny)) break;
				if (!use[nx][ny]) {
					if (b[nx][ny] < Min) {
						Min = b[nx][ny];
						_x = nx;
						_y = ny;
					}
				}
			}
		}
		if (Min == INF) {
			++res;
			for (int i = 1; i <= n; ++i) {
				for (int j = 1; j <= n; ++j) {
					if (!use[i][j]) {
						if (b[i][j] < Min) {
							Min = b[i][j];
							_x = i;
							_y = j;
						}
					}	
				}
			}
		}
		x = _x; y = _y;
		use[x][y] = 1;
	}
	return res;
}

bool ok() {
	if (get(4) < get(8)) return 1;
	return 0;
}

void run() {
	for (int i = 1; i <= n * n; ++i) a[i] = i;
	b[1][1] = 9;
	b[1][2] = 8;
	b[1][3] = 6;
	b[2][1] = 5;
	b[2][2] = 3;
	b[2][3] = 2;
	b[3][1] = 1;
	b[3][2] = 7;
	b[3][3] = 4;
	dbg(get(4), get(8));
	return;
	do {
		int pos = 1;
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= n; ++j) {
				b[i][j] = a[pos];
				++pos;
			//	cout << b[i][j] << " \n"[j == n];
			}
		}
		if (ok()) {
			for (int i = 1; i <= n; ++i) {
				for (int j = 1; j <= n; ++j) {
					printf("%d%c", b[i][j], " \n"[j == n]);
				}
			}
		}
	} while (next_permutation(a + 1, a + 1 + n * n));
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	cout << fixed << setprecision(20);
	while (cin >> n) run();
//    for (int kase = 1; kase <= _T; ++kase) {
//        cout << "Case #" << kase << ":\n";
//        run();
//    }
	return 0;
}
