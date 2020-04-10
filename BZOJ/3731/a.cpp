#include <bits/stdc++.h>
using namespace std;
#define dbg(x...) do { cout << "\033[32;1m" << #x << " -> "; err(x); } while (0) 
void err() { cout << "\033[39;0m" << endl; } 
template <class T, class... Ts> void err(const T& arg, const Ts&... args) { cout << arg << ' '; err(args...); }
#define SZ(x) (int(x.size()))
const int N = 2e5 + 10, M = 2e4 + 10;
int n, q, a[N], ans;
vector < vector<int> > G, BG; 

namespace MoTree {
	int blo, cnt;
	int belong[N], fa[N]; 
	struct Blocks {
		int a[256], sze; 
		void clear() { sze = 0; } 
		void ins(int x) {
			++sze; int pos = sze;
			for (int i = sze; i > 1  && a[i - 1] > x; --i)
			    a[i] = a[i - 1], pos = i - 1;
			a[pos] = x;
		}
		void modify(int x, int y) {  
			int pos = lower_bound(a + 1, a + sze + 1, x) - a;
			for (; pos < sze && a[pos + 1] < y; ++pos) a[pos] = a[pos + 1];
			for (; pos > 1 && a[pos - 1] > y; --pos) a[pos] = a[pos - 1];
			a[pos] = y;
		}
		int query(int x) {
			int pos = upper_bound(a + 1, a + sze + 1, x) - a;
			return sze - pos + 1;
		}
	}b[M];
	void getk(int u, int x) {
		ans += b[u].query(x);
		for (int i = 0; i < SZ(BG[u]); ++i) 
			getk(BG[u][i], x);
	}
	void getans(int u, int x) {
		if (a[u] > x) ++ans;
		for (int i = 0; i < SZ(G[u]); ++i) {
			int v = G[u][i];
			if (v == fa[u]) continue;
		    if (belong[v] == belong[u]) getans(v, x);
		    else getk(belong[v], x);
		}
	}
	void modify(int u, int x) { b[belong[u]].modify(a[u], x); a[u] = x; }
    void addBlock(int u) { 
		if (b[belong[fa[u]]].sze == blo) {
			belong[u] = ++cnt;
			b[cnt].ins(a[u]);
			BG[belong[fa[u]]].push_back(cnt);
		} else {
			b[belong[u] = belong[fa[u]]].ins(a[u]);
		}
	}
	void addItem(int u, int x) {
		a[++n] = x;
		G[u].push_back(n);
		G[n].push_back(u);
		fa[n] = u;
		addBlock(n); 
	}
	void dfs(int u) {
		addBlock(u);
		for (int i = 0; i < SZ(G[u]); ++i) {
			int v = G[u][i];
			if (v == fa[u]) continue;
			fa[v] = u;
			dfs(v);
		}
	}
	void del(vector <int> &vec, int x) {
		vec.erase(find(vec.begin(), vec.end(), x)); 
	}
	void reBuildFa(int u) {
		for (int i = 0; i < SZ(G[u]); ++i) {
			int v = G[u][i];
			if (v == fa[u]) continue; 
			if (belong[v] == belong[u]) {
				b[belong[u]].ins(a[v]);
				reBuildFa(v);
			}
		}
	}
	void reBuildSon(int u, int preBlk) {
		for (int i = 0; i < SZ(G[u]); ++i) {
			int v = G[u][i];
			if (v == fa[u]) continue;
			if (belong[v] == preBlk) {
				belong[v] = belong[u];
				b[belong[v]].ins(a[v]);
				reBuildSon(v, preBlk);
			} else {
				del(BG[preBlk], belong[v]);
				BG[belong[u]].push_back(belong[v]);
			}
		}
	}
    void del(int u) {
		if (u == 1) return;
		del(G[u], fa[u]);
		del(G[fa[u]], u);
		if (belong[u] != belong[fa[u]]) {
			del(BG[belong[fa[u]]], belong[u]); 
		} else {
			b[belong[fa[u]]].clear();
			b[belong[fa[u]]].ins(a[fa[u]]);
			reBuildFa(fa[u]);
			belong[u] = ++cnt;
			b[cnt].ins(a[u]);
			reBuildSon(u, belong[fa[u]]);
		}
		fa[u] = 0;
	}	
	void init() {
		blo = (int)sqrt(n); cnt = 0;
    	BG.clear(); BG.resize(N);	
		fa[1] = 0;
		dfs(1);
	}
}

int main(){
	scanf("%d", &n);
	G.clear(); G.resize(N);
	for (int i = 1, u, v; i < n; ++i) {
		scanf("%d%d", &u, &v);
		G[u].push_back(v);
		G[v].push_back(u);
	}
	for (int i = 1; i <= n; ++i) scanf("%d", a + i);
	MoTree::init(); 
	ans = 0;
	scanf("%d", &q);
	for (int i = 1; i <= q; ++i) {
		int opt, u, x;
		scanf("%d", &opt);
		if (opt == 3) {
			scanf("%d", &u);
			u ^= ans;
			MoTree::del(u); 
		} else {
			scanf("%d%d", &u, &x);
			u ^= ans; x ^= ans;
			if (opt == 0) {
				ans = 0; 
				MoTree::getans(u, x);
				printf("%d\n",ans);
			} else if (opt == 1) {
				MoTree::modify(u, x);
			} else if (opt == 2) {
				MoTree::addItem(u, x);	
			}
		}
	}
}
