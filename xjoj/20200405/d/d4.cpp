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
constexpr int N = 2e7 + 10;
ll n;

inline ll lowbit(ll x) { return x & -x; } 

int pri[N], check[N], ptot, _h[N]; 
int f[N], F[N];
void sieve_gao(int n, int opt = 0) { 
	memset(check, 0, sizeof (check[0]) * (n + 5)); 
	ptot = 0;
	f[1] = 1;
	_h[1] = 1;
	for (int i = 2; i <= n; ++i) {
		if (!check[i]) {
			pri[++ptot] = i;
			f[i] = (1 + lowbit(i)) % mod;
			_h[i] = i;
		}
		for (int j = 1; j <= ptot; ++j) {    
			if (1ll * i * pri[j] > n) break;
			check[i * pri[j]] = 1;  
		    if (i % pri[j] == 0) {
				_h[i * pri[j]] = _h[i] * pri[j];
				if (i / _h[i] == 1) f[i * pri[j]] = (f[i] + lowbit(_h[i * pri[j]])) % mod;
				else f[i * pri[j]] = 1ll * f[i / _h[i]] * f[_h[i * pri[j]]] % mod;
				break;
			} else {
				_h[i * pri[j]] = pri[j];
				f[i * pri[j]] = 1ll * f[i] * f[pri[j]] % mod;	
			}	
		}
	}
	if (opt) for (int i = 1; i <= n; ++i) F[i] = (F[i - 1] + f[i]) % mod;
}

int id1[N << 1], id2[N << 1], m, blk;
ll w[N << 1]; int h[N << 1]; 

int S(ll x, int y) {
	if (x <= 1 || pri[y] > x) return 0;
	int k = (x <= blk) ? id1[x] : id2[n / x];
	int ret = (1ll * h[k] - (2ll * (y - 1) % mod) + mod) % mod;
	if (y == 1) chadd(ret, 1);
	for (int i = y; i <= ptot && 1ll * pri[i] * pri[i] <= x; ++i) {
		ll t1 = pri[i], t2 = 1ll * pri[i] * pri[i];
		ll pre = 2;
		if (i == 1) ++pre;
		for (int e = 1; t2 <= x; ++e, t1 = t2, t2 *= pri[i]) {
			ll tmp = lowbit(t2);
			ret = (ret + pre * S(x / t1, i + 1) % mod + pre + tmp) % mod;
			chadd(pre, tmp);
		}
	}
	return ret;
}

inline int gao(ll n) {
	m = 0;
	blk = 5e5;
//	blk = pow(n, 3.0 / 4);
	sieve_gao(blk);
	for (ll i = 1, j; i <= n; i = j + 1) {
		j = n / (n / i);
		w[++m] = n / i;
		h[m] = 2ll * (w[m] - 1) % mod;
		if (w[m] <= blk) {
			id1[w[m]] = m; 
		} else {
			id2[n / w[m]] = m;
		}
	}	
	for (int j = 1; j <= ptot; ++j) {
		for (int i = 1; i <= m && 1ll * pri[j] * pri[j] <= w[i]; ++i) {
			int k = (w[i] / pri[j] <= blk) ? id1[w[i] / pri[j]] : id2[n / (w[i] / pri[j])];
			h[i] = (1ll * h[i] - (1ll * h[k] - 2ll * (j - 1) % mod + mod) + mod) % mod;
		}
	}
	return (S(n, 1) + 1) % mod;
}

void run() {
	rd(n);
	int limit = 2e6;
	if (n <= limit) {
		sieve_gao(n, 1);
		pt(F[n]);
	} else {
		pt(gao(n));
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	cout << fixed << setprecision(20);
	run();
//    for (int kase = 1; kase <= _T; ++kase) {
//        cout << "Case #" << kase << ":\n";
//        run();
//    }
	return 0;
}
