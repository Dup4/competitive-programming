#include <bits/stdc++.h>
using namespace std;
#define debug(...) { printf("#  "); printf(__VA_ARGS__); puts(""); }
#define fi first
#define se second
#define endl "\n" 
using ll = long long;
using pII = pair <int, int>;
using pLL = pair <ll, ll>;
using VI = vector <int>;
using VL = vector <ll>;
constexpr int mod = 1e9 + 7;
template <class T1, class T2> inline void chadd(T1 &x, T2 y) { x += y; if (x >= mod) x -= mod; else if (x < 0) x += mod; } 
template <class T1, class T2> inline void chmax(T1 &x, T2 y) { if (x < y) x = y; }
template <class T1, class T2> inline void chmin(T1 &x, T2 y) { if (x > y) x = y; }
inline int rd() { int x; cin >> x; return x; }
template <class T> inline void rd(T &x) { cin >> x; }
template <class T> inline void rd(vector <T> &vec) { for (auto &it : vec) cin >> it; }
template <class T> inline void out(T s) { cout << s << "\n"; }
template <class T> inline void out(vector <T> &vec) { for (auto &it : vec) cout << it << " "; cout << endl; } 
inline ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }
inline ll qpow(ll base, ll n) { ll res = 1; while (n) { if (n & 1) res = res * base % mod; base = base * base % mod; n >>= 1; } return res; }
constexpr int N = 5e5 + 10;
int n, m, a[N], pre[N]; ll ans[N];
struct BIT {
    ll a[N];
	inline void init() { memset(a, 0, sizeof a); }
    inline int lowbit(int x) { return x & -x; }
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
	//a[i]表示i这个数有a[i]个，相当于权值BIT，查询第k大。
    int kth(ll k) {
        int p = 0;
        for (int lim = 1 << 20; lim; lim /= 2)
            if (p + lim < N && a[p + lim] < k) {
                p += lim;
                k -= a[p];
            }
        return p + 1;
    }
    ll query(int l, int r) { if (l > r) return 0; return query(r) - query(l - 1); }
    void add(int l, int r, ll v) { if (l > r) return; add(l, v); add(r + 1, -v); }
}bit;
vector <vector<pII>> qvec;
void run() {
	bit.init();
	qvec.clear(); qvec.resize(n + 1);
	for (int i = 1; i <= n; ++i) cin >> a[i];
	memset(pre, 0, sizeof pre);
	memset(ans, 0, sizeof ans);
	for (int i = 1, l, r; i <= m; ++i) {
		cin >> l >> r;
		qvec[r].push_back(pII(l, i));
	}
	for (int i = 1; i <= n; ++i) {
		bit.add(pre[a[i]] + 1, i, a[i]);
		pre[a[i]] = i;
		for (auto &it : qvec[i]) 
			ans[it.se] = bit.query(it.fi);
	}
	for (int i = 1; i <= m; ++i) 
		cout << ans[i] << endl;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	cout << fixed << setprecision(20);
	while (cin >> n >> m) run();
	return 0;
}
