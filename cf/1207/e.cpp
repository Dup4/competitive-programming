#include <bits/stdc++.h>
using namespace std;
#define debug(...) { printf("#  "); printf(__VA_ARGS__); puts(""); }
#define ll long long
const int N = 1e5 + 10;
const int mod = 1e9 + 7;
template <class T1, class T2> inline void chadd(T1 &x, T2 y) { x += y; if (x >= mod) x -= mod; } 
template <class T1, class T2> inline void chmax(T1 &x, T2 y) { if (x < y) x = y; }
template <class T1, class T2> inline void chmin(T1 &x, T2 y) { if (x > y) x = y; }
inline int rd() { int x; cin >> x; return x; }
template <class T > inline void out(T s) { cout << s << "\n"; }
inline ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }
inline ll qpow(ll base, ll n) { ll res = 1; while (n) { if (n & 1) res = res * base % mod; base = base * base % mod; n >>= 1; } return res; }
int n, x, y;
void run() {
	cout << "?";
	for (int i = 0; i < 100; ++i) cout << " " << i; cout << "\n"; cout.flush();
	cin >> x;
	cout << " ?"; 
	for (int i = 128, j = 0; j < 100; ++j, i += 128) cout << " " << i; cout << "\n"; cout.flush();
	cin >> y;
	int res = 0;
	for (int i = 14; i >= 7; --i) res = res * 2 + ((x >> i) & 1);
	for (int i = 6; i >= 0; --i) res = res * 2 + ((y >> i) & 1); 
	cout << "! " << res << "\n"; cout.flush();
}

int main() {
	ios::sync_with_stdio(false); 
	cin.tie(nullptr); cout.tie(nullptr);
	cout << fixed << setprecision(20);
	run();
	return 0;
}
