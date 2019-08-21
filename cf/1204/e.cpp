#include <bits/stdc++.h>
using namespace std;
#define debug(...) { printf("#  "); printf(__VA_ARGS__); puts(""); }
#define ll long long
const int N = 2e3 + 10;
const int mod = 998244353;
template <class T1, class T2> inline void chadd(T1 &x, T2 y) { x += y; if (x >= mod) x -= mod; } 
template <class T1, class T2> inline void chmax(T1 &x, T2 y) { if (x < y) x = y; }
template <class T1, class T2> inline void chmin(T1 &x, T2 y) { if (x > y) x = y; }
inline int rd() { int x; cin >> x; return x; }
template <class T > inline void out(T s) { cout << s << "\n"; }
inline ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }
inline ll qpow(ll base, ll n) { ll res = 1; while (n) { if (n & 1) res = res * base % mod; base = base * base % mod; n >>= 1; } return res; }
int n, m;
ll f[N][N];
void run() {
	memset(f, 0, sizeof f);
	for (int i = 1; i <= m; ++i) f[0][i] = 1;
	//f[i][j]表示有i个1， j个-1 最大前缀和=0的方案数
	for (int i = 1; i <= n; ++i) {
		for (int j = i; j <= m; ++j) {
			chadd(f[i][j], f[i - 1][j]);
			chadd(f[i][j], f[i][j - 1]);
		}
	}
	ll res = 0;
	for (int i = 1; i <= n; ++i) {
		ll S = 0;
		for (int j = 1; j <= min(m, n - i); ++j) {
			
		}		
	}
	printf("%lld\n", res);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	cout << fixed << setprecision(20);
	while (cin >> n >> m) run();
	return 0;
}
