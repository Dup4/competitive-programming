#include <bits/stdc++.h>
#define debug(...) { printf("#  "); printf(__VA_ARGS__); puts(""); }
#define fi first
#define se second
#define endl "\n" 
using namespace std;
using db = double;
using ll = long long;
using ull = unsigned long long; 
using pII = pair <int, int>;
using pLL = pair <ll, ll>;
constexpr ll mod = 1e9 + 7;
template <class T1, class T2> inline void chadd(T1 &x, T2 y) { x += y; while (x >= mod) x -= mod; while (x < 0) x += mod; } 
template <class T1, class T2> inline void chmax(T1 &x, T2 y) { if (x < y) x = y; }
template <class T1, class T2> inline void chmin(T1 &x, T2 y) { if (x > y) x = y; }
inline int rd() { int x; cin >> x; return x; }
template <class T> inline void rd(T &x) { cin >> x; }
template <class T> inline void rd(vector <T> &vec) { for (auto &it : vec) cin >> it; }
inline void pt() { cout << endl; }
template <class T, class... Ts> void pt(const T& arg, const Ts&... args) { cout << arg << " "; pt(args...); }
template <class T> inline void pt(const T &s) { cout << s << "\n"; }
template <class T> inline void pt(const vector <T> &vec) { for (auto &it : vec) cout << it << " "; cout << endl; } 
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }
inline ll qpow(ll base, ll n) { ll res = 1; while (n) { if (n & 1) res = res * base % mod; base = base * base % mod; n >>= 1; } return res; }
constexpr int N = 1e5 + 10;
int n; char d[N]; ll inv, bit[N], f[N], g[N], h[N];  
inline ll getS(ll *S, int l, int r) {
	if (l > r) return 0;
	ll res = S[r];
	if (l) chadd(res, -S[l - 1]);
	return res;
}
struct SEG {
	struct node {
		ll sum, lazy;
		node() { sum = 0; lazy = 1; }
		void up(ll x) {
			sum = sum * x % mod;
			lazy = lazy * x % mod;
		}
		node operator + (const node &other) const {
			node res = node();
			res.sum = (sum + other.sum) % mod;
			return res;
		}
	}t[N << 2];
	void build(int id, int l, int r) {
		t[id] = node();
		if (l == r) {
			t[id].sum = h[l];
			return;
		}
		int mid = (l + r) >> 1;
		build(id << 1, l, mid);
		build(id << 1 | 1, mid + 1, r);
		t[id] = t[id << 1] + t[id << 1 | 1];
	}
	void down(int id) {
		ll &lazy = t[id].lazy;
		t[id << 1].up(lazy);
		t[id << 1 | 1].up(lazy);
		lazy = 1;
	}
	void update(int id, int l, int r, int ql, int qr, ll v) {
		if (ql > qr) return;
		if (l >= ql && r <= qr) {
			t[id].up(v);
			return;
		}
		int mid = (l + r) >> 1;
		down(id);
		if (ql <= mid) update(id << 1, l, mid, ql, qr, v);
		if (qr > mid) update(id << 1 | 1, mid + 1, r, ql, qr, v);
		t[id] = t[id << 1] + t[id << 1 | 1];
	}
	ll query(int id, int l, int r, int ql, int qr) {
		if (ql > qr) return 0;
		if (l >= ql && r <= qr) return t[id].sum;
		int mid = (l + r) >> 1;
		down(id);
		ll res = 0;
		if (ql <= mid) chadd(res, query(id << 1, l, mid, ql, qr));
		if (qr > mid) chadd(res, query(id << 1 | 1, mid + 1, r, ql, qr));
		return res;
	}
}seg;
void run() {
	cin >> (d + 1);
	f[0] = g[0] = 0;
	for (int i = 1; i <= n; ++i) {
		f[i] = 1ll * (d[i] - '0') * getS(bit, n - i, n - i) % mod * (i - 1) % mod;
		g[i] = 1ll * (d[i] - '0') * getS(bit, n - i, n - i) % mod;   
		chadd(f[i], f[i - 1]);
		chadd(g[i], g[i - 1]);
		h[i] = 1ll * (d[i] - '0') * getS(bit, i - 1, n - 1) % mod;
	//	pt(i, h[i]);
	}
	seg.build(1, 1, n);
	ll res = 0, tot = f[n], pre = 0; 	
	for (int i = 1; i <= n; ++i) {
		chadd(res, pre * getS(bit, n - i + 1, n - i + 1) % mod * (n - i + 1) % mod);
		chadd(res, seg.query(1, 1, n, i, n)); 
		chadd(res, tot);
	//	pt(res, pre * getS(bit, n - i + 1, n - i + 1) % mod * (n - i + 1) % mod, seg.query(1, 1, n, i, n), tot);
		chadd(tot, -getS(g, i + 1, n));
		seg.update(1, 1, n, i + 1, n, inv);
		pre = (pre * 10 + d[i] - '0') % mod; 
	}
	pt(res);
}

int main() {
	bit[0] = 1;
	for (int i = 1; i < N; ++i) bit[i] = bit[i - 1] * 10 % mod;
	for (int i = 1; i < N; ++i) chadd(bit[i], bit[i - 1]);
	inv = qpow(10, mod - 2);
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	cout << fixed << setprecision(20);
	while (cin >> n) run();
	return 0;
}
