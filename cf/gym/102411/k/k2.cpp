#include <bits/stdc++.h>
using namespace std;
const int N = 1e3 + 10;
int n, m, a[N][N];
char g[N][N];

int main() {
	while (scanf("%d%d", &n, &m) != EOF) {
		for (int i = 1; i <= n; ++i) {
			scanf("%s", g[i] + 1);
		}	
		int px, py;
		memset(a, 0, sizeof a);
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= m; ++j) {
				if (g[i][j] == 'A') {
					px = i;
					py = j;

				}
				if (isalpha(g[i][j])) {
					a[i][j] = 1;
				}
			}
		}

	}
	return 0;
}
