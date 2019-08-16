#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define N 40

int n, m;
ll w[N], p;
int G[N][N], vis[N];
ll mark[N], sum;

ll DFS(int u) {
	vis[u] = 1;
	ll S = 1ll << (u - 1);
	for (int i = 1; i <= n; ++i) {
		if (G[u][i]) {
			if (!vis[i]) {
				vis[i] = 1;
				S |= DFS(i);
			}
		}
	}
	return S;
}

ll gao(int pos, ll S, ll now, ll tmp) {
	if (pos == n + 1) {
	
	}
	for (int i = pos + 1; i <= n + 1; ++i) {
		if (i == n + 1) {
			
		}
	}
}

int main() {
	int T;
	scanf("%d", &T);
	for (int cas = 1; cas <= T; ++cas) {
		printf("Case #%d: ", cas);
		scanf("%d %d %lld", &n, &m, &p);
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= n; ++j) {
				G[i][j] = 0;
			}
			G[i][i] = 1;
			vis[i] = 0;
		}
		for (int i = 1; i <= n; ++i) {
			scanf("%lld", w + i);
			w[i] %= p;
		}
		for (int i = 1, u, v; i <= m; ++i) {
			scanf("%d %d", &u, &v);
			G[u][v] = G[v][u] = 1;
		}
		for (int i = 1; i <= n; ++i) {
			ll S = 1ll << (i - 1);
			for (int j = 1; j <= n; ++j) {
				if (G[i][j]) {
					S |= 1ll << (j - 1);
				}
			}
			mark[i] = S;
		}
		ll ans = 1;
		for (int i = 1; i <= n; ++i) {
			if (!vis[i]) {
				vis[i] = 1;
				ll S = DFS(i);
				sum = 0;
				gao(1, S, 0, 1ll);
				ans = ans * sum % p;
			}
		}
		printf("%lld\n", ans);
	}	
	return 0;
}
