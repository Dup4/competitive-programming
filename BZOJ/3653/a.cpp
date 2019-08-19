#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pii pair <int, int>
#define fi first
#define se second
const int N = 3e5 + 1e4;
vector < vector <pii> > qvec;
vector < vector <int> > G;
ll tmp[N], *s[N], *id = tmp, res[N];
int n, q, fa[N], md[N], hson[N], sze[N], deep[N];
void pre(int u) {
	md[u] = deep[u]; sze[u] = 1; hson[u] = 0;
	for (int o = 0, _sze = (int)G[u].size(); o < _sze; ++o) {
		int v = G[u][o];
		if (v == fa[u]) continue;
		fa[v] = u;
		deep[v] = deep[u] + 1;
		pre(v);
		sze[u] += sze[v];   
		if (!hson[u] || md[v] > md[hson[u]]) hson[u] = v;
	}	
	if (hson[u]) md[u] = md[hson[u]];  
}

void DFS(int u) {
	s[u][0] = 0;
	if (hson[u]) {
		s[hson[u]] = s[u] + 1;
		DFS(hson[u]);
		s[u][0] += s[u][1];
	}	
	for (int o = 0, _sze = (int)G[u].size(); o < _sze; ++o) {
		int v = G[u][o];
		if (v == fa[u] || v == hson[u]) continue;
		s[v] = id; id += md[v] - deep[v] + 1; DFS(v);            
		for (int j = 0; j <= md[v] - deep[v]; ++j) s[u][j + 1] += s[v][j];
		s[u][0] += s[v][0]; 
	}
	for (int o = 0, _sze = (int)qvec[u].size(); o < _sze; ++o) {
		int k = qvec[u][o].fi, id = qvec[u][o].se;
		res[id] = 1ll * (sze[u] - 1) * min(deep[u] - 1, k);
	//	cout << id << " " << res[id] << endl;
		if (k >= md[u] - deep[u]) res[id] += s[u][0];
		else res[id] += s[u][0] - s[u][k + 1];
	}
	s[u][0] += sze[u] - 1;
}

int main() {
	while (scanf("%d%d", &n, &q) != EOF) {
		G.clear(); G.resize(n + 1);
		qvec.clear(); qvec.resize(n + 1);
		for (int i = 1, u, v; i < n; ++i) {
			scanf("%d%d", &u, &v);
			G[u].push_back(v);
			G[v].push_back(u);
		}
		for (int i = 1, p, k; i <= q; ++i) {
			scanf("%d%d", &p, &k);
			qvec[p].push_back(pii(k, i));
		}
		fa[1] = 1; deep[1] = 1;
		pre(1);
		s[1] = id; id += md[1] + 1;
		DFS(1);
		for (int i = 1; i <= q; ++i)
			printf("%lld\n", res[i]);
	}
	return 0;
}
