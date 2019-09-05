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
constexpr int INF = 0x3f3f3f3f;
int n, q, a[N]; 
struct SEG {
	struct node {
		int Min[2];
		node() { Min[0] = Min[1] = INF; }
		node operator + (const node &other) const {
			node res = node();
			if (Min[0] < other.Min[0]) {
				res.Min[0] = Min[0];
				res.Min[1] = other.Min[0];
			} else {
				res.Min[0] = other.Min[0];
				res.Min[1] = Min[0];
			}
			res.Min[1] = min(res.Min[1], min(Min[1], other.Min[1]));
			return res;
		}
	}t[N << 2], res; 
	void build(int id, int l, int r) {
		t[id] = node();
		if (l == r) return;
		int mid = (l + r) >> 1;
		build(id << 1, l, mid);
		build(id << 1 | 1, mid + 1, r);
	}
	void update(int id, int l, int r, int pos, int v) {
		if (l == r) {
			t[id].Min[0] = v;
			t[id].Min[1] = INF;
			return;
		}
		int mid = (l + r) >> 1;
		if (pos <= mid) update(id << 1, l, mid, pos, v);
		else update(id << 1 | 1, mid + 1, r, pos, v);
		t[id] = t[id << 1] + t[id << 1 | 1];
	}
	void query(int id, int l, int r, int ql, int qr) {
		if (l >= ql && r <= qr) {
			res = res + t[id];
			return;
		}
		int mid = (l + r) >> 1;
		if (ql <= mid) query(id << 1, l, mid, ql, qr);
		if (qr > mid) query(id << 1 | 1, mid + 1, r, ql, qr);
	}
}seg[10];
inline void up(int x, int id) {
	int bk = x;
	for (int i = 0; i < 9; ++i) {
		if (x % 10) seg[i].update(1, 1, n, id, bk);
		else seg[i].update(1, 1, n, id, INF);
		x /= 10;
	}
}
inline int query(int l, int r) {
	int res = INF * 2;
	for (int i = 0; i < 9; ++i) {
		seg[i].res = SEG::node();
		seg[i].query(1, 1, n, l, r);
		int A = seg[i].res.Min[0], B = seg[i].res.Min[1];
		if (A < INF && B < INF) res = min(res, A + B);
	}
	if (res == INF * 2) res = -1;
	return res;
}
void run() {
	for (int i = 1; i <= n; ++i) cin >> a[i];
	for (int i = 0; i < 9; ++i) seg[i].build(1, 1, n);
	for (int i = 1; i <= n; ++i) up(a[i], i);
	for (int i = 1, op, x, y; i <= q; ++i) {
		cin >> op >> x >> y;
		if (op == 1) {
			a[x] = y;
			up(a[x], x);
		} else cout << query(x, y) << endl;
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	cout << fixed << setprecision(20);
	while (cin >> n >> q) run();
	return 0;
}
