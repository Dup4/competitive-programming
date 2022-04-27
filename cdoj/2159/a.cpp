#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10;
int n, m, f[N];
vector<vector<int>> G;

int main() {
    while (scanf("%d%d", &n, &m) != EOF) {
        G.clear();
        G.resize(n + 1);
        memset(f, 0, sizeof f);
        for (int i = 1, u, v; i < n; ++i) {
            scanf("%d%d", &u, &v);
            G[u].push_back(v);
            G[v].push_back(u);
        }
        DFS(1);
    }
    return 0;
}
