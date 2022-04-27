#include <bits/stdc++.h>
using namespace std;

using db = double;
const int N = 2e5 + 10;
int n, m, d[N], ord[N];
db f[N], g[N];
vector<vector<int>> G;
void Toposort() {
    *ord = 0;
    queue<int> q;
    for (int i = 1; i <= n; ++i)
        if (!d[i])
            q.push(i);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        ord[++*ord] = u;
        for (auto &v : G[u])
            if (--d[v] == 0)
                q.push(v);
    }
    for (int i = 1; i <= n; ++i) d[i] = (int)G[i].size();
}

int main() {
    int _T;
    cin >> _T;
    while (_T--) {
        scanf("%d%d", &n, &m);
        G.clear();
        G.resize(n + 1);
        memset(d, 0, sizeof(d[0]) * (n + 1));
        memset(f, 0, sizeof(f[0]) * (n + 1));
        memset(g, 0, sizeof(g[0]) * (n + 1));
        for (int i = 1, u, v; i <= m; ++i) {
            scanf("%d%d", &u, &v);
            G[u].push_back(v);
            ++d[v];
        }
        Toposort();
        for (int i = *ord - 1, u; i >= 1; --i) {
            u = ord[i];
            db sum = 0;
            for (auto &v : G[u]) sum += f[v];
            f[u] = sum / d[u] + (d[u] + 1) * 1.0 / d[u];
        }
        for (int i = *ord - 1, u; i >= 1; --i) {
            u = ord[i];
            db sum = 0;
            for (auto &v : G[u]) sum += f[v];
            f[u] = sum / d[u] + (d[u] + 1) * f[u] / d[u];
        }
        printf("%.2f\n", f[1]);
    }
    return 0;
}
