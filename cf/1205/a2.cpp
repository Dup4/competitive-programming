#include <bits/stdc++.h>
using namespace std;
#define debug(...) { printf("#  "); printf(__VA_ARGS__); puts(""); }
#define ll long long
const int N = 2e5 + 10;
const int mod = 1e9 + 7;
template <class T1, class T2> inline void chadd(T1 &x, T2 y) { x += y; if (x >= mod) x -= mod; } 
template <class T1, class T2> inline void chmax(T1 &x, T2 y) { if (x < y) x = y; }
template <class T1, class T2> inline void chmin(T1 &x, T2 y) { if (x > y) x = y; }
inline int rd() { int x; cin >> x; return x; }
template <class T > inline void out(T s) { cout << s << "\n"; }
inline ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }
inline ll qpow(ll base, ll n) { ll res = 1; while (n) { if (n & 1) res = res * base % mod; base = base * base % mod; n >>= 1; } return res; }
int n, res[N];
void run() {
	if (n % 2 == 0) return out("NO");
	out("YES");
	for (int i = 1, j = 1; i <= n; ++i, j += 2) {
		if (i & 1) {
			res[i] = j;
			res[i + n] = j + 1;
		} else {
			res[i] = j + 1;
			res[i + n] = j;
		}
	}
	for (int i = 1; i <= 2 * n; ++i)
		cout << res[i] << " \n"[i == 2 * n];
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	cout << fixed << setprecision(20);
	while (cin >> n) run();
	return 0;
}
