#include <bits/stdc++.h>
using namespace std;

#define N 100010
int n, fa[N], used[N], point[N];
vector <vector<int>> G;
int deep[N];
void DFS(int u) {
	for (auto v : G[u]) {
		deep[v] = deep[u] + 1;
		DFS(v); 
	}
}

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		fa[1] = 0;
		G.clear(); G.resize(n + 1); 
		scanf("%d", &n);
		for (int i = 2; i <= n; ++i) {
			scanf("%d", fa + i);
			G[fa[i]].push_back(i);  
		}
		DFS(1);
		for (int i = 1; i <= n; ++i) point[i] = i;
		sort(point + 1, point + 1 + n, [](int x, int y){
			return deep[x] > deep[y]; 		
		});
		int res = 0;
		memset(used, 0, sizeof used);
		for (int i = 1; i <= n; ++i) {
			int x = point[i];
			if (!used[x]) {
				int F = fa[x], FF, a[3] = {0, 0, 0};    
				if (F == 1) continue;      
				if (!used[F]) {
					while (!G[F].empty()) {
						if (G[F].back() == x || used[G[F].back()]) G[F].pop_back();
						else {
							a[0] = G[F].back();
							break;
						}
					}
					if (a[0]) {
						FF = fa[F];
						while (!G[FF].empty()) {
							if (G[FF].back() == F || used[G[F].back()]) G[F].pop_back();
							else if (!a[1]) {
								a[1] = G[F].back();
								G[F].pop_back();
							} else if (!a[2]) {
								a[2] = G[F].back();
								break;
							}
						}
						if (!a[1]) {
							if (!a[2]) {
								++res;
								used[x] = 1;
								used[F] = 1;
								for (int j = 0; j < 3; ++j) used[a[j]] = 1; 
							} else {
								G[FF].push_back(a[1]);
								G[FF].push_back(F);
							}
						} else {
							G[FF].push_back(F);
						}
					} else {
						G[F].push_back(i);
					}
				}			
			}
		}
		printf("%d\n", res);
	}
	return 0;
}
