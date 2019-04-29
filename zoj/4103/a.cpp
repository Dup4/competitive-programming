#include <bits/stdc++.h>
using namespace std;

#define N 100010
vector <int> res;
int n;
int used[N], d[N];   
bool done; 
vector < vector <int> > G;

void DFS(int u) {
	if ((int)res.size() == n) {
		done = 1;
		return;
	}
	for (auto v : G[u]) {
		if (!used[v]) {
			for (auto it : G[u]) {
				--d[it]; 
			}
			bool flag = true;
			for (auto it : G[u]) { 
				if (!used[it] && it != v && d[it] <= 0) {
					flag = false;
					break;
				}
			}
			if (flag) {
				used[v] = 1;
				res.push_back(v);
				DFS(v);
				if (done) {
					return; 
				} else {
					used[v] = 0;
					res.pop_back();
				}
			}
			for (auto it : G[u]) {
				++d[it];
			}
		}
	}
}	

void init() {
	res.clear();
	res.push_back(1);
	for (int i = 1; i <= n; ++i) {
		used[i] = 0;
		d[i] = 0;
	}
	used[1] = 1;
	done = false;
	G.resize(n + 1);
	for (int i = 1; i <= n; ++i) {
		G[i].clear();
		for (auto it : {i / 2, i - 1, i * 2, i * 2 + 1}) if (it >= 1 && it <= n) {
			G[i].push_back(it);
			++d[it];
		}
	}
}
int main() {
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		init();
		DFS(1);
		if (!done) {
			puts("-1");
		} else {
			for (int i = 0; i < n; ++i) {
				printf("%d%c", res[i], " \n"[i == n - 1]);
			}
		}
	}
	return 0;
}
