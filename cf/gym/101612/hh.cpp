#include <bits/stdc++.h>
using namespace std;

#define N 100010
int n;
vector < vector <int> > G;
vector < vector <int> > unused;
int fa[N], rt[N]; 
int used[N];
vector <int> a, b;
int res;
void DFS(int u, int root) {
	rt[u] = root;
	used[u] = 0;
	for (auto v : G[u]) {
		DFS(v, root);
		if (!used[u] && !used[v]) {
			++res;
			used[u] = used[v] = 1;
		}
		if (used[v] == 0) {
			unused[root].push_back(v);
		}
	}
}

void File() {
	#ifndef HOME
	freopen("hidden.in", "r", stdin);
	freopen("hidden.out", "w", stdout);
	#endif
}
void init() {
	G.clear();
	G.resize(n + 1);
	unused.clear();
	unused.resize(n + 1);
	memset(fa, 0, sizeof fa);
	a.clear();
	b.clear();
	res = 0;
}
int main() {
	File();
	while (scanf("%d", &n) != EOF) {
		init();
		for (int i = 2; i <= n; ++i) {
			scanf("%d", fa + i);
			G[fa[i]].push_back(i);
		}
		queue <int> q;
		for (int i = 1; i <= n; ++i) if (fa[i] == 0) {
			DFS(i, i);
			if (used[i] == 1) {
				fa[i] = 1;
				for (auto it : unused[i]) {
					q.push(it);
				}
			} else {
				a.push_back(i);
			}
		}
		sort(a.begin(), a.end(), [&](int x, int y) {
			return unused[x].size() > unused[y].size();	 		
		});
		for (auto it : a) {
			if (!q.empty() && it != 1) {
				fa[it] = q.front();
				q.pop();
				++res;
			} else {
				b.push_back(it);
			}
			for (auto it2 : unused[it]) {
				q.push(it2);
			}
		}
		sort(b.begin(), b.end());
		for (int i = 0, sze = b.size(); i < sze; ++i) {
			if (i == 0) {
				fa[b[i]] = 1;
			} else {
				fa[b[i]] = b[i - 1];
			}
			res += i & 1;
		}
		printf("%d\n", res);
		for (int i = 2; i <= n; ++i) {
			printf("%d%c", fa[i], " \n"[i == n]); 
		}
	}
	return 0;
}
