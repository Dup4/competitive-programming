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
constexpr int mod = 998244353, phi = mod - 1;
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
inline ll qpow(ll base, ll n, ll mod = 998244353) { ll res = 1; while (n) { if (n & 1) res = res * base % mod; base = base * base % mod; n >>= 1; } return res; }
//head
constexpr int N = 4e5 + 10;
int n, m, f[N], a[N], b[N];
ll sqr2 = 116195171; 

struct NTT {
	ll qpow(ll base, ll n, ll mod) { ll res = 1; while (n) { if (n & 1) res = res * base % mod; base = base * base % mod; n >>= 1; } return res; }
	ll inv(ll a, ll mod) { return qpow(a, mod - 2, mod); } 
	int fn, fl, rev[N << 2]; 
	static const int m1 = 469762049, m2 = 998244353, m3 = 1004535809, g = 3;
	static const ll M = 1ll * m1 * m2; 
	int c[N], d[N], ans[3][N], goal[N]; 
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
	//多组数据记得清空c[], d[]
	//满足模数可以分解成p = a2^k + 1形式
	//此处的n, m表示[0, n],[0, m]
	void gao(int *a, int *b, int n, int m) {
		init(max(n, m));
		copy(a, a + n + 1, c); copy(b, b + m + 1, d); work(fn, c, 1, mod); work(fn, d, 1, mod);
		for (int i = 0; i <= fn; ++i) goal[i] = 1ll * c[i] * d[i] % mod;
		work(fn, goal, -1, mod);
	}
	
}ntt;

void run() {
	m = 1e5;
	memset(a, 0, sizeof a);
	memset(b, 0, sizeof b);
	memset(f, 0, sizeof f);
	for (int i = 0, x; i < n; ++i) {
		cin >> x;
		++f[x];
	}
	for (int i = 0; i <= m; ++i) {
		ll rt = qpow(sqr2, (-1ll * i * i % phi + phi) % phi);
		a[i] = 1ll * f[i] * rt % mod;
		b[i] = a[i];
	}
	ntt.gao(a, b, m, m);
	ll res = 0;
	for (int i = 0; i <= m * 2; ++i) { 
		chadd(res, qpow(sqr2, 1ll * i * i % phi) * ntt.goal[i] % mod); 
	}
	pt(res);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	cout << fixed << setprecision(20);
	while (cin >> n) run();
	return 0;
}
