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
constexpr int N = 1e5 + 10; 
int n, q, a[N], f[N]; 

struct BIT {
    ll a[N];
	void init() { memset(a, 0, sizeof a); }
    int lowbit(int x) { return x & -x; }
    void add(int x, ll v) {
        for (int i = x; i < N; i += lowbit(i))
            a[i] += v;
    }
    ll query(int x) {
        ll ret = 0;
        for (int i = x; i > 0; i -= lowbit(i))
            ret += a[i];
        return ret;
    }
    ll query(int l, int r) { if (l > r) return 0; return query(r) - query(l - 1); }
}bit;

void run() {
	bit.init();
	for (int i = 1; i <= n; ++i) rd(a[i]), bit.add(i, a[i]);
	f[1] = 1;
	for (int i = 2; i <= n; ++i) {
		if (a[i] < a[i - 1]) f[i] = i;
		else f[i] = f[i - 1];
	}
	rd(q);
	while (q--) {
		static int x, y;
		rd(x, y);
		ll ans = bit.query(max(f[y], y - x + 1), y);
		if (y - x + 1 < f[y]) ans += 1ll * a[f[y]] * (f[y] - y + x - 1);
		pt(ans);	
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	cout << fixed << setprecision(20);
	while (cin >> n) run();
	return 0;
}
