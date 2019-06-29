#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 200010
int n;
vector < vector <int> > G;

ll f1(int n) {
	return (1ll * n * (n + 1)) / 2;
}

ll f2(int n) {
	return 1ll * n * (n + 1) * (2 * n + 1) / 6;
}

ll f(int n) {
	return (n + 1) * f1(n) - f2(n); 
}

int main() {
	while (scanf("%d", &n) != EOF) {
		G.clear(); G.resize(n + 1);
		for (int i = 1, u, v; i < n; ++i) {
			scanf("%d%d", &u, &v);
			G[u].push_back(i);
			G[v].push_back(i);
		}
		ll res = 1ll * n * f1(n - 1) - f(n - 1);   
		for (int i = 1; i <= n; ++i) {
			int sze = (int)G[i].size();
		    res -= f1(*G[i].begin() - 1);
			res -= f1(n - 1 - (*G[i].rbegin()));	
			for (int j = 1; j < sze; ++j) {
				res -= f1(G[i][j] - G[i][j - 1] - 1);
			}
		}   
		printf("%lld\n", res);
	}
	return 0;
}
