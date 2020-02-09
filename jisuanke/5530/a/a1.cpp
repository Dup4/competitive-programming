#include <bits/stdc++.h>
using namespace std;
#define dbg(x...) do { cout << "\033[32;1m" << #x << " -> "; err(x); } while (0) 
void err() { cout << "\033[39;0m" << endl; } 
template <class T, class... Ts> void err(const T& arg, const Ts&... args) { cout << arg << ' '; err(args...); }
const int N = 1e6 + 10;
int n, m, ans[N]; 

struct W { int op, a, b; }w[N]; 
vector <vector<int>> G;

struct UFS {
	struct node { int fa, sze; void init() { fa = 0; sze = 1; } }t[N << 1];  
	struct BackNode { int who, id, cnt; node t; }Back[N << 1];
	int id[N], T; 
	void init(int n) { *id = 0; for (int i = 1; i <= n; ++i) t[i].init(), id[i] = ++*id; T = 0; }
	int find(int x) { return t[x].fa == 0 ? x : find(t[x].fa); }
	void dead(int x) {
		int fx = find(id[x]); 
		Back[++T] = {0, fx, *id, t[fx]};
		Back[++T] = {x, id[x], *id, t[id[x]]};
		--t[fx].sze; 
		id[x] = 0;
	}
	void rebirth(int x) {
		dead(x);
		id[x] = ++*id;
		t[id[x]].init();
	}
	void merge(int x, int y) {
		int fx = find(id[x]), fy = find(id[y]);
		if (fx != fy) {
			if (t[fx].sze > t[fy].sze) swap(fx, fy);
			Back[++T] = {0, fx, *id, t[fx]};
			Back[++T] = {0, fy, *id, t[fy]};
			t[fx].fa = fy;
			t[fy].sze += t[fx].sze;
		}
	} 
	bool same(int x, int y) { return find(id[x]) == find(id[y]); } 
	int getsze(int x) { return t[find(id[x])].sze; } 
	void rollback(int _T) {
		while (T != _T) {
			BackNode tmp = Back[T]; 
			if (tmp.who) id[tmp.who] = tmp.id;
			t[tmp.id] = tmp.t;
			*id = tmp.cnt; 
			--T;
		}
	}
}ufs;

void dfs(int u) {
	for (auto &v : G[u]) {
		int T = ufs.T;
		int op = w[v].op, a = w[v].a, b = w[v].b;
		if (op == 1) {
			if (ufs.id[a] && ufs.id[b]) 
				ufs.merge(a, b);
		} else if (op == 2) {
			if (ufs.id[a])
				ufs.dead(a);	
		} else if (op == 3) {
			if (ufs.id[a] && ufs.id[b] && a != b) {
				ufs.rebirth(a);
				ufs.merge(a, b);
			}
		} else if (op == 4) {
			if (ufs.id[a] == 0 || ufs.id[b] == 0)
				ans[v] = 0;
			else 
				ans[v] = ufs.same(a, b);
		} else if (op == 5) {
			if (ufs.id[a] == 0)
				ans[v] = 0;
			else
				ans[v] = ufs.getsze(a);
		}
		dfs(v);
		ufs.rollback(T);
	}
}

int main() {
	while (scanf("%d%d", &n, &m) != EOF) {
		G.clear(); G.resize(m + 1);
		for (int i = 1, op, k, a, b; i <= m; ++i) {
			scanf("%d%d%d", &op, &k, &a);
			if (op == 1 || op == 3 || op == 4) scanf("%d", &b);
			w[i] = {op, a, b};
			G[k].push_back(i);
		}
		ufs.init(n);
		dfs(0);
		for (int i = 1; i <= m; ++i) {
			if (w[i].op == 4) {
				puts(ans[i] ? "Yes" : "No");
			} else if (w[i].op == 5) {
				printf("%d\n", ans[i]);
			}
		}
	}
	return 0;
}
