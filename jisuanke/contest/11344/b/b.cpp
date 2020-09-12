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
constexpr int N = 3e5 + 10; 
int n, m;
ll b[N], w[N], f[N], Sb[N], Sw[N];

struct E {
	int t, l, r; ll c;
	E() {}
	void scan() { rd(t, l, r, c); }
	bool operator < (const E &other) const { return l < other.l; }
}e[N];

void run() {
	rd(n, m);
	for (int i = 1; i <= n; ++i) rd(b[i]), Sb[i] = Sb[i - 1] + b[i];
	for (int i = 1; i <= n; ++i) rd(w[i]), Sw[i] = Sw[i - 1] + w[i];
	for (int i = 1; i <= m; ++i) e[i].scan();
	memset(f, 0, sizeof f);
	sort(e + 1, e + 1 + m);
	int pos = 1;
	for (int i = 1; i <= n; ++i) {
		f[i] = max(b[i], w[i]) + f[i - 1];
		if (pos <= m && e[pos].r == i) {
			int t = e[pos].t, l = e[pos].l, r = e[pos].r;
			ll c = e[pos].c;
			ll sum = 0;
			if (t == 1) {
				sum = Sb[r] - Sb[l - 1];
			} else {
				sum = Sw[r] - Sw[l - 1];
			}
			chmax(f[i], f[l - 1] + sum + c);
			++pos;
		}
	}
	pt(f[n]);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	cout << fixed << setprecision(20);
	int _T = 1;
	while (_T--) run(); 
//    for (int kase = 1; kase <= _T; ++kase) {
//        cout << "Case #" << kase << ": ";
//        run();
//    }
//	while (cin >> n) run();
//	run();
	return 0;
}
