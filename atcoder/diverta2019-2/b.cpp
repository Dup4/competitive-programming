#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pii pair <int, int>
#define fi first
#define se second
#define N 60
int n, tot;
pii a[N];
map <pii, int> mp;
vector < vector <int> > G;
int vis[N];
void DFS(int u, int fa) {
	vis[u] = 1;
	for (auto v : G[u]) if (v != fa) {
		DFS(v, u);
	}
}

int main() {
	while (scanf("%d", &n) != EOF) {
		mp.clear();
		for (int i = 1; i <= n; ++i) {
			scanf("%d%d", &a[i].fi, &a[i].se);
			mp[a[i]] = i;
		}
		vector <pii> vec;
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= n; ++j) if (i != j) {
				vec.push_back(pii(a[i].fi - a[j].fi, a[i].se - a[j].se));
			}
		}	
		sort(vec.begin(), vec.end());
		vec.erase(unique(vec.begin(), vec.end()), vec.end());
		int res = 1e9;
	    if (n == 1) {
			res = 1;
		}	
		for (auto it : vec) {
			G.clear(); G.resize(n + 1);
			memset(vis, 0, sizeof vis);
			tot = 0;
			int p = it.fi, q = it.se;
			for (int i = 1; i <= n; ++i) { 
				int x = a[i].fi, y = a[i].se;
				if (mp.find(pii(1ll * x - p, 1ll * y - q)) != mp.end()) {
					G[i].push_back(mp[pii(1ll * x - p, 1ll * y - q)]);
					G[mp[pii(1ll * x - p, 1ll * y - q)]].push_back(i);
				}
			}	
			for (int i = 1; i <= n; ++i) {
				if (!vis[i]) {
					++tot;
					DFS(i, i);
				}
			}
			res = min(res, tot);
		}
		printf("%d\n", res);
	}
	return 0;
}
