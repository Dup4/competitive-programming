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
constexpr int N = 2e5 + 10;
int n, k, a[N], c[N];  
ll res, b[N];
inline void check(int x) {
	if (c[x] >= k) res = min(res, b[x]);
}
void run() {
	memset(b, 0, sizeof b);
	memset(c, 0, sizeof c);
	for (int i = 1; i <= n; ++i) cin >> a[i];
	sort(a + 1, a + 1 + n);
	res = 1e18;
	for (int i = 1; i <= n; ++i) {
		int cnt = 0;
		++c[a[i]]; check(a[i]);
		while (a[i]) {
			a[i] /= 2;
			++cnt;
			++c[a[i]];
			b[a[i]] += cnt;
			check(a[i]);
		}
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