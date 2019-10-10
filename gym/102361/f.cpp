#include <bits/stdc++.h>
using namespace std;
using ll = long long; 
const int N = 5e5 + 10;
const ll mod = 998244353;
int n, m, bit[N];
vector <vector<int>> G;
int dep[N], tot, vis[N], Insta[N]; ll res;
void DFS(int u, int pre) {
	vis[u] = 1;
	Insta[u] = 1;
	for (auto &v : G[u]) if (v != pre) {   
		if (Insta[v]) { 
			tot -= dep[u] - dep[v] + 1; 
			res = 1ll * res * (bit[dep[u] - dep[v] + 1] - 1) % mod;
			res %= mod;
		}
		if (!vis[v]) {
			dep[v] = dep[u] + 1;
			DFS(v, u);
		}
	}
	Insta[u] = 0;
}
 
int main() {
	bit[0] = 1;
	for (int i = 1; i < N; ++i) bit[i] = 1ll * bit[i - 1] * 2 % mod;
	while (scanf("%d%d", &n, &m) != EOF) {
		G.clear(); G.resize(n + 1);
		for (int i = 1; i <= n; ++i) fa[i] = dep[i] = vis[i] = Insta[i] = 0;
		for (int i = 1, u, v; i <= m; ++i) {
			scanf("%d%d", &u, &v);
			G[u].push_back(v);
			G[v].push_back(u);
		}
		tot = m; res = 1; 
		fa[1] = 1; dep[1] = 1; 
		DFS(1, 0);
		res = 1ll * res * bit[tot] % mod;
		res = (res + mod) % mod;
		printf("%lld\n", res);
	}
	return 0;
}
