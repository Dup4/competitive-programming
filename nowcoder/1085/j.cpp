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
template <class T1, class T2> inline void chadd(T1 &x, T2 y) { x += y; if (x >= mod) x -= mod; else if (x < 0) x += mod; } 
template <class T1, class T2> inline void chmax(T1 &x, T2 y) { if (x < y) x = y; }
template <class T1, class T2> inline void chmin(T1 &x, T2 y) { if (x > y) x = y; }
inline int rd() { int x; cin >> x; return x; }
template <class T> inline void rd(T &x) { cin >> x; }
template <class T> inline void rd(vector <T> &vec) { for (auto &it : vec) cin >> it; }
template <class T> inline void out(T s) { cout << s << "\n"; }
template <class T> inline void out(vector <T> &vec) { for (auto &it : vec) cout << it << " "; cout << endl; } 
inline ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }
inline ll qpow(ll base, ll n) { ll res = 1; while (n) { if (n & 1) res = res * base % mod; base = base * base % mod; n >>= 1; } return res; }
constexpr int N = 1e6 + 1010;
constexpr int M = 1e3 + 10; 
int n, a[N], fac[N], inv[N], f[M][M];
inline ll C(int n, int m) {
	if (n < m) return 0;
	return 1ll * fac[n] * inv[m] % mod * inv[n - m] % mod;	
}
inline ll F(int x, int y) {
	if (y == 0) return 1;
	if (y <= 1000) return f[y][x];
	ll res = 0;
	for (int i = 1; i <= x; ++i) {
		chadd(res, C(y + x - i - 1, y - 1));
	}
	return res;
}
void run() {
	a[0] = 1000; a[n + 1] = 1;
	for (int i = 1; i <= n; ++i) cin >> a[i]; 
	int pre = 10001;
	for (int i = 1; i <= n; ++i) {
		if (a[i] != 0) {
			if (a[i] > pre) return out(0);
			pre = a[i];
		}
	}
	ll res = 1; pre = 0; 
	for (int i = 1; i <= n + 1; ++i) {
		if (a[i] == 0) continue;
		res = res * F(a[pre] - a[i] + 1, i - pre - 1) % mod;
		pre = i;
	}
	cout << res << endl;
}

int main() {
	fac[0] = 1;
	for (int i = 1; i < N; ++i) fac[i] = 1ll * fac[i - 1] * i % mod;
	inv[N - 1] = qpow(fac[N - 1], mod - 2);
	for (int i = N - 1; i >= 1; --i) inv[i - 1] = 1ll * inv[i] * i % mod;
	for (int i = 1; i <= 1000; ++i) f[0][i] = 1;
	for (int i = 1; i <= 1000; ++i) {
		for (int j = 1; j <= 1000; ++j) {
			f[i][j] = (f[i][j - 1] + f[i - 1][j]) % mod;
		}
	} 
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	cout << fixed << setprecision(20);
	while (cin >> n) run();
	return 0;
}
