#include <bits/stdc++.h>
using namespace std;

#define N 200010
#define INF 0x3f3f3f3f
int n, m;
vector < vector <int> > G;
int vis[N], deep[N], cnt[N], Max;   
void DFS(int u) {
	vis[u] = 1;
	Max = max(Max, deep[u]);
	++cnt[deep[u]];
	for (auto v : G[u]) if (!vis[v]) {
		deep[v] = deep[u] + 1;
		DFS(v);
	}
}
int f1() {
	int res = 0;
	for (int i = 1; i <= Max; i += 2) {
		res += cnt[i];
	}
	return res;
}
int f2() {
	int res = 0;
	for (int i = 2; i <= Max; i += 2) {
		res += cnt[i];
	}
	return res; 
}

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &n, &m);
		G.clear();
		G.resize(n + 1);
		Max = 0;
		for (int i = 1; i <= n; ++i) {
			vis[i] = 0;
			cnt[i] = 0;
		}
		for (int i = 1, u, v; i <= m; ++i) {
			scanf("%d%d", &u, &v);
			G[u].push_back(v);
			G[v].push_back(u); 
		}
		deep[1] = 1;
		DFS(1);
		vector <int> vec;
		if (f1() < f2()) {
			for (int i = 1; i <= Max; ++i) vis[i] = 0;
			for (int i = 1; i <= Max; i += 2) {
				vis[i] = 1;
			}
		} else {
			for (int i = 1; i <= Max; ++i) vis[i] = 0;
			for (int i = 2; i <= Max; i += 2) {
				vis[i] = 1;
			}	
		}
		for (int i = 1; i <= n; ++i) {
			if (vis[deep[i]]) {
				vec.push_back(i);
			}
		}
		int sze = (int)vec.size();
		printf("%d\n", sze);
		for (int i = 0; i < sze; ++i) {
			printf("%d%c", vec[i], " \n"[i == sze - 1]);
		}
	}
	return 0;
}
