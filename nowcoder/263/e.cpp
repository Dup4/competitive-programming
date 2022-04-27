#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 10;
int n, vis[N], Insta[N], Idsta[N], res;
vector<vector<int>> G;

void dfs(int u) {
    vis[u] = 1;
    Insta[u] = 1;
    Idsta[u] = ++*Idsta;
    for (auto &v : G[u]) {
        if (Insta[v]) {
            res = min(res, *Idsta - Idsta[v] + 1);
            continue;
        }
        if (!vis[v])
            dfs(v);
    }
    Insta[u] = 0;
    --(*Idsta);
}

int main() {
    while (scanf("%d", &n) != EOF) {
        G.clear();
        G.resize(n + 1);
        for (int u = 1, v; u <= n; ++u) {
            scanf("%d", &v);
            G[u].push_back(v);
        }
        res = 1e9;
        *Idsta = 0;
        for (int i = 1; i <= n; ++i)
            if (!vis[i])
                dfs(i);
        printf("%d\n", res);
    }
    return 0;
}
