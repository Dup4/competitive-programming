#include <bits/stdc++.h>
using namespace std;

#define N 100010
int n, m, a[N], b[N];
vector <vector<int>> G;
char s[N];

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &n, &m);
		G.clear(); G.resize(n + 1);
		for (int i = 1; i <= n; ++i) a[i] = 0;
		for (int i = 1; i <= m; ++i) b[i] = 0;
		for (int i = 1; i <= n; ++i) {
			scanf("%s", s + 1);
			G[i].resize(m + 1);
			for (int j = 1; j <= m; ++j) {
				if (s[j] == '*') {
					G[i][j] = 1;
				} else {
					++a[i];
					++b[j];
				}
			}
		}
		int res = n + m - 1;
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= m; ++j) {
				if (G[i][j]) {
					res = min(res, a[i] + b[j]); 
				} else {
					res = min(res, a[i] + b[j] - 1);
				}
			}
		}
		printf("%d\n", res);
	}
	return 0;
}
