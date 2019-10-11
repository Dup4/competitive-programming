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
constexpr int N = 6e5 + 10, M = 25; 
struct BIT {
	int a[N];
	void init() { memset(a, 0x3f, sizeof a); }
	void update(int x, int v) {
		for (; x < N; x += x & -x) {
			chmin(a[x], v);
		}
	}
	int query(int x) {
		int res = 0x3f3f3f3f;
		for (; x > 0; x -= x & -x)
			chmin(res, a[x]);
		return res;
	}
}bit;
int n, q, a[N], nx[N], vis[3000010], ans[N]; 
vector <vector<pII>> vec;
void run() {
	for (int i = 1; i <= n; ++i) cin >> a[i], a[i] ^= a[i - 1];
	for (int i = n + 1; i >= 1; --i) a[i] = a[i - 1]; ++n; 
	for (int i = 0; i < 3000010; ++i) vis[i] = n + 1;
	for (int i = n; i >= 1; --i) {
		nx[i] = vis[a[i]] - i;
		vis[a[i]] = i;
	}
	bit.init();
	vec.clear(); vec.resize(n + 1);
	for (int i = 1; i <= q; ++i) {
		int l = rd(), r = rd() + 1;
		vec[l].emplace_back(r, i);
	}
	for (int i = n; i >= 1; --i) {
		bit.update(i + nx[i], nx[i]);
		for (auto &it : vec[i])
			ans[it.se] = bit.query(it.fi);
	}
	for (int i = 1; i <= q; ++i) {
		if (ans[i] > n + 1) ans[i] = -1;
		pt(ans[i]);
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	cout << fixed << setprecision(20);
	while (cin >> n >> q) run();
	return 0;
}
