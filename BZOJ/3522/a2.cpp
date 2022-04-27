#include <bits/stdc++.h>
using namespace std;

#define ll long long
const int N = 5e3 + 10;
int n;
vector<vector<int> > G;
ll f[4][N], s[N];

void DFS(int u, int fa, int deep, int f) {
    s[deep] += f;
    for (int _ = 0, sze = (int)G[u].size(); _ < sze; ++_) {
        int v = G[u][_];
        if (v == fa)
            continue;
        DFS(v, u, deep + 1, f);
    }
}

int main() {
    while (scanf("%d", &n) != EOF) {
        G.clear();
        G.resize(n + 1);
        for (int i = 1, u, v; i < n; ++i) {
            scanf("%d%d", &u, &v);
            G[u].push_back(v);
            G[v].push_back(u);
        }
        ll res = 0;
        for (int i = 1; i <= n; ++i) {
            memset(f, 0, sizeof f);
            for (int j = 0; j <= n; ++j) f[0][j] = 1;
            for (int _ = 0, sze = (int)G[i].size(); _ < sze; ++_) {
                int v = G[i][_];
                DFS(v, i, 1, 1);
                for (int j = 3; j >= 1; --j) {
                    for (int k = 1; s[k]; ++k) {
                        f[j][k] += f[j - 1][k] * s[k];
                    }
                }
                DFS(v, i, 1, -1);
            }
            for (int i = 1; f[3][i]; ++i) res += f[3][i];
        }
        printf("%lld\n", res);
    }
    return 0;
}
