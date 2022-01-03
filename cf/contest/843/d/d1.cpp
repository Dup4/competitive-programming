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
constexpr ll INFLL = 0x3f3f3f3f3f3f3f3f;
int n, m, q, W[N];
ll *f;

struct Graph {
	struct E { int to, nx, w; }e[N << 1]; int h[N], cnt;
	void init(int n) { for (int i = 0; i <= n; ++i) h[i] = -1; cnt = -1; }
	void addedge(int u, int v, int w = 0) { e[++cnt] = { v, h[u], w}; h[u] = cnt; } 
}G;

struct Dijkstra {
	struct node {
		int u; ll w;
		node(int u = 0, ll w = 0) : u(u), w(w) {}
		bool operator < (const node &other) const { return w > other.w; }		
	};
	ll dis[N]; bool used[N];
	void gao(int s) {
		for (int i = 1; i <= n; ++i) {
			dis[i] = INFLL;
			used[i] = 0;
		}
		priority_queue <node> pq;
		dis[s] = 0;
		pq.push(node(s, dis[s]));
		while (!pq.empty()) {
			int u = pq.top().u; pq.pop();
			if (used[u]) continue;
			used[u] = 1;
			for (int i = G.h[u]; ~i; i = G.e[i].nx) {
				int v = G.e[i].to; ll w = W[G.e[i].w];
				if (dis[v] > dis[u] + w) {
					dis[v] = dis[u] + w;
					pq.push(node(v, dis[v]));
				}
			}
		}
	}
}dij;

namespace SPFA {
	struct Node {
	    int fa, val, depth;
	    vector <int> ch;
		void init() { fa = val = depth = 0; ch.clear(); }
	}node[N << 1];
	ll dis[N];
	void Change(int x, int val) {
	    node[x].val = val;
	    for (int i = 0; i < SZ(node[x].ch); ++i) {
	        node[node[x].ch[i]].val = val;
	        Change(node[x].ch[i], val);
	    }
	}
	void Maintain(int x) {
	    for(int i = 0; i < SZ(node[x].ch); ++i) {
	        node[node[x].ch[i]].depth = node[x].depth + 1;
	        Maintain(node[x].ch[i]);
	    }
	}
	int queuery(int x) { return node[x].val; }
	void Link(int x, int y) {
	    node[x].fa = y;
	    node[x].depth = node[y].depth + 1;
	    Maintain(x);
	    node[y].ch.push_back(x);
	}
	void Cut(int x) {
	    Node &s = node[node[x].fa];
	    node[x].depth = 1;
	    Maintain(x);
	    for (int i = 0; i < SZ(s.ch); ++i) {
	        if (s.ch[i] == x) {
	            for (int j = i; j < SZ(s.ch) - 1; ++j) {
	                s.ch[j] = s.ch[j + 1];
	            }
	            s.ch.pop_back();
	            break;
	        }
	    }
	    node[x].fa = 0;
	}
	int lca(int x, int y) {
	    if (x == y) return true;
	    for (int i = 0; i < SZ(node[x].ch); ++i) {
	         if (lca(node[x].ch[i], y)) return true;
	    }
	    return false;
	}
	bool gao(int S) {
		queue <int> que;
		for (int i = 0; i <= n; ++i) dis[i] = INFLL;
	    dis[S] = 0;
	    node[S].depth = 1;
	    que.push(S);
	    Change(S, 1);
	    while (!que.empty()) {
	        int u = que.front(); que.pop();
	        if (node[u].val == 0) continue;
	        for (int i = G.h[u]; ~i; i = G.e[i].nx) {
	            int v = G.e[i].to; ll w = W[G.e[i].w] + f[u] - f[v];
	            if (dis[v] > dis[u] + w) {
	                if (lca(v, u)) return 1;
					dis[v] = dis[u] + w;
	                que.push(v);
	                Change(v, 0);
	                node[v].val = 1;
	                Cut(v);
	                Link(v, u);
	            }
	        }
	    }
	    return 0;
	}
	void init(int n) {
		for (int i = 1; i <= n; ++i) node[i].init();
	} 
}

void run() {
	G.init(n);
	for (int i = 1, u, v, w; i <= m; ++i) {
		rd(u, v, w);
		G.addedge(u, v, i);
		W[i] = w;
	}
	dij.gao(1);
    f = dij.dis;	
	while (q--) {
		int op;
		rd(op);
		if (op == 1) {
			int v; rd(v);
			if (f[v] >= INFLL) pt(-1);
			else pt(f[v]);
		} else {
			int sz, x; rd(sz);
			for (int i = 1; i <= sz; ++i) {
				rd(x);
				++W[x];
			}
			SPFA::init(n);
			SPFA::gao(1);
			for (int i = 1; i <= n; ++i) if (SPFA::dis[i] < INFLL) f[i] += SPFA::dis[i];
		}
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	cout << fixed << setprecision(20);
	while (cin >> n >> m >> q) run();
//    for (int kase = 1; kase <= _T; ++kase) {
//        cout << "Case #" << kase << ":\n";
//        run();
//    }
	return 0;
}
