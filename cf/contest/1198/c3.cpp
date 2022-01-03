#include <bits/stdc++.h>
using namespace std;
#define debug(...) { printf("#  "); printf(__VA_ARGS__); puts(""); }
const int N = 1e6 + 10;
int n, m, need;
int e[N][2], vis[N];
vector <int> res;

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &n, &m);
		need = n; n *= 3;
		memset(vis, 0, (n + 10) * sizeof (vis[0]));
		for (int i = 1; i <= m; ++i) {
			scanf("%d%d", e[i], e[i] + 1);
		}
		res.clear();
		for (int i = 1; i <= m; ++i) {
			if (!vis[e[i][0]] && !vis[e[i][1]]) {
				vis[e[i][0]] = vis[e[i][1]] = 1;
				res.push_back(i);
			}
		}
		if ((int)res.size() >= need) {
			puts("Matching");
			for (int i = 0; i < need; ++i)
				printf("%d%c", res[i], " \n"[i == need - 1]);
		} else {
			puts("IndSet");
			res.clear();
			for (int i = 1; i <= n; ++i) if (!vis[i])
				res.push_back(i);
			for (int i = 0; i < need; ++i) 
				printf("%d%c", res[i], " \n"[i == need - 1]);
		}
	}	
	return 0;
}
