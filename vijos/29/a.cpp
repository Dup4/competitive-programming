#include <bits/stdc++.h>
using namespace std;

#define N 500010
int n, q;
vector<vector<int>> G, U, D;

int fa[N][20], deep[N], md[N], len[N], son[N], top[N], hbit[N];
void DFS(int u, int ff) {
    fa[u][0] = ff;
    md[u] = deep[u] = deep[ff] + 1;
    for (int i = 1; i < 20; ++i) {
        if (fa[u][i - 1]) {
            fa[u][i] = fa[fa[u][i - 1]][i - 1];
        } else {
            break;
        }
    }
    for (auto v : G[u]) {
        if (v != ff) {
            DFS(v, u);
            if (md[v] > md[son[u]]) {
                son[u] = v;
                md[u] = md[v];
            }
        }
    }
}
void gettop(int u, int tp) {
    top[u] = tp;
    len[u] = md[u] - deep[top[u]] + 1;
    if (!son[u])
        return;
    gettop(son[u], tp);
    for (auto v : G[u])
        if (v != fa[u][0] && v != son[u]) {
            gettop(v, v);
        }
}

int query(int u, int k) {
    if (!k)
        return u;
    if (k > deep[u])
        return 0;
    u = fa[u][hbit[k]];
    k ^= (1 << hbit[k]);
    if (!k)
        return u;
    if (deep[u] - deep[top[u]] == k)
        return top[u];
    if (deep[u] - deep[top[u]] > k)
        return D[top[u]][deep[u] - deep[top[u]] - k - 1];
    return U[top[u]][k - deep[u] + deep[top[u]] - 1];
}

void init() {
    G.clear();
    G.resize(n + 1);
    U.clear();
    U.resize(n + 1);
    D.clear();
    D.resize(n + 1);
    memset(deep, 0, sizeof deep);
    memset(son, 0, sizeof son);
    memset(fa, 0, sizeof fa);
    memset(md, 0, sizeof md);
    for (int i = 1, mx = 1; i <= n; ++i) {
        if (i >> mx & 1)
            ++mx;
        hbit[i] = mx - 1;
    }
    md[1] = deep[1] = 1;
}
int main() {
    scanf("%d\n", &n);
    init();
    for (int i = 1, u, v; i < n; ++i) {
        scanf("%d%d", &u, &v);
        G[u].push_back(v);
        G[v].push_back(u);
    }
    DFS(1, 0);
    gettop(1, 1);
    for (int i = 1; i <= n; ++i) {
        if (i == top[i]) {
            int it = i;
            for (int j = 1; it && j <= len[i]; ++j) {
                it = fa[it][0];
                U[i].push_back(it);
            }
            it = i;
            for (int j = 1; j <= len[i]; ++j) {
                it = son[it];
                D[i].push_back(it);
            }
        }
    }
    int lastans = 0;
    scanf("%d", &q);
    for (int _q = 1, u, k; _q <= q; ++_q) {
        scanf("%d%d", &u, &k);
        u ^= lastans;
        k ^= lastans;
        printf("%d\n", lastans = query(u, k));
    }
    return 0;
}
