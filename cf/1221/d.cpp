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
constexpr int N = 3e5 + 10;
constexpr ll INF = 0x3f3f3f3f3f3f3f3f;
int n, a[N], b[N]; ll f[N][2];  
void run() {
	cin >> n;
	for (int i = 1; i <= n; ++i) cin >> a[i] >> b[i];  
	f[1][0] = 0; f[1][1] = b[1];
	for (int i = 2; i <= n; ++i) {
		f[i][1] = min(f[i - 1][0], f[i - 1][1]) + b[i];
		if (a[i] == a[i - 1]) {
			f[i][0] = f[i - 1][1];
		} else {
			f[i][0] = min(f[i - 1][0], f[i - 1][1]);
		}
	}
	cout << min(f[n][0], f[n][1]) << endl;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	cout << fixed << setprecision(20);
	int _T; cin >> _T;
	while (_T--) run();
	return 0;
}
