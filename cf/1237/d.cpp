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
constexpr int N = 5e5 + 10, M = 25;
int n, a[N], b[N << 1], f[N], res[N];
struct BIT {
	int a[N];
	void init() { memset(a, 0, sizeof a); }
	void update(int x, int v) {
		for (; x > 0; x -= x & -x)
			chmax(a[x], v);
	}
	int query(int x) {
		int res = 0;
		for (; x < N; x += x & -x)
			chmax(res, a[x]);
		return res;
	}
}bit;
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
void run() {
	bit.init();
	for (int i = 1; i <= n; ++i) cin >> a[i];
	for (int i = n + 1; i <= n * 2; ++i) a[i] = a[i - n];
	for (int i = n * 2 + 1; i <= n * 3; ++i) a[i] = a[i - n];
	*b = 0;
	for (int i = 1; i <= n; ++i) b[++*b] = a[i], b[++*b] = a[i] * 2 + 1; 
	sort(b + 1, b + 1 + *b);
	*b = unique(b + 1, b + 1 + *b) - b - 1;
	for (int i = 1; i <= n * 3; ++i) {
		f[i] = bit.query(lower_bound(b + 1, b + 1 + *b, a[i] * 2 + 1) - b);
		bit.update(lower_bound(b + 1, b + 1 + *b, a[i]) - b, i);
	}
	rmq.init(n * 3, f);
	for (int i = 1; i <= n; ++i) {
		int l = i, r = n * 3, ans = -1;
		while (r - l >= 0) {
			int mid = (l + r) >> 1;
			if (rmq.queryMax(i, mid) >= i) {
				ans = mid;
				r = mid - 1;
			} else {
				l = mid + 1;
			}
		}
		if (ans == -1) res[i] = -1;
		else res[i] = ans - i;
	}
	for (int i = 1; i <= n; ++i)
		cout << res[i] << " \n"[i == n];
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	cout << fixed << setprecision(20);
	while (cin >> n) run();
	return 0;
}
