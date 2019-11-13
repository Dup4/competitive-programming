#pragma GCC optimize("Ofast,unroll-loops,no-stack-protector,fast-math")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#include <bits/stdc++.h>
#define fi first
#define se second
#define endl "\n" 
using namespace std;
using db = double;
using ll = long long;
using ull = unsigned long long; 
using pII = pair <int, int>;
using pLL = pair <ll, ll>;
constexpr int mod = 1e9 + 7;
template <class T1, class T2> inline void chadd(T1 &x, T2 y) { x += y; while (x >= mod) x -= mod; while (x < 0) x += mod; } 
template <class T1, class T2> inline void chmax(T1 &x, T2 y) { if (x < y) x = y; }
template <class T1, class T2> inline void chmin(T1 &x, T2 y) { if (x > y) x = y; }
inline int rd() { int x; cin >> x; return x; }
template <class T> inline void rd(T &x) { cin >> x; }
template <class T> inline void rd(vector <T> &vec) { for (auto &it : vec) cin >> it; }  
#define dbg(x...) do { cout << "\033[32;1m" << #x << " -> "; err(x); } while (0) 
void err() { cout << "\033[39;0m" << endl; } 
template <class T, class... Ts> void err(const T& arg, const Ts&... args) { cout << arg << ' '; err(args...); }
template <template<typename...> class T, typename t, typename... A> 
void err(const T <t> &arg, const A&... args) { for (auto &v : arg) cout << v << ' '; err(args...); }
inline void pt() { cout << endl; } 
template <class T, class... Ts> void pt(const T& arg, const Ts&... args) { cout << arg << ' '; pt(args...); }
template <template<typename...> class T, typename t, typename... A> 
void pt(const T <t> &arg, const A&... args) { for (auto &v : arg) cout << v << ' '; pt(args...); }
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }
inline ll qpow(ll base, ll n) { ll res = 1; while (n) { if (n & 1) res = res * base % mod; base = base * base % mod; n >>= 1; } return res; }
//head
constexpr int N = 2e5 + 10, M = 20, INF = 0x3f3f3f3f;
struct RMQ {
	int Max[N][M];
	int mm[N];
	void init(int n, int *b) {
		mm[0] = -1;
		for (int i = 1; i <= n; ++i) {
			mm[i] = ((i & (i - 1)) == 0) ? mm[i - 1] + 1 : mm[i - 1];
			Max[i][0] = b[i];
		}
		for (int j = 1; j <= mm[n]; ++j) {
			for (int i = 1; i + (1 << j) - 1 <= n; ++i) {
				Max[i][j] = max(Max[i][j - 1], Max[i + (1 << (j - 1))][j - 1]);
			}
		}
	}
	int queryMax(int x, int y) {
		int k = mm[y - x + 1];
		return max(Max[x][k], Max[y - (1 << k) + 1][k]);
	}
}rmq;

int n, m, a[N], f[N];
pII b[N]; 
void run() {
	n = rd();
	for (int i = 1; i <= n; ++i) a[i] = rd();
	rmq.init(n, a);
	m = rd();
	for (int i = 1; i <= m; ++i) cin >> b[i].fi >> b[i].se;
	memset(f, 0x3f, sizeof f);
	f[0] = 0;
	sort(b + 1, b + 1 + m, [&](pII x, pII y) {
		if (x.fi != y.fi) return x.fi < y.fi;
		return x.se < y.se;		
	});
	for (int i = m - 1; i >= 1; --i) {
		chmax(b[i].se, b[i + 1].se);
	}
	for (int i = 1; i <= n; ++i) {
		int l = 1, r = i, res = -1;
		while (r - l >= 0) {
			int mid = (l + r) >> 1;
			int Max = rmq.queryMax(i - mid + 1, i);
			int pos = lower_bound(b + 1, b + 1 + m, pII(Max, 0)) - b;
			if (pos >= 1 && pos <= m && b[pos].se >= mid) {
				res = mid;
				l = mid + 1;
			} else {
				r = mid - 1;
			}
		}
		if (res == -1) break;
		f[i] = f[i - res] + 1;
	}
	if (f[n] == INF) f[n] = -1;
	pt(f[n]);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	cout << fixed << setprecision(20);
	int _T = rd();
	while (_T--) run();
	return 0;
}
