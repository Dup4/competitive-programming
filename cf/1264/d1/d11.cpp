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
constexpr int N = 2e3 + 10;
int n, fac[N], inv[N]; char s[N]; pII l[N], r[N];
ll C(int n, int m) {
	return 1ll * fac[n] * inv[m] % mod * inv[n - m] % mod;
}
void run() {
	n = strlen(s + 1);
	l[0] = pII(0, 0);
	for (int i = 1; i <= n; ++i) {
		l[i] = l[i - 1];
		if (s[i] == '(') ++l[i].fi;
		if (s[i] == '?') ++l[i].se;
	}
	r[n + 1] = pII(0, 0);
	for (int i = n; i >= 1; --i) {
		r[i] = r[i + 1];
		if (s[i] == ')') ++r[i].fi;
		if (s[i] == '?') ++r[i].se;
	}
	int res = 0;
	for (int i = 1; i <= n; ++i) {
		for (int j = 0; j <= l[i].se; ++j) {
			int x = l[i].fi + j;
			int k = x - r[i + 1].fi;
			if (k >= 0 && k <= r[i + 1].se) {
				chadd(res, 1ll * x * C(l[i].se, j) % mod * C(r[i + 1].se, k) % mod);
			}
		}
	}
	pt(res);
}

int main() {
	fac[0] = 1;
	for (int i = 1; i < N; ++i) fac[i] = 1ll * fac[i - 1] * i % mod;
	inv[N - 1] = qpow(fac[N - 1], mod - 2);
	for (int i = N - 1; i >= 1; --i) inv[i - 1] = 1ll * inv[i] * i % mod;
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	cout << fixed << setprecision(20);
	while (cin >> (s + 1)) run();
	return 0;
}
