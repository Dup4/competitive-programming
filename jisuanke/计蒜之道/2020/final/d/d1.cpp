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
constexpr int N = 2e5 + 10; 
//constexpr int M = 2e5 + 10;
constexpr int S = 0;
int n, q, a[N], b[N], c[N], fb[N]; 
vector <pII> vec;

struct NTT {
	ll qpow(ll base, ll n, ll mod) { ll res = 1; while (n) { if (n & 1) res = res * base % mod; base = base * base % mod; n >>= 1; } return res; }
	ll inv(ll a, ll mod) { return qpow(a, mod - 2, mod); } 
	//static const int m1 = 469762049, m2 = 998244353, m3 = 1004535809, g = 3;
//	static const ll M = 1ll * m1 * m2; 
	static const int g = 3;
	int fn, fl, rev[N], goal[N]; 
	int c[N], d[N], ans[3][N]; 
	void init(int n) { 
		fn = 1, fl = 0;
		while (fn <= n * 2) fn <<= 1, ++fl;
		for (int i = 0; i < fn; ++i) {
			rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (fl - 1));
		}
	}
	void work(int n, int *a, int opt, int mod) {
   		for (int i = 0; i < n; ++i)
   		    if (i < rev[i]) 
				swap(a[i], a[rev[i]]);
   		for (int k = 1; k < n; k <<= 1)
   		    for (int i = 0, wn = qpow(g, (mod - 1) / (k << 1), mod); i < n; i += (k << 1))
   		        for (int j = 0, w = 1, x, y; j < k; ++j, w = 1ll * w * wn % mod) {
   		            x = a[i + j];
					y = 1ll * w * a[i + j + k] % mod;
   		            a[i + j]= (x + y) % mod;
					a[i + j + k] = (x - y + mod) % mod;
   		        }
   		if (opt == -1) {
			ll Inv = inv(n, mod);
			a[0] = 1ll * a[0] * Inv % mod;
   		    for (int i = 1; i <= n / 2; ++i) {
   		        a[i] = 1ll * a[i] * Inv % mod;
   		        if (i != n - i) a[n - i] = 1ll * a[n - i] * Inv % mod;
   		        swap(a[i], a[n - i]);
   		    }
   		}
	}
	void gao(int *a, int *b, int n, int m) {
		init(max(n, m));
		copy(a, a + n + 1, c); copy(b, b + m + 1, d); 
		for (int i = n + 1; i <= fn; ++i) c[i] = d[i] = 0;
		work(fn, c, 1, mod); work(fn, d, 1, mod);
		for (int i = 0; i <= fn; ++i) goal[i] = 1ll * c[i] * d[i] % mod;
		work(fn, goal, -1, mod);
	}
}ntt;

void build() {
	ntt.gao(a, b, n, n);
	for (int i = 0; i <= n + n; ++i) {
		c[i] = ntt.goal[i];
		if (i) chadd(c[i], c[i - 1]);
	}
}

int query(int l, int r) {
	int res = c[r];
	if (l) chadd(res, mod - c[l - 1]);
	return res;
}

int gao(int x) {
	if (x < 0) return 0;
	int res = 0;
	for (auto &it : vec) {
		int p = it.fi, q = it.se;
		if (p > x) continue;
	//	dbg(p, q, x - p);
		chadd(res, mod + 1ll * q * fb[min(n, x - p)] % mod);
	}
	return res;
}

void run() {
	rd(n);
	for (int i = 0; i <= n; ++i) {
		rd(a[i]);
		chadd(a[i], 0);
		//dbg(i, a[i]);
	}
	for (int i = 0; i <= n; ++i) {
		rd(b[i]);
		chadd(b[i], 0);
		fb[i] = b[i];
	//	dbg(i, b[i]);
		if (i) chadd(fb[i], fb[i - 1]);
	}
	build();
	rd(q);
	vec.clear();
	for (int i = 1, op, x, y; i <= q; ++i) {
		rd(op, x, y);
		if (op == 2) {
			chadd(a[x], y);
			vec.push_back(pII(x, y));
		} else {
		//	dbg(op, x, y);
			if (SZ(vec) > S) {
				build();
				vec.clear();
			}
			int res = (query(x, y) + gao(y)) % mod;
			chadd(res, mod - gao(x - 1));   
			pt(res);
		}
	}
}

int main() {
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
