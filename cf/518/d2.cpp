#include <bits/stdc++.h>
using namespace std;
#define debug(...) { printf("#  "); printf(__VA_ARGS__); puts(""); }
#define fi first
#define se second
#define endl "\n" 
using ll = long long;
using db = double;
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
constexpr int N = 2e3 + 10;
int n, t; db p, f[N][N]; 
void run() {
	//f[i][j]表示i秒之后，电梯上有j个人的概率
	//f[i + 1][j + 1] = f[i][j] * p
	//f[i + 1][j] = f[i][j] * (1 - p)
	memset(f, 0, sizeof f);
	f[0][0] = 1;
	db ans = 0; 
	for (int i = 1; i <= t; ++i) {
	 	f[i][n] += f[i - 1][n] * p; 
		for (int j = 0; j <= n; ++j) {
			if (i >= 1 && j >= 1) {
				ans += f[i - 1][j - 1] * p;
				f[i][j] += f[i - 1][j - 1] * p;
			}
			if (i >= 1) f[i][j] += f[i - 1][j] * (1 - p);
		}
	}
	cout << ans << endl;
	
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	cout << fixed << setprecision(20);
	while (cin >> n >> p >> t) run();
	return 0;
}
