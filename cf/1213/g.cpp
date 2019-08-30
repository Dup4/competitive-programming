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
constexpr int N = 2e5 + 10;
int n, q, fa[N], sze[N];
struct Edge {
	int u, v, w;
	void scan() { cin >> u >> v >> w; }
	bool operator < (const Edge &other) const {
		return w < other.w;
	}
}e[N];
pII qrr[N]; 
ll res, ans[N];
int find(int x) {
	return !fa[x] ? x : fa[x] = find(fa[x]);
}
inline ll f(ll x) { return x * (x - 1); }
inline void merge(int x, int y) {
	x = find(x), y = find(y);
	if (x != y) {
		res -= f(sze[x]);
		res -= f(sze[y]);
		if (sze[x] > sze[y]) swap(x, y);
		fa[x] = y;
		sze[y] += sze[x];
		res += f(sze[y]);
	}
}
void run() {
	for (int i = 1; i <= n; ++i) {
		fa[i] = 0;
		sze[i] = 1;
	}
	for (int i = 1; i < n; ++i) {
		e[i].scan();
	}
	sort(e + 1, e + n);
	for (int i = 1; i <= q; ++i) {
		cin >> qrr[i].fi;
		qrr[i].se = i;
	}
	sort(qrr + 1, qrr + 1 + q, [&](pII x, pII y) {
		return x.fi < y.fi;		
	});
	res = 0;
	int pos = 1;
	for (int i = 1; i <= q; ++i) {
		while (pos < n && e[pos].w <= qrr[i].fi) {
			merge(e[pos].u, e[pos].v);
			++pos;
		}
		ans[qrr[i].se] = res;
	}
	for (int i = 1; i <= q; ++i)
		cout << ans[i] / 2 << " \n"[i == q];
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	cout << fixed << setprecision(20);
	while (cin >> n >> q) run();
	return 0;
}
