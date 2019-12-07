#include <bits/stdc++.h>
using namespace std;
const int N = 110;
struct E {
	int son[2];
	E() {son[0] = son[1] = -1;}
}e[N];
int n, vis[N];
vector <int> vec;
void bfs(int S) {
	queue <int> que;
	que.push(S);
	while (!que.empty()) {
		int u = que.front(); que.pop();
		vec.push_back(u);
		if (e[u].son[1] != -1) {
			que.push(e[u].son[1]);
		}
		if (e[u].son[0] != -1) {
			que.push(e[u].son[0]);
		}
	}
}

void dfs(int u) {
	if (u == -1) return;
	dfs(e[u].son[1]);
	vec.push_back(u);
	dfs(e[u].son[0]);
}

void print(vector<int> vec) {
	for (int i = 0; i < n; ++i)
		printf("%d%c", vec[i], " \n"[i == n - 1]);
}

int main() {
	while (scanf("%d", &n) != EOF) {
		memset(e, -1, sizeof e);
		memset(vis, 0, sizeof vis);
		for (int i = 0; i < n; ++i) {
			static char x[10], y[10];
			scanf("%s %s", x, y);
			if (x[0] != '-') {
				int c = x[0] - '0';
				e[i].son[0] = c;
				vis[c] = 1;
			}
			if (y[0] != '-') {
				int c = y[0] - '0';
				e[i].son[1] = c;
				vis[c] = 1;
			}
		}
		int rt = -1;
		for (int i = 0; i < n; ++i) {
			if (!vis[i])
				rt = i;
		}
		vec.clear();
		bfs(rt);
		print(vec);
		vec.clear();
		dfs(rt);
		print(vec);
	}
	return 0;
}
