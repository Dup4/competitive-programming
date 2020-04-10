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
constexpr int N = 5e5 + 10; 
int n, k, m, l[N], r[N], x[N];  
ll sum[N], f[N]; int one[N], pre[N];

ll calc(int k) {
	memset(sum, 0, sizeof sum);
	memset(f, 0, sizeof f);
	memset(one, 0, sizeof one);
	memset(pre, 0, sizeof pre);
	for (int i = 1; i <= m; ++i) {
		if ((x[i] >> k) & 1) {
			++one[l[i]]; --one[r[i] + 1];
		} else {
			chmax(pre[r[i] + 1], l[i]);
		}
	}
	for (int i = 1; i <= n + 1; ++i) chmax(pre[i], pre[i - 1]);
	sum[0] = f[0] = 1;
	for (int i = 1; i <= n + 1; ++i) {
		one[i] += one[i - 1];
		if (one[i]) f[i] = 0;
		else {
			f[i] = sum[i - 1];
			if (pre[i]) chadd(f[i], mod - sum[pre[i] - 1]);
		}
		sum[i] = sum[i - 1];
		chadd(sum[i], f[i]);
	}
	return f[n + 1];
}

void run() { 
	for (int i = 1; i <= m; ++i) {
		rd(l[i], r[i], x[i]);
	}
	ll res = 1;
	for (int i = 0; i < k; ++i) {
		res = res * calc(i) % mod;
	}
	pt(res);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	cout << fixed << setprecision(20);
	while (cin >> n >> k >> m) run();
//    for (int kase = 1; kase <= _T; ++kase) {
//        cout << "Case #" << kase << ":\n";
//        run();
//    }
	return 0;
}
