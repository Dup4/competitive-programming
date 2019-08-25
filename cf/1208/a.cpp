#include <bits/stdc++.h>
using namespace std;
#define debug(...) { printf("#  "); printf(__VA_ARGS__); puts(""); }
#define ll long long
#define endl "\n" 
constexpr int N = 1e5 + 10;
constexpr int mod = 1e9 + 7;
template <class T1, class T2> inline void chadd(T1 &x, T2 y) { x += y; if (x >= mod) x -= mod; else if (x < 0) x += mod; } 
template <class T1, class T2> inline void chmax(T1 &x, T2 y) { if (x < y) x = y; }
template <class T1, class T2> inline void chmin(T1 &x, T2 y) { if (x > y) x = y; }
inline int rd() { int x; cin >> x; return x; }
template <class T> inline void rd(T &x) { cin >> x; }
template <class T > inline void out(T s) { cout << s << "\n"; }
inline ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }
inline ll qpow(ll base, ll n) { ll res = 1; while (n) { if (n & 1) res = res * base % mod; base = base * base % mod; n >>= 1; } return res; }
ll a, b, n;
void run() {
	cin >> a >> b >> n;
	ll res;
	if (n % 3 == 0) res = a;
	else if (n % 3 == 1) res = b;
	else res = a ^ b;
	cout << res << endl;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	cout << fixed << setprecision(20);
	int T; cin >> T;
	while (T--) run();
	return 0;
}
