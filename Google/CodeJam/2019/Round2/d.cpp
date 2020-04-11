#include <bits/stdc++.h>
using namespace std;

#define N 100010
#define pii pair <int, int>
#define fi first
#define se second
const ll p = 1e9 + 7;
int vis[N];
int n, a[N];
vector < vector <int> > G;


void init() {
	G.clear();
	G.resize(n + 1);
}
int main() {
	int T; scanf("%d", &T);
	for (int kase = 1; kase <= T; ++kase) {
		printf("Case #%d: ", kase);
		memset(vis, 0, sizeof vis);
		for (int i = 1, x, y; i <= n; ++i) {
			scanf("%d%d", &x, &y);
			if (x == i) vis[i] = 1;
			else G[i].push_back(x);
			if (y == i) vis[i] = 1;
			else G[i].push_back(y);
		}
		for (int i = 1; i <= n; ++i) {
			scanf("%d", a + i);
		}
		
	}
	return 0;
}
