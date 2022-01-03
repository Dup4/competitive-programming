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
constexpr int N = 1e6 + 10; 
int n, m, f[N], g[N]; char a[N], b[N], s[N]; 

struct ExKMP {
	int Next[N];
	int extend[N];
	//下标从1开始
	void get_Next(char *s) {
		int lens = strlen(s + 1), p = 1, pos;
		Next[1] = lens;
		while (p + 1 <= lens && s[p] == s[p + 1]) ++p;
		Next[pos = 2] = p - 1;
		for (int i = 3; i <= lens; ++i) {
			int len = Next[i - pos + 1];
			if (len + i < p + 1) Next[i] = len;
			else {
				int j = max(p - i + 1, 0);
				while (i + j <= lens && s[j + 1] == s[i + j]) ++j;
				p = i + (Next[pos = i] = j) - 1; 
			}
		}
	}
	void work(char *s, char *t) {
		get_Next(t);
		int lens = strlen(s + 1), lent = strlen(t + 1), p = 1, pos;
		while (p <= lent && s[p] == t[p]) ++p;
		p = extend[pos = 1] = p - 1;
		for (int i = 2; i <= lens; ++i) {
			int len = Next[i - pos + 1];
			if (len + i < p + 1) extend[i] = len;
			else {
				int j = max(p - i + 1, 0);
				while (i + j <= lens && j <= lent && t[j + 1] == s[i + j]) ++j;
				p = i + (extend[pos = i] = j) - 1;
			}
		}
	}
}exkmp;

struct BIT {
    ll a[N];
	void init() { memset(a, 0, sizeof a); }
    int lowbit(int x) { return x & -x; }
    void add(int x, ll v) {
		++x;
        for (int i = x; i < N; i += lowbit(i))
            a[i] += v;
    }
    ll query(int x) {
		++x;
        ll ret = 0;
        for (int i = x; i > 0; i -= lowbit(i))
            ret += a[i];
        return ret;
    }
    ll query(int l, int r) { if (l > r) return 0; return query(r) - query(l - 1); }
}bit[2];

void run() {
	cin >> (a + 1) >> (b + 1) >> (s + 1);
	exkmp.get_Next(a);
	exkmp.work(a, s);
	memset(f, 0, sizeof f);
	for (int i = 1; i <= n; ++i) {
		f[i] = min(exkmp.extend[i], m - 1);
	}
	reverse(b + 1, b + 1 + n);
	reverse(s + 1, s + 1 + m);
	exkmp.get_Next(b);
	exkmp.work(b, s);
	memset(g, 0, sizeof g);
	for (int i = 1; i <= n; ++i) {
		g[n - i + 1] = min(exkmp.extend[i], m - 1);
	}
	bit[0].init();
	bit[1].init();
	ll ans = 0;
	int l = 1, r = 0;
	for (int i = 1; i <= n; ++i) {
		int _n = min(n, i + m - 2);
		while (r < _n) {
			bit[0].add(g[r + 1], 1);
			bit[1].add(g[r + 1], g[r + 1]); 
			++r;
		}
		while (l < i) {
			bit[0].add(g[l], -1);
			bit[1].add(g[l], -g[l]);
			++l;
		}
		int x = f[i] - m + 1;
		ans += 1ll * x * bit[0].query(-x, m);
		ans += bit[1].query(-x, m);
	}
	pt(ans);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	cout << fixed << setprecision(20);
	while (cin >> n >> m) run(); 
//	while (cin >> n) run();
//    for (int kase = 1; kase <= _T; ++kase) {
//        cout << "Case #" << kase << ":\n";
//        run();
//    }
	return 0;
}
