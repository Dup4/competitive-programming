#include <bits/stdc++.h>
#define fi first
#define se second
#define endl "\n" 
using namespace std;
using db = double;
using ll = long long;
using ull = unsigned long long; 
using pII = pair <int, int>;
using pLL = pair <ll, ll>;
constexpr int mod = 1e9 + 7;
template <class T1, class T2> inline void chadd(T1 &x, T2 y) { x += y; while (x >= mod) x -= mod; while (x < 0) x += mod; } 
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
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }
inline ll qpow(ll base, ll n) { ll res = 1; while (n) { if (n & 1) res = res * base % mod; base = base * base % mod; n >>= 1; } return res; }
//head
constexpr int N = 5e2 + 10;
int n, m, K, p, q, inv, f[2][N][N], g[N]; 
void run() {
	cin >> n >> m >> K >> p >> q;
	for (int i = 0; i < 2; ++i) 
		for (int j = 0; j <= n; ++j)
			for (int k = 0; k <= n; ++k)
				f[i][j][k] = 0;
	f[1][0][0] = 1;
    int A = 1ll * p * inv % mod, B = 1ll * q * inv % mod, C = 1ll * (100 - p - q) * inv % mod;	
	for (int i = 2; i <= m; ++i) {
		int p = i & 1;
		for (int j = 0; j <= n; ++j) {
			for (int k = 0; k + j <= i; ++k) {
				f[p][j][k] = 0;
			}
		}
		for (int x = 0; x < n; ++x) {
			for (int y = 0; x + y <= i; ++y) {
				chadd(f[p][x][y], 1ll * f[p ^ 1][x][y] * C % mod);
				//顺时针
				if (y) {
					if (x == 0) chadd(f[p][x][y], 1ll * f[p ^ 1][0][y - 1] * A % mod);
					chadd(f[p][x][y], 1ll * f[p ^ 1][x + 1][y - 1] * A % mod);
				}
				//逆时针
				if (x) {
					if (y == 0) chadd(f[p][x][y], 1ll * f[p ^ 1][x - 1][0] * B % mod);
					chadd(f[p][x][y], 1ll * f[p ^ 1][x - 1][y + 1] * B % mod);
				}
			}
		}
	}
	for (int i = 0; i <= n; ++i) g[i] = 0;
	g[n] = 1;
	for (int i = 1; i < n; ++i) {
		for (int x = 0; x <= i - 1; ++x) {
			chadd(g[i], f[m & 1][x][i - 1 - x]);
		}
		chadd(g[n], mod - g[i]);
	}
	int ans = 0;
	for (int i = 1; i <= n; ++i) {
		chadd(ans, qpow(i, K) * g[i] % mod);
	}
	pt(qpow(100, m - 1) * ans % mod); 
}

int main() {
	inv = qpow(100, mod - 2);
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	cout << fixed << setprecision(20);
	int _T = rd();
	while (_T--) run();
	return 0;
}
