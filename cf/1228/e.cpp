#include <bits/stdc++.h>
using namespace std;
#define debug(...) { printf("#  "); printf(__VA_ARGS__); puts(""); }
#define fi first
#define se second
#define endl "\n" 
using ll = long long;
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
template <class T> inline void out(T s) { cout << s << "\n"; }
template <class T> inline void out(vector <T> &vec) { for (auto &it : vec) cout << it << " "; cout << endl; } 
inline ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }
inline ll qpow(ll base, ll n) { ll res = 1; while (n) { if (n & 1) res = res * base % mod; base = base * base % mod; n >>= 1; } return res; }
constexpr int N = 300 + 10;
int n, k; ll f[N][N], C[N][N];
void run() {
	if (n == 1 || k == 1) return out(1);
	memset(f, 0, sizeof f);
	for (int i = 1; i <= n; ++i) f[1][i] = f[i][1] = 1;
	for (int i = 2; i <= n; ++i) {
		for (int j = 2; j <= n; ++j) {
			f[i][j] = 0;
			for (int k = 1; k <= j; ++k) {
				chadd(f[i][j], f[i - 1][j] * C[j][k] % mod * qpow(k - 1, j - k) % mod);
			}
			for (int k = 1; k <= i; ++k) {
				chadd(f[i][j], f[i][j - 1] * C[i][k] % mod * qpow(k - 1, i - k) % mod); 
			}
			chadd(f[i][j], f[i - 1][j - 1] * qpow(k - 1, i + j - 1) % mod);
			for (int _i = 1; _i < i; ++_i) {
				for (int _j = 1; _j < j; ++_j) {
					chadd(f[i][j], mod - f[i - 1][j - 1] * qpow(k - 1, i + j - _i - _j) % mod * C[i][_i] % mod * C[j][_j] % mod);
				}
			}
		}
	}
	out(f[n][n]);
}

int main() {
	C[0][0] = 1;
	for (int i = 1; i < N; ++i) {
		C[i][0] = C[i][i] = 1;
		for (int j = 1; j < i; ++j)
			C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % mod;
	}
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	cout << fixed << setprecision(20);
	while (cin >> n >> k) run();
	return 0;
}
