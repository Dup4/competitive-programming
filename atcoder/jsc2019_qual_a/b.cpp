#include <bits/stdc++.h>
using namespace std;
#define debug(...) { printf("#  "); printf(__VA_ARGS__); puts(""); }
#define ll long long
#define endl "\n" 
constexpr int N = 1e5 + 10;
constexpr ll mod = 1e9 + 7;
template <class T1, class T2> inline void chadd(T1 &x, T2 y) { x += y; if (x >= mod) x -= mod; else if (x < 0) x += mod; } 
template <class T1, class T2> inline void chmax(T1 &x, T2 y) { if (x < y) x = y; }
template <class T1, class T2> inline void chmin(T1 &x, T2 y) { if (x > y) x = y; }
inline int rd() { int x; cin >> x; return x; }
template <class T> inline void rd(T &x) { cin >> x; }
template <class T > inline void out(T s) { cout << s << "\n"; }
inline ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }
inline ll qpow(ll base, ll n) { ll res = 1; while (n) { if (n & 1) res = res * base % mod; base = base * base % mod; n >>= 1; } return res; }
int n, k, a[N], f[N], g[N];
inline ll F(ll n) {
	return (n * (n + 1) / 2) % mod;
}
void run() {
	for (int i = 1; i <= n; ++i) cin >> a[i];
	ll res = 0;
	for (int i = n; i >= 1; --i) {
		f[i] = 0; g[i] = 0;
		for (int j = i + 1; j <= n; ++j) 
			f[i] += a[j] < a[i];
		for (int j = 1; j <= n; ++j)
			g[i] += a[j] < a[i]; 
		chadd(res, 1ll * k * f[i] % mod); 
		chadd(res, 1ll * F(k - 1) * g[i] % mod);
	}
	cout << res << endl;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	cout << fixed << setprecision(20);
	while (cin >> n >> k) run();
	return 0;
}

