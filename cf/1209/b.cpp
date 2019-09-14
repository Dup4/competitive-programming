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
constexpr int N = 1e5 + 10;
int n, a[N], b[N], c[N]; char s[N];
inline void add(int l, int r) {
	if (l > r) return;
	++c[l]; --c[r + 1];
}
void run() {
	cin >> (s + 1);
	for (int i = 1; i <= n; ++i) cin >> a[i] >> b[i];
	memset(c, 0, sizeof c);
	for (int i = 1; i <= n; ++i) {
	//	cout << a[i] << " " << b[i] << endl;
		int t = s[i] - '0';
		int pre = 0;
		for (int j = b[i]; j <= 10000; j += a[i]) {
			if (t) add(pre, j - 1);
			t ^= 1;
			pre = j; 
		}
	}
	for (int i = 1; i <= 10000; ++i) c[i] += c[i - 1];
	int res = 0;
	for (int i = 0; i <= 10000; ++i) res = max(res, c[i]);
	cout << res << endl;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	cout << fixed << setprecision(20);
	while (cin >> n) run();
	return 0;
}
