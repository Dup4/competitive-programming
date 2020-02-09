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
int n, m;
ll a[N][N], b[N], f[N][N]; 
inline void add(int x1, int y1, int x2, int y2, int v) {
	if (x1 > x2 || y1 > y2) return;
	a[x1][y1] += v;
	a[x1][y2 + 1] -= v;
	a[x2 + 1][y1] -= v;
	a[x2 + 1][y2 + 1] += v;
}
void run() {
	memset(a, 0, sizeof a);
	memset(b, 0, sizeof b);
	for (int i = 1, l, r; i <= m; ++i) {
		cin >> l >> r;
		b[l] += 2; b[r + 1] -= 2;
		add(l, l, r, r, -1);
		add(1, l, l - 1, n, 1);
		add(l, r + 1, r, n, 1);
	}
	for (int i = 1; i <= n; ++i) b[i] += b[i - 1];
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			a[i][j] += a[i - 1][j] + a[i][j - 1] - a[i - 1][j - 1];
		}
	}
	for (int i = 1; i <= n; ++i) a[i][i] += b[i];
	memset(f, 0x3f, sizeof f);
	for (int i = 1; i <= n; ++i) f[i][i] = a[i][i];
	for (int L = 2; L <= n; ++L) {
		for (int i = 1; i + L - 1 <= n; ++i) {
			int l = i, r = i + L - 1;
			for (int j = l; j < r; ++j) {
				chmin(f[l][r], f[i][j] + f[j + 1][r] + a[l][r]);
			}
		}
	}
	pt(f[1][n]);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	cout << fixed << setprecision(20);
	while (cin >> n >> m) run();
	return 0;
}
