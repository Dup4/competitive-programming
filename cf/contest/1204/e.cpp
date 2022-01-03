#include <bits/stdc++.h>
using namespace std;
#define debug(...) { printf("#  "); printf(__VA_ARGS__); puts(""); }
#define ll long long
const int N = 5e3 + 10;
const int mod = 998244353;
template <class T1, class T2> inline void chadd(T1 &x, T2 y) { x += y; if (x >= mod) x -= mod; } 
template <class T1, class T2> inline void chmax(T1 &x, T2 y) { if (x < y) x = y; }
template <class T1, class T2> inline void chmin(T1 &x, T2 y) { if (x > y) x = y; }
inline int rd() { int x; cin >> x; return x; }
template <class T > inline void out(T s) { cout << s << "\n"; }
inline ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }
inline ll qpow(ll base, ll n) { ll res = 1; while (n) { if (n & 1) res = res * base % mod; base = base * base % mod; n >>= 1; } return res; }
int n, m;
ll fac[N], inv[N];
ll C(int n, int m) {
	if (n < m || m < 0) return 0; 
	return fac[n] * inv[n - m] % mod * inv[m] % mod;
}
void run() {
	ll res = 0, base = 0;
	if (n > m) {
		base = n - m;
		n = m;
	}
	ll pre = 0;
	for (int i = 0; i <= n; ++i) {
		ll now = (C(n + m, n) - C(n + m, n - 1 - i) + mod) % mod;
		chadd(res, 1ll * i * (now - pre + mod) % mod);
		pre = now;
	}
	printf("%lld\n", res);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	cout << fixed << setprecision(20);
	fac[0] = 1;
	for (int i = 1; i < N; ++i) fac[i] = fac[i - 1] * i % mod;
	inv[N - 1] = qpow(fac[N - 1], mod - 2);
	for (int i = N - 1; i >= 1; --i) inv[i - 1] = inv[i] * i % mod;
	while (cin >> n >> m) run();
	return 0;
}
