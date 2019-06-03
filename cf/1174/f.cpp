#include <bits/stdc++.h>
using namespace std;

#define N 200010
int n;
vector < vector <int> > G;

int fa[N], sze[N], son[N], bigson[N]; 
void pre(int u) {
	sze[u] = 1;
	son[u] = 0;
	for (auto v : G[u]) if (v != fa[u]) {
		fa[v] = u;
		pre(v);
		sze[u] += sze[v];
		if (!son[u] || sze[v] > sze[son[u]]) {
			son[u] = v; 
		}
	}	
}


void f5() {
	fflush(stdout);
}

void solve(int u) {
	//printf("# %d\n", u); f5();
	int v, d;
	printf("d %d\n", u); f5();
	scanf("%d", &d);
	if (d == 0) {
		printf("! %d\n", u); f5();
		return;
	}
	if (!bigson[u]) { 
		printf("s %d\n", u); f5(); 
		scanf("%d", &v);
		if (d == 1) {
			printf("! %d\n", v); f5();
			return;
		}
		solve(v); 
	} else {
		int it = u, d2;
		for (int i = 1; i <= d; ++i) {
			it = son[it]; 
		}	
		printf("d %d\n", it); f5();
		scanf("%d", &d2);
		if (d2 == 0) {
			printf("! %d\n", it); f5();
			return;
		} else {
			int it = u;
			for (int i = 0; i < d; ++i) {
				if (2 * (d - i) == d2) {
					printf("s %d\n", it); f5();
					scanf("%d", &v);
					if (i == d - 1) {
						printf("! %d\n", v); f5();
						return;
					}
					solve(v);
					return;
				}
				it = son[it];
			}		
		}
	}
}

int main() {
	while (scanf("%d", &n) != EOF) {
		G.clear();
		G.resize(n + 1);
		for (int i = 2, u, v; i <= n; ++i) {
			scanf("%d%d", &u, &v);
			G[u].push_back(v);
			G[v].push_back(u);  
		}
		pre(1);
		memset(bigson, 0, sizeof bigson); 
		for (int i = 1; i <= n; ++i) if (son[i]) {
			bigson[son[i]] = 1; 
		}
		solve(1);
	}
	return 0;
}
