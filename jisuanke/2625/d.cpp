#include <bits/stdc++.h>

using namespace std;

const int maxn = 2e2 + 10;

struct Edge{
	int to, nxt;
	Edge() {}
	Edge(int to, int nxt): to(to), nxt(nxt){}
}edge[maxn << 1];

int n, m;
int head[maxn], tot;
int vis[maxn];
int w[maxn];
int val[maxn][2];
int dp[maxn][10010];

void Init() {
	tot = 0;
	memset(val, 0, sizeof val);
	memset(dp, -1, sizeof dp);
	memset(vis, -1, sizeof vis);
	memset(head, -1, sizeof head);
}

void addedge(int u,int v) {
	edge[tot] = Edge(v, head[u]); head[u] = tot++;
	edge[tot] = Edge(u, head[v]); head[v] = tot++;
}

void DFS(int id, int u,int fa) {
	for (int i = head[u]; ~i; i = edge[i].nxt) {
		int v = edge[i].to;
		if (v == fa) continue;
		if (vis[v] != -1) continue;
		vis[v] = !vis[u];
		val[id][vis[v]] += w[v];
		DFS(id, v, u);
	}
}

int main() {
	int t;
	scanf("%d", &t);
	while(t--) {
		Init();
		scanf("%d %d", &n, &m);
		int sum = 0;
		for (int i = 1; i <= n; ++i) {
			scanf("%d", w + i);
			w[i] /= 100;
			sum += w[i];	
		}
		for (int i = 1, u, v; i <= m; ++i) {
			scanf("%d %d", &u, &v);
			addedge(u, v);
		}
		int cnt = 0;
		for (int i = 1; i <= n; ++i) {
			if (vis[i] == -1) {
				cnt++;
				vis[i] = 0;
				val[cnt][0] += w[i];
				DFS(cnt, i, -1);
			}
		}
		dp[0][0] = 1;
		for (int i = 1; i <= cnt; ++i) {
			for (int j = sum; j >= 0; --j) {
				if (dp[i - 1][j] != -1) {
					dp[i][j + val[i][0]] = 1;
					dp[i][j + val[i][1]] = 1;
				}
			}
		}
		int ans = 1 << 30;
		for (int i = 0; i <= sum; ++i) {
			if (dp[cnt][i] != -1 && dp[cnt][sum - i] != -1) {
				ans = min(ans, max(i, sum - i));
			}
		}
		printf("%d\n", ans * 100);
	}
	return 0;
}
