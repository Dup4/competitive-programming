#include <bits/stdc++.h>
#define fi first
#define se second
#define SZ(x) int((x).size())
#define endl "\n" 
using namespace std;
using db = double;
using ll = long long;
using ull = unsigned long long; 
using pII = pair <int, int>;
using pLL = pair <ll, ll>;
constexpr int mod = 998244353;
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
constexpr int N = 1e7 + 10;
ll n; int h[N];

inline ll lowbit(ll x) { return x & -x; }

inline int f(ll x) {
	if (x < N) return h[x];
	int res = 0, bit = 1;
	while (x) {
		if (x & 1) {
			chadd(res, ((x >> 1) + 1) % mod * bit % mod);
		} else {
			chadd(res, (((x - 1) >> 1) + 1) % mod * bit % mod); 
		}
		chadd(bit, bit);
		x >>= 1;
	}
	return res;
}

void run() {
	h[0] = 0;
	for (int i = 1; i < N; ++i) chadd(h[i], h[i - 1] + lowbit(i));
	rd(n); 
	ll res = 0, pre = 0, prePos = -1;
	for (ll i = 1, j; i <= n; i = j + 1) {
		j = n / (n / i);
		if (0 && i == j) chadd(res, (n / i) % mod * lowbit(i) % mod);
		else {
			ll now = f(j);
			if (prePos < i - 1) {
				prePos = i - 1;
				pre = f(prePos);
			}
			chadd(res, (n / i) % mod * (now - pre + mod) % mod); 
			pre = now;
			prePos = j;
		}
	//	ll now = f(j);
	//	chadd(res, (n / i) % mod * (now - pre + mod) % mod);
	//	pre = now;
	}	
	pt(res);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	cout << fixed << setprecision(20);
	//pt(f(4));
		run();
//    for (int kase = 1; kase <= _T; ++kase) {
//        cout << "Case #" << kase << ":\n";
//        run();
//    }
	return 0;
}