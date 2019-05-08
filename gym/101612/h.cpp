#include <bits/stdc++.h>
using namespace std;

#define N 100010
int n;
vector < vector <int> > G;
int fa[N]; 
int used[N];
int f[N][3];
//0 表示该节点不选
//1 表示该节点向儿子连一条边
//2 表示该节点向父亲连一条边
void DFS(int u) {
	for (int i = 0; i < 3; ++i) {
		f[u][i] = 0;
	}
	int Min = 1e9;
	for (auto v : G[u]) {
		DFS(v);
		f[u][0] += max(f[v][0], f[v][1]);
		f[u][1] += f[v][0];
		Min = min(Min, f[v][0] - f[v][2]); 
		f[u][2] += max(f[v][0], f[v][1]);
	}
	++f[u][2];
    f[u][1] -= Min;	
}
	

void File() {
	freopen("hidden.in", "r", stdin);
	freopen("hidden.out", "w", stdout);
}
void init() {
	G.clear();
	G.resize(n + 1);
	memset(fa, 0, sizeof fa);
	memset(f, 0, sizeof f);
	memset(used, 0, sizeof used);
}
int main() {
	//File();
	while (scanf("%d", &n) != EOF) {
		init();
		for (int i = 2; i <= n; ++i) {
			scanf("%d", fa + i);
			G[fa[i]].push_back(i);
		}
		int res = 0;
		int cnt = 0;
		vector <int> vec;
		for (int i = 1; i <= n; ++i) if (fa[i] == 0) {
			DFS(i);
			if (f[i][0] >= f[i][1]) {
				res += f[i][0];
				++cnt; 
				vec.push_back(i);   
				used[i] = 1;
			} else {
				res += f[i][1];
			}
		}
		for (int i = 0, sze = vec.size(); i < sze; ++i) {
			if (i == 0) {
				fa[vec[i]] = 1;
			} else {
				fa[vec[i]] = fa[vec[i - 1]];
			}
		}
		for (int i = 1; i <= n; ++i) if (fa[i] == 0 && used[i] == 0) {
			fa[i] = 1;
		}	
		printf("%d\n", res + cnt / 2);
		for (int i = 2; i <= n; ++i) {
			printf("%d%c", fa[i], " \n"[i == n]);
		}
	}
	return 0;
}
