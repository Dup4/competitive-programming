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
constexpr int N = 1e6 + 10;
constexpr ll INF = 0x3f3f3f3f3f3f3f3f;

int n, m, q, s, id, pos[N]; 
struct Edge { int v, nx, w; }e[N * 8]; int h[N * 8]; 
inline void addedge(int u, int v, int w) { e[++*h] = {v, h[u], w}; h[u] = *h; }
struct SEG {
	struct node {
		int ls, rs;
		node() { ls = rs = 0; }
	}t[N << 3];
	int rt_in, rt_out;
	inline void init() { rt_in = rt_out = 0; } 
	inline int newnode() { ++id; t[id] = node(); return id; }  
	void build(int &rt, int l, int r, int op) {
		rt = newnode();
		if (l == r) {
			if (op == 1) {
				pos[l] = rt; 
			}
			return;
		}
		int mid = (l + r) >> 1;
		build(t[rt].ls, l, mid, op);
		build(t[rt].rs, mid + 1, r, op);  
		if (op == 1) {
			addedge(rt, t[rt].ls, 0);
			addedge(rt, t[rt].rs, 0);
		} else { 
			addedge(t[rt].ls, rt, 0);
			addedge(t[rt].rs, rt, 0);    
		}
	}
	void add(int id, int l, int r, int ql, int qr, int u, int w, int op) {
		if (l >= ql && r <= qr) {
			if (op == 1) {
				addedge(id, u, w); 
			} else {
				addedge(u, id, w);
			}
			return;	
		}
		int mid = (l + r) >> 1;
		if (ql <= mid) add(t[id].ls, l, mid, ql, qr, u, w, op);
		if (qr > mid) add(t[id].rs, mid + 1, r, ql, qr, u, w, op);
	}
	void addleaf(int rt_in, int rt_out, int l, int r) {
		if (l == r) {
			addedge(rt_in, rt_out, 0);  
			return;
		}
		int mid = (l + r) >> 1;
		addleaf(t[rt_in].ls, t[rt_out].ls, l, mid);
		addleaf(t[rt_in].rs, t[rt_out].rs, mid + 1, r);
	}
}seg;

void add(int a, int b, int c, int d, int w) {
	int p1 = ++id, p2 = ++id;
	seg.add(seg.rt_out, 1, n, a, b, p1, 0, 1);
	addedge(p1, p2, w);
	seg.add(seg.rt_in, 1, n, c, d, p2, 0, 0);
}

struct Dijkstra {
	struct node {
		int u; ll w;
		node() {}
		node(int u, ll w) : u(u), w(w) {}
		bool operator < (const node &other) const {
			return w > other.w;
		}
	};
    ll dis[N]; bool used[N];
	void gao() {
		for (int i = 1; i <= id; ++i) {
			dis[i] = INF;
			used[i] = 0;
		}
		dis[pos[s]] = 0;
		priority_queue <node> pq;
		pq.push(node(pos[s], 0));
		while (!pq.empty()) {
			int u = pq.top().u; pq.pop();
			if (used[u]) continue;
			used[u] = 1;
			for (int i = h[u]; i; i = e[i].nx) {
				int v = e[i].v, w = e[i].w;
				if (dis[v] > dis[u] + w) {
					dis[v] = dis[u] + w;
					pq.push(node(v, dis[v]));
				}
			}
		}
		for (int i = 1; i <= n; ++i) {
			if (dis[pos[i]] == INF) dis[pos[i]] = -1;
			printf("%lld\n", dis[pos[i]]);
		}
	}
}dij;

void run() {
	rd(n, m); 
	memset(h, 0, sizeof h); 
	seg.init(); 
	seg.build(seg.rt_in, 1, n, 1);
	seg.build(seg.rt_out, 1, n, 0);
	seg.addleaf(seg.rt_in, seg.rt_out, 1, n);
	for (int i = 1, u, v, w; i <= m; ++i) {
		rd(u, v, w);
		add(u, u, v, v, w);
	}	
	rd(q);
	for (int i = 1, op, u, l, r, w; i <= q; ++i) {
		rd(op);
		if (op == 1) {
			rd(u, l, r, w);
			add(u, u, l, r, w);
		} else {
			rd(l, r, u, w);
			add(l, r, u, u, w);
		}
	}
	s = 1;
	dij.gao();
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
