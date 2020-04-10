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
constexpr int N = 4e5 + 10, INF = 0x3f3f3f3f, M = 20; 
int n, q, K, R, dis[N], restPoint[N];  
vector <vector<int>> G;

struct UFS {
	int fa[N], rk[N];
	void init(int n) {
		memset(fa, 0, sizeof (fa[0]) * (n + 5));
		memset(rk, 0, sizeof (rk[0]) * (n + 5));
	}
	int find(int x) { return fa[x] == 0 ? x : fa[x] = find(fa[x]); }
	bool merge(int x, int y) {
		int fx = find(x), fy = find(y);
		if (fx != fy) {
			if (rk[fx] > rk[fy]) swap(fx, fy);
			fa[fx] = fy;
			if (rk[fx] == rk[fy]) ++rk[fy];
			return true;
		}
		return false;
	}
	bool same(int x, int y) { return find(x) == find(y); }
}ufs;

void bfs() {
	queue <int> que;
	for (int i = 1; i <= n; ++i) {
		if (restPoint[i]) {
			dis[i] = 0;
			que.push(i);
		} else dis[i] = INF;
	}
	ufs.init(n);
	while (!que.empty()) {
		int u = que.front(); que.pop();
		if (dis[u] >= K) continue;
		for (auto &v : G[u]) {
			if (dis[v] >= dis[u] + 1) ufs.merge(u, v);
			if (dis[v] > dis[u] + 1) {
				dis[v] = dis[u] + 1;
				que.push(v);
			}
		}
	}
}

struct LCA {
	int fa[N][M], dis[N][M]; 
	int deep[N]; 
	void bfs(int rt) {
		queue <int> q; 
		deep[rt] = 0; fa[rt][0] = rt; dis[rt][0] = 0; q.emplace(rt); 
		while (!q.empty()) {
			int u = q.front(); q.pop(); 
			for (int i = 1; i < M; ++i) { 
				dis[u][i] = dis[u][i - 1] + dis[fa[u][i - 1]][i - 1];   
				fa[u][i] = fa[fa[u][i - 1]][i - 1]; 
			} 
			for (auto &v : G[u]) {
				int w = 1;
				if (v == fa[u][0]) continue;
				deep[v] = deep[u] + 1;   
				fa[v][0] = u; 
				dis[v][0] = w;   
				q.emplace(v);   
			} 
		}
	}
	int querylca(int u, int v) {
		if (deep[u] > deep[v]) swap(u, v);
		for (int det = deep[v] - deep[u], i = 0; det; det >>= 1, ++i) {
			if (det & 1) v = fa[v][i];
		}	
		if (u == v) return u;
		for (int i = M - 1; i >= 0; --i) {
			if (fa[u][i] == fa[v][i]) continue;
			u = fa[u][i]; v = fa[v][i];
		}
		return fa[u][0];
	}
	int querydis(int u, int v) {
		if (deep[u] > deep[v]) swap(u, v); 
		int res = 0;
		for (int det = deep[v] - deep[u], i = 0; det; det >>= 1, ++i) {
			if (det & 1) {
				res += dis[v][i];
				v = fa[v][i];
			}
		}
		if (u == v) return res;
		for (int i = M - 1; i >= 0; --i) {
			if (fa[u][i] == fa[v][i]) continue;
			res += dis[u][i] + dis[v][i];
			u = fa[u][i], v = fa[v][i];
		}
		return res + dis[u][0] + dis[v][0];   
	}
	int kth(int u, int k) {
		for (int i = M - 1; i >= 0; --i) {
			if ((k >> i) & 1)
				u = fa[u][i];
		}
		return u;
	}
	//u -> v cross lca(u, v) d step
	int jump(int u, int v, int Lca, int d) {
		if (d <= deep[u] - deep[Lca]) {
			return kth(u, d);
		} else {
			int tot = deep[u] + deep[v] - 2 * deep[Lca];
			tot -= deep[u] - deep[Lca];
			d -= deep[u] - deep[Lca];
			return kth(v, tot - d);
		}
	}
}lca;

void run() {
	G.clear(); G.resize(n * 2 + 5);
	int oldN = n;
	for (int i = 1, u, v; i < oldN; ++i) {
		rd(u, v);
		++n;
		G[u].push_back(n);
		G[n].push_back(u);
		G[v].push_back(n);
		G[n].push_back(v);
	}
	for (int i = 1; i <= n; ++i) restPoint[i] = 0;
	for (int i = 1, x; i <= R; ++i) {
		rd(x);
		restPoint[x] = 1;
	}
	bfs();
	lca.bfs(1);
	rd(q);
	while (q--) {
		static int u, v;
		rd(u, v);
		if (lca.querydis(u, v) <= K * 2) pt("YES");
		else {
			int Lca = lca.querylca(u, v);
			int _u = lca.jump(u, v, Lca, K);
			int _v = lca.jump(v, u, Lca, K);
			if (ufs.same(lca.jump(u, v, Lca, K), lca.jump(v, u, Lca, K))) pt("YES");
			else pt("NO");
		}
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	cout << fixed << setprecision(20);
	while (cin >> n >> K >> R) run(); 
//	while (cin >> n) run();
//    for (int kase = 1; kase <= _T; ++kase) {
//        cout << "Case #" << kase << ":\n";
//        run();
//    }
	return 0;
}
