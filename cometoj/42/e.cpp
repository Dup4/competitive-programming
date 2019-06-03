#include <bits/stdc++.h>
using namespace std;

#define N 20
int n, sx, sy;
char G[N][N];

int main() {
	while (scanf("%d", &n) != EOF) {
		for (int i = 1; i <= n; ++i) {
			scanf("%s", G[i] + 1);
			for (int j = 1; j <= m; ++j) {
				if (G[i][j] == 'S') {
					sx = i;
					sy = j;
				}
			}
		}
		
		
	}
	return 0;
}
