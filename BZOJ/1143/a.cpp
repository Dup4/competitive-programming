#include <bits/stdc++.h>
using namespace std;
const int N = 1e3 + 10;
int n, m, g[N][N];
vector<vector<int> > G;
struct Hungary {
    // uN　左边的点数
    // linker[i] 右边的第i个点连向左边的点
    int uN, linker[N];
    bool used[N];
    bool dfs(int u) {
        for (int o = 0; o < G[u].size(); ++o) {
            int v = G[u][o];
            if (!used[v]) {
                used[v] = true;
                if (linker[v] == -1 || dfs(linker[v])) {
                    linker[v] = u;
                    return true;
                }
            }
        }
        return false;
    }
    int gao() {
        int res = 0;
        memset(linker, -1, sizeof linker);
        for (int u = 0; u < uN; ++u) {
            memset(used, 0, sizeof used);
            if (dfs(u))
                ++res;
        }
        return res;
    }
} hungary;

int main() {
    while (scanf("%d%d", &n, &m) != EOF) {
        memset(g, 0, sizeof g);
        for (int i = 1, u, v; i <= m; ++i) {
            scanf("%d%d", &u, &v);
            g[u][v] = 1;
        }
        for (int k = 1; k <= n; ++k) {
            for (int i = 1; i <= n; ++i) {
                for (int j = 1; j <= n; ++j) {
                    g[i][j] = g[i][j] | (g[i][k] & g[k][j]);
                }
            }
        }
        G.clear();
        G.resize(n + 1);
        hungary.uN = n;
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (i != j && g[i][j]) {
                    G[i - 1].push_back(j - 1);
                }
            }
        }
        printf("%d\n", n - hungary.gao());
    }
    return 0;
}
