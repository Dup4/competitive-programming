#include <bits/stdc++.h>
using namespace std;
const int N = 3e5 + 10;
int n, q, fa[N], f[N], sze[N], ma_sze[N];
vector<vector<int>> G;

bool ok(int goal, int u) {
    if (ma_sze[goal] * 2 > sze[u] || (sze[u] - sze[goal]) * 2 > sze[u])
        return false;
    return true;
}

void dfs(int u) {
    sze[u] = 1;
    ma_sze[u] = 0;
    int Max = 0, pos = 0;
    for (auto &v : G[u]) {
        dfs(v);
        sze[u] += sze[v];
        ma_sze[u] = max(ma_sze[u], sze[v]);
        if (sze[v] > Max) {
            Max = sze[v];
            pos = f[v];
        }
    }
    if (!pos)
        f[u] = u;
    else {
        f[u] = pos;
        while (!ok(f[u], u)) f[u] = fa[f[u]];
    }
}

int main() {
    while (scanf("%d%d", &n, &q) != EOF) {
        G.clear();
        G.resize(n + 1);
        fa[1] = 1;
        for (int i = 2; i <= n; ++i) {
            scanf("%d", fa + i);
            G[fa[i]].push_back(i);
        }
        dfs(1);
        for (int i = 1, x; i <= q; ++i) {
            scanf("%d", &x);
            printf("%d\n", f[x]);
        }
    }
    return 0;
}
