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
template <class T1, class T2> inline void chadd(T1 &x, T2 y) { x += y; while (x >= mod) x -= mod; while (x < 0) x += mod; } 
template <class T1, class T2> inline void chmax(T1 &x, T2 y) { if (x < y) x = y; }
template <class T1, class T2> inline void chmin(T1 &x, T2 y) { if (x > y) x = y; }
inline int rd() { int x; cin >> x; return x; }
template <class T> inline void rd(T &x) { cin >> x; }
template <class T> inline void rd(vector <T> &vec) { for (auto &it : vec) cin >> it; }
//template <class T> inline void out(T s) { cout << s << "\n"; }
//template <class T> inline void out(vector <T> &vec) { for (auto &it : vec) cout << it << " "; cout << endl; } 
inline ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }
inline ll qpow(ll base, ll n) { ll res = 1; while (n) { if (n & 1) res = res * base % mod; base = base * base % mod; n >>= 1; } return res; }
constexpr int N = 2e5 + 10;
constexpr int S = 350;
int n, m, q, d[N], in[N], out[N], w[N], e[N][2];  
inline ll get(int x) { return 1ll * in[x] * out[x]; }
vector <vector<int>> G;
struct SEG {
	struct node {
		int ls, rs, lazy, num, b;
		// a ab a out b in
		// b b - a
		ll a;
		inline ll getf(int x) {
			return 1ll * x * x;
		}
		void up(ll x) {
			a += b * x - getf(lazy) * num;
			b += x * num * -2;
			lazy += x;
		}
		node() { ls = rs = a = b = num = lazy = 0; } 
	}t[N * 40];
	int rt[N], tot;
	void init() { tot = 0; memset(rt, 0, sizeof rt); }
	void down(int id) {
		int &lazy = t[id].lazy;
		int ls = t[id].ls, rs = t[id].rs;
		if (!lazy) return;
		if (ls) t[ls].up(lazy);
		if (rs) t[rs].up(lazy);
		lazy = 0;
	}
	void add(node &x, node y) {
		x.a += y.a;
		x.b += y.b;
		x.num += y.num;
	}
	void up(int id) {
		t[id].a = t[id].b = t[id].num = 0;
		int ls = t[id].ls, rs = t[id].rs;
		if (ls) add(t[id], t[ls]);
		if (rs) add(t[id], t[rs]);
	}	
	void Set(int &now, int l, int r, int pos, int In, int Out, int num) {
		if (!now) now = ++tot, t[now] = node();
		if (l == r) {
			t[now].a = 1ll * In * Out;
			t[now].b = Out - In;
			t[now].num = num;
			return;
		}
		int mid = (l + r) >> 1;
		down(now);
		if (pos <= mid) Set(t[now].ls, l, mid, pos, In, Out, num);
		else Set(t[now].rs, mid + 1, r, pos, In, Out, num);
		up(now);
	}
	void update(int &now, int l, int r, int ql, int qr, int v) {
		if (ql > qr) return;
		if (!now) return; 
		if (l >= ql && r <= qr) {
			t[now].up(v);
			return;
		}
		int mid = (l + r) >> 1;
		down(now);
		if (ql <= mid) update(t[now].ls, l, mid, ql, qr, v);
		if (qr > mid) update(t[now].rs, mid + 1, r, ql, qr, v);
		up(now);
	} 
	ll query(int &now, int l, int r, int ql, int qr) {
		if (!now || ql > qr) return 0;
		if (l >= ql && r <= qr) return t[now].a;
		int mid = (l + r) >> 1;
		down(now);
		ll res = 0;
		if (ql <= mid) res += query(t[now].ls, l, mid, ql, qr);
		if (qr > mid) res += query(t[now].rs, mid + 1, r, ql, qr);
		return res;
	}
}seg;
void run() {
	memset(d, 0, sizeof d); 
	memset(in, 0, sizeof in);
	memset(out, 0, sizeof out);
	G.clear(); G.resize(n + 1);
	for (int i = 1; i <= n; ++i) w[i] = i;
	for (int i = 1; i <= m; ++i) {
		cin >> e[i][0] >> e[i][1];
		++d[e[i][0]]; ++d[e[i][1]];
	}
	for (int i = 1; i <= m; ++i) {
		int u = e[i][0], v = e[i][1];
		if (d[u] <= S || (d[u] > S && d[v] > S)) {
			G[u].push_back(v);
			G[v].push_back(u);
		} 
	}	
	seg.init(); 
	ll res = 0;
	for (int i = 1; i <= m; ++i) {
		int u = e[i][0], v = e[i][1];
		if (u > v) ++out[u], ++in[v];
		else ++in[u], ++out[v];
	}
	for (int i = 1; i <= n; ++i) res += get(i);
	for (int u = 1; u <= n; ++u) if (d[u] <= S) {
		for (auto &v : G[u]) if (d[v] > S) {
			seg.Set(seg.rt[v], 1, n + m, w[u], in[u], out[u], 1);   
		}
	}
	cin >> q;
	cout << res << endl;
	int u;
	for (int _q = 1; _q <= q; ++_q) {
		cin >> u;
		//小点
		if (d[u] <= S) {
			out[u] = 0; in[u] = 0;
			for (auto &v : G[u]) {
				if (w[v] > w[u]) ++in[u];
				else ++out[u];
			}
			res -= get(u); 
			out[u] = d[u]; in[u] = 0; 
			for (auto &v : G[u]) {
				if (d[v] > S) {
					seg.Set(seg.rt[v], 1, n + m, w[u], 0, 0, 0);
					seg.Set(seg.rt[v], 1, n + m, n + _q, in[u], out[u], 1); 
				} 
				if (w[v] > w[u]) {
					res -= get(v);
					--out[v]; ++in[v];
					res += get(v);
				}	
			}
			w[u] = n + _q;
		} else {
			res -= get(u);
			out[u] = d[u]; in[u] = 0;
			for (auto &v : G[u]) {
				if (w[v] > w[u]) {
					res -= get(v);
					--out[v]; ++in[v];
					res += get(v);
				}
			}
			res -= seg.query(seg.rt[u], 1, n + m, 1, n + m);
			seg.update(seg.rt[u], 1, n + m, w[u] + 1, n + m, 1);
			res += seg.query(seg.rt[u], 1, n + m, 1, n + m);
			w[u] = n + _q;
		}
		cout << res << endl;
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	cout << fixed << setprecision(20);
	while (cin >> n >> m) run();
	return 0;
}
