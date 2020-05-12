#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define SZ(x) int((x).size())
#define endl "\n" 
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
constexpr int N = 1e3 + 10; 
int W, H, L, U, R, D; 
db f[N][N];
db bit[N];

db C(int n, int m) {
	db res = 1;
	for (int i = n; i > n - m; --i) {
		res *= i;
	}
	for (int i = 1; i <= m; ++i) res /= i;
	return res;
}

bool ok(int x, int y) {
	if (x < 1 || x > H || y < 1 || y > W) return 0;
//	if (x >= U && x <= D && y >= L && y <= R) return 0;
	return 1;
}

bool ok2(int x, int y) {
	if (x >= U && x <= D && y >= L && y <= R) return 0;
	return 1;
}

int Move[][2] = {
	1, 0,
	0, 1,
};

void run() {
	rd(W, H, L, U, R, D);
	memset(f, 0, sizeof f);
	f[1][1] = 1;
	for (int i = 1; i <= H; ++i) {
		for (int j = 1; j <= W; ++j) if (ok2(i, j)) {
	//	   dbg(i, j, f[i][j]);	
			int nx = i + Move[0][0];
			int ny = j + Move[0][1];
			int nx2 = i + Move[1][0];
			int ny2 = j + Move[1][1];
			if (ok(nx, ny) && ok(nx2, ny2)) {
				f[nx][ny] += f[i][j] * 0.5;
				f[nx2][ny2] += f[i][j] * 0.5;
			} else if (ok(nx, ny)) {
				f[nx][ny] += f[i][j];
			} else if (ok(nx2, ny2)) {
				f[nx2][ny2] += f[i][j];
			}
		}
	}	
	pt(f[H][W]);
}

int main() {
	bit[0] = 1;
	for (int i = 1; i < N; ++i) bit[i] = bit[i - 1] * 0.5;
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
//	run();
	return 0;
}
