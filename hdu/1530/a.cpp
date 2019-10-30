#include <bits/stdc++.h>
using namespace std;
const int N = 310;
int n;
int g[N][N];
int dp[N];
int stk[N][N];
int mx;

int dfs(int n, int ns, int dep) {
    if (0 == ns) {
        if (dep > mx) {
            mx = dep;
        }
        return 1;
    }
    int i, j, k, p, cnt;
    for (i = 0; i < ns; i++) {
        k = stk[dep][i];
        cnt = 0;
        if (dep + n - k <= mx) {
            return 0;
        }
        if (dep + dp[k] <= mx) {
            return 0;
        }
        for (j = i + 1; j < ns; j++) {
            p = stk[dep][j];
            if (g[k][p]) {
                stk[dep + 1][cnt++] = p;
            }
        }
        dfs(n, cnt, dep + 1);
    }
    return 1;
}

int clique(int n) {
    int i, j, ns;
    for (mx = 0, i = n - 1; i >= 0; i--) {   //  vertex: 0 ~ n-1
        for (ns = 0, j = i + 1; j < n; j++) {
            if (g[i][j]) {
                stk[1][ns++] = j;
            }
        }
        dfs(n, ns, 1);
        dp[i] = mx;
    }
    return mx;
}

int main() {
	while (scanf("%d", &n), n) {
		for (int i = 0; i < n; ++i)
			for (int j = 0; j < n; ++j)
				scanf("%d", g[i] + j);
		printf("%d\n", clique(n));
	}
	return 0;
}
