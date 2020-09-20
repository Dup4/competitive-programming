#include <bits/stdc++.h>
using namespace std;
#define endl "\n" 
#define fi first
#define se second
#define SZ(x) ((int)(x).size())
#define mkp make_pair
#define all(x) (x).begin(), (x).end()
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
constexpr int N = 1e3 + 10; 
int n, k; 
int f[N], fac[N], inv[N];

inline int C(int n, int m) {
	return 1ll * fac[n] * inv[m] % mod * inv[n - m] % mod;
}

void dfs(vector <int> vec) {
	if (accumulate(all(vec), 0) > 13) return;
	if (SZ(vec) == k) {
		int m = 0;
		int base = 1;
		int scheme = 1;
		int tot = 13;
		for (int i = 0; i < SZ(vec); ++i) {
			m += vec[i] * (i + 1);
			scheme = 1ll * scheme * C(tot, vec[i]) % mod;
			tot -= vec[i];
			base = 1ll * base * qpow(inv[i + 1], vec[i]) % mod;
		}
		chadd(f[m], 1ll * scheme * base % mod); 
	} else {
		for (int i = 0; i <= 13; ++i) {
			vec.push_back(i);
			dfs(vec);
			vec.pop_back();
		}
	}
}

class Solution {
public:
    int keyboard(int _k, int _n) {
		fac[0] = 1;
		for (int i = 1; i < N; ++i) fac[i] = 1ll * fac[i - 1] * i % mod;
		inv[N - 1] = qpow(fac[N - 1], mod - 2);
		for (int i = N - 1; i >= 1; --i) inv[i - 1] = 1ll * inv[i] * i % mod;
		n = _n, k = _k;
		memset(f, 0, sizeof f);
		dfs(vector<int>());
		int res = 0;
		int m = 13 * k;
		for (int i = 0; i <= min(n, m); ++i) {
			chadd(res, 1ll * f[i] * f[n - i] % mod);
		}
		//return (int)(1ll * f[n] * fac[n] % mod);
		return 1ll * res * fac[n] % mod;
    }
};

void run() {
	int k, n;
	rd(k, n);
	pt((new Solution())->keyboard(k, n));
}

int main() {
	fac[0] = 1;
	for (int i = 1; i < N; ++i) fac[i] = 1ll * fac[i - 1] * i % mod;
	inv[N - 1] = qpow(fac[N - 1], mod - 2);
	for (int i = N - 1; i >= 1; --i) inv[i - 1] = 1ll * inv[i] * i % mod;
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	cout << fixed << setprecision(20);
	int _T = 1;
	//nextInt();
	while (_T--) run(); 
//    for (int kase = 1; kase <= _T; ++kase) {
//        cout << "Case #" << kase << ": ";
//        run();
//    }
//	while (cin >> n) run();
//	run();
	return 0;
}
