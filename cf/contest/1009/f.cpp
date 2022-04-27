#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pii pair<int, int>
#define fi first
#define se second
const int N = 1e6 + 1e4;
vector<vector<int> > G;
int tmp[N], *s[N], *id = tmp;
pii res[N];
int n, q, fa[N], md[N], hson[N], sze[N], deep[N];
void pre(int u) {
    md[u] = deep[u];
    sze[u] = 1;
    hson[u] = 0;
    for (auto v : G[u])
        if (v != fa[u]) {
            fa[v] = u;
            deep[v] = deep[u] + 1;
            pre(v);
            sze[u] += sze[v];
            if (!hson[u] || md[v] > md[hson[u]])
                hson[u] = v;
        }
    if (hson[u])
        md[u] = md[hson[u]];
}

void DFS(int u) {
    s[u][0] = 1;
    res[u] = pii(1, 0);
    if (hson[u]) {
        s[hson[u]] = s[u] + 1;
        DFS(hson[u]);
        if (res[hson[u]].fi > res[u].fi) {
            res[u] = res[hson[u]];
            ++res[u].se;
        }
    }
    for (auto v : G[u])
        if (v != fa[u] && v != hson[u]) {
            s[v] = id;
            id += md[v] - deep[v] + 1;
            DFS(v);
            for (int j = 0; j <= md[v] - deep[v]; ++j) {
                s[u][j + 1] += s[v][j];
                if (s[u][j + 1] > res[u].fi || (s[u][j + 1] == res[u].fi && j + 1 < res[u].se)) {
                    res[u] = pii(s[u][j + 1], j + 1);
                }
            }
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
        fa[1] = 1;
        deep[1] = 1;
        pre(1);
        s[1] = id;
        id += md[1] + 1;
        DFS(1);
        for (int i = 1; i <= n; ++i) printf("%d\n", res[i].se);
    }
    return 0;
}
