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
int n, m, k, a[N], b[N]; ll w[N], f[110][3110];  
void run() {
	memset(w, 0, sizeof w);
	for (int i = 0; i <= k; ++i) cin >> w[i];
	for (int i = 1; i <= m; ++i) cin >> a[i] >> b[i];  
	memset(f, -0x3f, sizeof f);
	f[1][0] = 0;
	for (int i = 2; i <= n; ++i) {
		for (int j = 0; j <= k; ++j) {
			f[i][j + w[j]] = max(f[i][j + w[j]], f[i - 1][j]);
		}
		for (int j = 1; j <= m; ++j) {
			for (int o = 3000 - a[j]; o >= 0; --o) {
				f[i][o] = max(f[i][o], f[i][o + a[j]] + b[j]);
			}
		}
	}
	ll ans = 0;
	for (int i = 0; i <= 3100; ++i)
		ans = max(ans, f[n][i] + i + w[i]);
	cout << ans << endl;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	cout << fixed << setprecision(20);
	while (cin >> n >> m >> k) run();
	return 0;
}
