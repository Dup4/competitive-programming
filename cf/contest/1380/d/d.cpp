#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define SZ(x) ((int)(x).size())
#define mkp make_pair
#define all(x) (x).begin(), (x).end()
#define endl "\n" 
using db = double;
using ll = long long;
using ull = unsigned long long; 
using pII = pair <int, int>;
using pLL = pair <ll, ll>;
constexpr int mod = 1e9 + 7;
template <class T1, class T2> inline void chadd(T1 &x, T2 y, int Mod = mod) { x += y; while (x >= Mod) x -= Mod; while (x < 0) x += Mod; } 
template <class T1, class T2> inline void chmax(T1 &x, T2 y) { if (x < y) x = y; }
template <class T1, class T2> inline void chmin(T1 &x, T2 y) { if (x > y) x = y; }
inline int nextInt() { int x; cin >> x; return x; }
void rd() {}
template <class T, class... Ts> void rd(T& arg, Ts&... args) { cin >> arg; rd(args...); }
#define dbg(x...) do { cout << "\033[32;1m" << #x << " -> "; err(x); } while (0) 
void err() { cout << "\033[39;0m" << endl; } 
template <class T, class... Ts> void err(const T& arg, const Ts&... args) { cout << arg << ' '; err(args...); }
template <template<typename...> class T, typename t, typename... A> 
void err(const T <t> &arg, const A&... args) { for (auto &v : arg) cout << v << ' '; err(args...); }
void ptt() { cout << endl; }
template <class T, class... Ts> void ptt(const T& arg, const Ts&... args) { cout << ' ' << arg; ptt(args...); }
template <class T, class... Ts> void pt(const T& arg, const Ts&... args) { cout << arg; ptt(args...); }
void pt() {}
template <template<typename...> class T, typename t, typename... A>
void pt(const T <t> &arg, const A&... args) { for (int i = 0, sze = arg.size(); i < sze; ++i) cout << arg[i] << " \n"[i == sze - 1]; pt(args...); }
inline ll qpow(ll base, ll n) { assert(n >= 0); ll res = 1; while (n) { if (n & 1) res = res * base % mod; base = base * base % mod; n >>= 1; } return res; }
//head
constexpr int N = 4e5 + 10; 
constexpr ll INFLL = 0x3f3f3f3f3f3f3f3f;
int n, m, a[N], b[N], vis[N]; ll x, k, y; 

void init() {
	int j = 1;
	for (int i = 1; i <= n; ++i) {
		if (a[i] == b[j]) {
			vis[i] = 1;
			++j;
		}
	}
	if (j <= m) {
		pt(-1);
		exit(0);
	}
}

void run() {
	rd(n, m);
	rd(x, k, y);
	for (int i = 1; i <= n; ++i) rd(a[i]);
	for (int i = 1; i <= m; ++i) rd(b[i]);
	memset(vis, 0, sizeof vis);
	init();
	vector <pII> vec;
	int l = n + 1;
	for (int i = 1; i <= n + 1; ++i) {
		if (vis[i] || i > n) {
			if (l <= n) vec.push_back(pII(l, i - 1));
			l = n + 1;
		} else chmin(l, i);
	}
	ll res = 0;
	for (auto &it : vec) {
		int l = it.fi, r = it.se;
		int Max = 0;
		for (int i = l; i <= r; ++i) {
			chmax(Max, a[i]);
		}
		int ok = 0;
		if (l > 1 && Max < a[l - 1]) ok = 1;
		if (r < n && Max < a[r + 1]) ok = 1;
		int num = r - l + 1;
		ll base = 0;
		if (!ok) {
			if (num < k) return pt(-1);
			base = x;
			num -= k;
		}
		ll Min = INFLL;
		ll tot = 0;
		for (int i = 0; i <= num; ++i) {
			int now = num - i;
			if (now % k == 0) {
				chmin(Min, tot + x * (now / k));
			}
			tot += y;
		}
		res += base + Min;
	}
	pt(res);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	cout << fixed << setprecision(20);
	int _T = 1;
	while (_T--) run(); 
//    for (int kase = 1; kase <= _T; ++kase) {
//        cout << "Case #" << kase << ": ";
//        run();
//    }
//	while (cin >> n) run();
//	run();
	return 0;
}
