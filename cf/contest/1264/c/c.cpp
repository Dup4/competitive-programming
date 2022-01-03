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
constexpr int mod = 998244353;
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
void ptt() { cout << endl; }
template <class T, class... Ts> void ptt(const T& arg, const Ts&... args) { cout << ' ' << arg; ptt(args...); }
template <class T, class... Ts> void pt(const T& arg, const Ts&... args) { cout << arg; ptt(args...); }
void pt() {}
template <template<typename...> class T, typename t, typename... A>
void pt(const T <t> &arg, const A&... args) { for (int i = 0, sze = arg.size(); i < sze; ++i) cout << arg[i] << " \n"[i == sze - 1]; pt(args...); }
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }
inline ll qpow(ll base, ll n) { ll res = 1; while (n) { if (n & 1) res = res * base % mod; base = base * base % mod; n >>= 1; } return res; }
//head
constexpr int N = 2e5 + 10;
int n, q, p[N]; ll f[N], g[N], inv[N], inv100, res; 
ll gao(int l, int r, int ff) {
	ll A = (g[r] - g[l - 1] + mod) % mod * inv[l - 1] % mod;
	ll B = f[r] * inv[l - 1] % mod;
	return (A * qpow(B, mod - 2) % mod * ff + mod) % mod;
}
void run() {
	f[0] = 1;
	inv[0] = qpow(f[0], mod - 2);
	g[0] = 0;
	for (int i = 1; i <= n; ++i) {
		cin >> p[i];
		p[i] = 1ll * p[i] * inv100 % mod; 
		g[i] = g[i - 1] + f[i - 1];
		f[i] = f[i - 1] * p[i] % mod;
		inv[i] = qpow(f[i], mod - 2);
	}
	set <int> se;
	se.insert(1);
	se.insert(n + 1); 
	res = gao(1, n, 1);
	for (int i = 1, x; i <= q; ++i) {
		cin >> x;
		auto pos = se.lower_bound(x);
		if (*pos == x) {
			auto pre = pos; --pre;
			auto nx = pos; ++nx;
			chadd(res, gao(*pre, *pos - 1, -1));
			chadd(res, gao(*pos, *nx - 1, -1));
			chadd(res, gao(*pre, *nx - 1, 1));
			se.erase(pos);
		} else {
			auto pre = pos; --pre;
			chadd(res, gao(*pre, *pos - 1, -1));
			chadd(res, gao(*pre, x - 1, 1));
			chadd(res, gao(x, *pos - 1, 1));
			se.insert(x);
		}
		pt(res);
	}
}

int main() {
	inv100 = qpow(100, mod - 2);
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	cout << fixed << setprecision(20);
	while (cin >> n >> q) run();
	return 0;
}
