#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define dbg(x...) do { cout << "\033[32;1m" << #x << " -> "; err(x); } while (0) 
void err() { cout << "\033[39;0m" << endl; } 
template <class T, class... Ts> void err(const T& arg, const Ts&... args) { cout << arg << ' '; err(args...); }
template <template<typename...> class T, typename t, typename... A> 
void err(const T <t> &arg, const A&... args) { for (auto &v : arg) cout << v << ' '; err(args...); }
const ll mod = 1e9 + 7;
const int N = 2e5 + 10;
int n, m, id[N];
vector <vector<int>> G;
struct Edge { int v, nx, cut; }e[N << 1]; int h[N], tot;
inline void addedge(int u, int v) { e[tot] = {v, h[u], 0}; h[u] = tot++; }
struct Tarjan {
	int Low[N], DFN[N], add_block[N], cut[N], bridge; bool Insta[N]; 
	void dfs(int u, int pre) {
		Low[u] = DFN[u] = ++*Low;
		Insta[u] = 1;
		int son = 0; 
	    int pre_cnt = 0;	
		for (int i = h[u]; ~i; i = e[i].nx) {
			int v = e[i].v;
			if (v == pre && pre_cnt == 0) { pre_cnt++; continue; }
			if (!DFN[v]) {
				++son;
				dfs(v, u);
				Low[u] = min(Low[u], Low[v]);
				if (Low[v] > DFN[u]) {
					++bridge;
					e[i].cut = 1;
					e[i ^ 1].cut = 1; 
				}
				if (u != pre && Low[v] >= DFN[u]) {
					cut[u] = 1;
					++add_block[u];
				}
			} else Low[u] = min(Low[u], DFN[v]); 
		}
		if (u == pre && son > 1) cut[u] = 1;
		if (u == pre) add_block[u] = son - 1;
		Insta[u] = 0;
	}
	void gao(int n) {
		memset(DFN, 0, sizeof (DFN[0]) * (n + 10));
		memset(Insta, 0, sizeof (Insta[0]) * (n + 10));
		*Low = 0;
		for (int i = 1; i <= n; ++i) if (!DFN[i]) dfs(i, i); 
	}
}tarjan;

struct UFS {
	int fa[N], sze[N];
	void init() {
		for (int i = 1; i <= n; ++i) {
			fa[i] = 0;
			sze[i] = 1;
		}
	}
	int find(int x) {
		return fa[x] == 0 ? x : fa[x] = find(fa[x]);
	}
	void merge(int u, int v) {
		int fu = find(u), fv = find(v);
		if (fu != fv) {
			if (sze[u] > sze[v]) swap(u, v);
			fa[fu] = fv;
			sze[fv] += sze[fu];
		}
	}
}ufs;

int Max, Maxid;
void dfs(int u, int fa, int deep) {
	if (deep > Max) {
		Max = deep;
		Maxid = u;
	}
	for (auto &v : G[u]) if (v != fa) {
		dfs(v, u, deep + 1);
	}
}

ll qpow(ll base, ll n) {
	ll res = 1;
	while (n) {
		if (n & 1) res = res * base % mod;
		base = base * base % mod;
		n >>= 1;
	}
	return res;
}

int main() {
	while (scanf("%d%d", &n, &m) != EOF) {
		tot = 0; 
		memset(h, -1, sizeof h);
		for (int i = 1, u, v; i <= m; ++i) {
			scanf("%d%d", &u, &v);
			addedge(u, v);
			addedge(v, u);
		}
		tarjan.gao(n);
		ufs.init();
		*id = 0;
		for (int u = 1; u <= n; ++u) {
			for (int i = h[u]; ~i; i = e[i].nx) {
				int v = e[i].v;
				if (e[i].cut == 0) {
					ufs.merge(u, v);
				}
			}
		}		
		for (int i = 1; i <= n; ++i) {
			if (ufs.fa[i] == 0) {
				id[i] = ++*id;
			}
		}
		for (int i = 1; i <= n; ++i) {
			if (ufs.fa[i]) {
				id[i] = id[ufs.find(i)];
			}
		}
		G.clear(); G.resize(*id + 1);
		for (int u = 1; u <= n; ++u) {
			for (int i = h[u]; ~i; i = e[i].nx) {
				int v = e[i].v;
				if (e[i].cut) { 
					G[id[u]].push_back(id[v]);
				}
			}
		}		
		Max = 0, Maxid = 0;
		dfs(1, 0, 0);
		Max = 0; 
		dfs(Maxid, 0, 0);
		printf("%lld\n", 1ll * (*id - 1 - Max) * qpow(m + 1, mod - 2) % mod); 
	}
	return 0;
}
