#include <bits/stdc++.h>
using namespace std;
 
#define N 510
int n, m;
char s[N];
int G[N][N], l[N][N], r[N][N], up[N][N];
 
int get(int G[][N]) {
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            l[i][j] = r[i][j] = j;
            up[i][j] = 1;
        }
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 2; j <= m; ++j) {
            if (G[i][j] == 1 && G[i][j] == G[i][j - 1]) {
                l[i][j] = l[i][j - 1];
            }
        }
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = m - 1; j >= 1; --j) {
            if (G[i][j] == 1 && G[i][j] == G[i][j + 1]) {
                r[i][j] = r[i][j + 1];
            }
        }
    }
	int x = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (i > 1 && G[i][j] == 1 && G[i][j] == G[i - 1][j]) {
                l[i][j] = max(l[i][j], l[i - 1][j]);
                r[i][j] = min(r[i][j], r[i - 1][j]);
                up[i][j] = up[i - 1][j] + 1;
            }
            if (G[i][j] == 1) {
                int tcol = r[i][j] - l[i][j] + 1;
                int trow = up[i][j];
				int tx = min(tcol, trow);
				x = max(x, tx);
            }
        }
    }
	return x * x;
}
 
int main() {
	int T; scanf("%d", &T);
    while (T--) {
		scanf("%d%d", &n, &m);
        for (int i = 1; i <= n; ++i) {
			scanf("%s", s + 1);
            for (int j = 1; j <= m; ++j) {
            	G[i][j] = s[j] == '.' ? 1 : 0;
			}
        }
    	printf("%d\n", get(G));
	}
    return 0;
}
