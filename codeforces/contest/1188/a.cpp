#include <bits/stdc++.h>
using namespace std;

#define N 100010
int n;
vector<vector<int>> G;
bool F;

int deep[N], s, t;
void DFS(int u, int fa) {
    if (deep[u] > deep[s]) {
        s = u;
    }
    for (auto v : G[u])
        if (v != fa) {
            deep[v] = deep[u] + 1;
            DFS(v, u);
        }
}
void DFS2(int u, int fa) {
    if (G[u].size() == 2) {
        F = 0;
        return;
    }
    for (auto v : G[u])
        if (v != fa) {
            DFS2(v, u);
            if (!F)
                return;
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
        deep[1] = 0;
        s = 0;
        DFS(1, 1);
        F = 1;
        DFS2(s, s);
        puts(F ? "YES" : "NO");
    }
    return 0;
}
