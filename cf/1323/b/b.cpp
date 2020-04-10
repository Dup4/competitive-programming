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
constexpr int N = 4e4 + 10; 
int n, m, k, a[N], b[N]; ll Sa[N], Sb[N]; 

void add(ll *a, int l, int r, int x) {
	if (l <= r) {
		a[l] += x;
		a[r + 1] -= x;
	}
}

void run() {
	for (int i = 1; i <= n; ++i) rd(a[i]);
	for (int i = 1; i <= m; ++i) rd(b[i]);
	memset(Sa, 0, sizeof Sa);
	memset(Sb, 0, sizeof Sb);
	int tot = 0;
	for (int i = 1; i <= n; ++i) {
		if (a[i]) ++tot;
		else tot = 0;
		add(Sa, 1, tot, 1);
	}
	tot = 0;
	for (int i = 1; i <= m; ++i) {
		if (b[i]) ++tot;
		else tot = 0;
		add(Sb, 1, tot, 1);
	}
	for (int i = 1; i <= n; ++i) Sa[i] += Sa[i - 1];
	for (int i = 1; i <= m; ++i) Sb[i] += Sb[i - 1];
	ll res = 0;
	for (int i = 1; i <= n; ++i) {
		if (Sa[i] && k % i == 0 && k / i <= m) {
			res += Sa[i] * Sb[k / i];
		}
	}
	pt(res);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	cout << fixed << setprecision(20);
	while (cin >> n >> m >> k) run();
//    for (int kase = 1; kase <= _T; ++kase) {
//        cout << "Case #" << kase << ":\n";
//        run();
//    }
	return 0;
}
