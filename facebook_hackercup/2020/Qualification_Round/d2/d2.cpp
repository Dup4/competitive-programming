#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define SZ(x) ((int)(x).size())
#define mkp make_pair
#define all(x) (x).begin(), (x).end()
#define endl "\n" 
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
constexpr int N = 4e6 + 10; 
constexpr ll INF = 0x3f3f3f3f3f3f3f3f;
int n, m, a, b, vis[N]; ll c[N];

struct Graph {
	struct E { int to, nx, w; }e[N << 1]; int h[N], cnt;
	void init(int n) { for (int i = 0; i <= n; ++i) h[i] = -1; cnt = -1; }
	void addedge(int u, int v, int w = 0) { e[++cnt] = { v, h[u], w}; h[u] = cnt; } 
}G;

namespace HLD {
	int fa[N], deep[N], dis[N], sze[N], son[N], top[N], in[N], fin[N], out[N]; 
	void dfs(int u) {
		//dbg(u);
		sze[u] = 1; son[u] = 0;
		for (int i = G.h[u]; ~i; i = G.e[i].nx) {
			int v = G.e[i].to, w = G.e[i].w;
			if (v == fa[u]) continue;
			fa[v] = u; deep[v] = deep[u] + 1; dis[v] = dis[u] + w;
			dfs(v);
			sze[u] += sze[v];
			if (!son[u] || sze[v] > sze[son[u]]) son[u] = v; 
		}
	}
	void gettop(int u, int tp) {
	//	dbg(u, tp);
		in[u] = ++*in; fin[*in] = u;
		top[u] = tp;
		if (son[u]) gettop(son[u], tp);
		for (int i = G.h[u]; ~i; i = G.e[i].nx) {
			int v = G.e[i].to;
			if (v != son[u] && v != fa[u]) {
				gettop(v, v);
			}
		}
		out[u] = *in;
	}
	void init(int rt) {
		fa[rt] = rt;
		dis[rt] = 0;
	    deep[rt] = 1;	
		*in = 0;
		dfs(rt);
		gettop(rt, rt);
	} 
	int querylca(int u, int v) {
		while (top[u] != top[v]) {
			if (deep[top[u]] < deep[top[v]]) {
				swap(u, v);
			}
			u = fa[top[u]];
		}
		if (deep[u] > deep[v]) swap(u, v); 
		return u;
	}
	int querydis(int u, int v) { return dis[u] + dis[v] - 2 * dis[querylca(u, v)]; }
}

struct SEG {
	struct node {
		ll Min;
		node() { Min = INF; }
		node operator + (const node &other) const {
			node res = node();
			res.Min = min(Min, other.Min);
			return res;
		}
	}t[N << 2];
	void build(int id, int l, int r) {
		t[id] = node();
		if (l == r) return;
		int mid = (l + r) >> 1;
		build(id << 1, l, mid);
		build(id << 1 | 1, mid + 1, r);
		t[id] = t[id << 1] + t[id << 1 | 1];
	}
	void update(int id, int l, int r, int pos, ll v) {
		if (l == r) {
			chmin(t[id].Min, v);
			return;
		}
		int mid = (l + r) >> 1;
		if (pos <= mid) update(id << 1, l, mid, pos, v);
		else update(id << 1 | 1, mid + 1, r, pos, v);
		t[id] = t[id << 1] + t[id << 1 | 1];
	}
	ll query(int id, int l, int r, int ql, int qr) {
	//	dbg(id, l, r, ql, qr);
		if (l >= ql && r <= qr) return t[id].Min;
		int mid = (l + r) >> 1;
		ll Min = INF;
		if (ql <= mid) chmin(Min, query(id << 1, l, mid, ql, qr));
		if (qr > mid) chmin(Min, query(id << 1 | 1, mid + 1, r, ql, qr));
		return Min;
	}
}seg;

void viss() {
	memset(vis, 0, sizeof vis);
	int u = a, v = b;
	vis[u] = 1; vis[v] = 1;
	while (u != v) {
		if (HLD::deep[u] > HLD::deep[v]) {
			u = HLD::fa[u];
			vis[u] = 1;
		} else {
			v = HLD::fa[v];
			vis[v] = 1;
		}
	}
}

void dfs1(int u, int fa, int rt) {
	if (c[u]) {
		int dis = HLD::deep[u] - HLD::deep[rt];
		ll cost = seg.query(1, 1, n, max(1, HLD::deep[u] - m), HLD::deep[u]) + c[u];
		int _dep = max(1, HLD::deep[rt] - dis);
		seg.update(1, 1, n, _dep, cost);
	}
	for (int i = G.h[u]; ~i; i = G.e[i].nx) {
		int v = G.e[i].to;
		if (v == fa) continue;
		dfs1(v, u, rt);
	}
}

void dfs(int u, int fa) {
//	dbg(u, fa);
	int son = -1;
	for (int i = G.h[u]; ~i; i = G.e[i].nx) {
		int v = G.e[i].to;
		if (v == fa) continue;
		if (vis[v]) son = v;
		else dfs1(v, u, u);
	}
	if (c[u]) {
		ll cost = seg.query(1, 1, n, max(1, HLD::deep[u] - m), HLD::deep[u]) + c[u];
		seg.update(1, 1, n, HLD::deep[u], cost);
	}
	if (son != -1) dfs(son, u);
}

void run() {
	rd(n, m, a, b);
	G.init(n);
	for (int i = 1, p; i <= n; ++i) {
		rd(p, c[i]);
		if (p) {
	//		dbg(i, p);
			G.addedge(i, p);
			G.addedge(p, i);
		}
	}
	HLD::init(a);
//	for (int i = 1; i <= n; ++i) dbg(i, HLD::deep[i]);
	viss();	
	seg.build(1, 1, n);
	seg.update(1, 1, n, 1, 0);
	dfs(a, a);
	ll Min = seg.query(1, 1, n, max(1, HLD::deep[b] - m), HLD::deep[b]);
	if (Min == INF) Min = -1;
	pt(Min);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	cout << fixed << setprecision(20);
	int _T = nextInt();
   	for (int kase = 1; kase <= _T; ++kase) {
   	    cout << "Case #" << kase << ": ";
   	    run();
   	}
//	while (cin >> n) run();
//	run();
	return 0;
}
