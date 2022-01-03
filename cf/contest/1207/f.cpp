#include <bits/stdc++.h>
using namespace std;
#define debug(...) { printf("#  "); printf(__VA_ARGS__); puts(""); }
#define ll long long
const int N = 5e5 + 10;
const int mod = 1e9 + 7;
template <class T1, class T2> inline void chadd(T1 &x, T2 y) { x += y; if (x >= mod) x -= mod; } 
template <class T1, class T2> inline void chmax(T1 &x, T2 y) { if (x < y) x = y; }
template <class T1, class T2> inline void chmin(T1 &x, T2 y) { if (x > y) x = y; }
inline int rd() { int x; cin >> x; return x; }
template <class T > inline void out(T s) { cout << s << "\n"; }
inline ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }
inline ll qpow(ll base, ll n) { ll res = 1; while (n) { if (n & 1) res = res * base % mod; base = base * base % mod; n >>= 1; } return res; }
int n, q, S, a[N], b[760][760];
void run() {
	n = 500000; S = 740;
	memset(a, 0, sizeof a);
	memset(b, 0, sizeof b);
	for (int _q = 1, op, x, y; _q <= q; ++_q) {
		cin >> op >> x >> y;
		if (op == 1) {
			a[x] += y;
			for (int i = 1; i <= S; ++i) {
				b[i][x % i] += y; 
			}
		} else {
			if (x <= S) cout << b[x][y] << "\n";
			else {
				int res = 0;
				for (int i = y; i <= n; i += x) {
					res += a[i];
				}
				cout << res << "\n";
			}
		}
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	cout << fixed << setprecision(20);
	while (cin >> q) run();
	return 0;
}
