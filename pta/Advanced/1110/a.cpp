#include <bits/stdc++.h>
using namespace std;
const int N = 1100;

struct E {
	int son[2];
	E() {son[0] = son[1] = -1;}
}e[N];

int n, Max, MaxId, vis[N];

void dfs(int u, int id) {
	MaxId = max(MaxId, id);
	if (id == n) Max = u;
	int now = e[u].son[0];
	if (now != -1)
		dfs(now, id << 1);
	now = e[u].son[1];
	if (now != -1)
		dfs(now, id << 1 | 1);
}

int main() {
	while (scanf("%d", &n) != EOF) {
		assert(n <= 20);
		memset(e, -1, sizeof e);
		memset(vis, 0, sizeof vis);
		for (int i = 0; i < n; ++i) {
			static char x[10], y[10]; 
			scanf("%s %s", x, y);
			if (x[0] != '-') {
				int c = 0;
				for (int j = 0; x[j]; ++j)
					c = c * 10 + x[j] - '0';
				e[i].son[0] = c;
				vis[c] = 1;
			}
			if (y[0] != '-') {
				int c = 0;
				for (int j = 0; y[j]; ++j)
					c = c * 10 + y[j] - '0';
				e[i].son[1] = c;
				vis[c] = 1;
			}
		}
		int rt = -1;
		for (int i = 0; i < n; ++i) {
			if (!vis[i]) {
				assert(rt == -1);
				rt = i;
			}
		}
		Max = -1; MaxId = 0;
		dfs(rt, 1);
		if (MaxId == n) {
			cout << "YES " << Max;
		} else {
			cout << "NO " << rt;
		}
		cout << "\n";
	}
	return 0;
}

