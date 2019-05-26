#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 100010
const ll p = 1e9 + 7;
int n, fa[N];
ll w[N];
ll b[N];
ll sum[N];
ll res;
vector < vector <int> > G;
int sze[N], big[N], used[N];
void DFS(int u) {
	sze[u] = 1;
	big[u] = 0; 
	for (auto v : G[u]) {
		w[v] ^= w[u];
		DFS(v);  
		if (sze[v] > sze[big[u]]) {
			big[u] = v; 
		}
		sze[u] += sze[v]; 
	}
}

void add(int u, int op) {
	for (auto v : G[u]) if (!used[v]) {
		add(v, op);
		(sum[w[v]] += 1ll * op * sze[v] % p) %= p;
		(sum[w[v]] += p) %= p;
	}
}

void DSU(int u, bool vis) {
	for (auto v : G[u]) if (v != big[u]) {
		DSU(v, 0);
	}
	if (big[u]) {
		DSU(big[u], 1);
		used[big[u]] = 1;
	}
	(res += p - 1ll * sze[u] * sum[w[u]] % p) %= p;
	(res += 1ll * (n - sze[big[u]]) * sum[w[u]] % p) %= p;
	for (auto v : G[u]) if (v != big[u]) {
		add(v, 1);
		(res += p - 1ll * sze[u] * sum[w[u]] % p) %= p;
		(res += 1ll * (n - sze[v]) * sum[w[u]] % p) %= p;
		add(v, -1); 
	}
	(sum[w[u]] += sze[u]) %= p;
	if (big[u]) used[big[u]] = 0;
	if (!vis) {
		add(v, -1);
		(sum[w[u]] += p - sze[u]) %= p;
	}
}


int main() {
	while (scanf("%d", &n) != EOF) {
		G.clear();
		G.resize(n + 1);   
		w[1] = 0;
		sze[0] = 0; 
		for (int i = 2; i <= n; ++i) {
			scanf("%d%lld", fa + i, w + i);
			G[fa[i]].push_back(i);
		}
		DFS(1);
		b[0] = 0;
		for (int i = 1; i <= n; ++i) {
			b[++b[0]] = w[i];
		}
		sort(b + 1, b + 1 + b[0]);
		b[0] = unique(b + 1, b + 1 + b[0]) - b - 1;
		for (int i = 1; i <= n; ++i) {
			w[i] = lower_bound(b + 1, b + 1 + b[0], w[i]) - b;
		}
	//	for (int i = 1; i <= n; ++i) {
	//		cout << i << " " << sze[i] << endl;
	//	}
		res = 0;
		memset(sum, 0, sizeof sum);
		for (int i = 1; i <= n; ++i) {
			if (w[i] == 1) continue;
			(res += 1ll * sze[i] * sum[w[i]] % p) %= p;
			(sum[w[i]] += sze[i]) %= p;	
		}
	//	puts("#####################");
	//	for (int i = 1; i <= n; ++i) {
	//		cout << i << " " << w[i] << " " << sum[w[i]] << endl;
	//	}
		cout << res << endl;
		memset(sum, 0, sizeof sum);
		memset(used, 0, sizeof used);
		DSU(1, 0);
		printf("%lld\n", res);
	}
	return 0;
}
