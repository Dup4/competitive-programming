#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
int n, q, a[N << 1], vis[N];
vector<vector<int>> G[2];

namespace Tree {
int fa[N], deep[N], sze[N], son[N], top[N], in[N], out[N], Sta[N << 1];
int f[N], g[N];
void dfs(int u) {
    son[u] = 0;
    sze[u] = 1;
    for (auto &v : G[0][u]) {
        if (v == fa[u])
            continue;
        fa[v] = u;
        deep[v] = deep[u] + 1;
        dfs(v);
        sze[u] += sze[v];
        if (!son[u] || sze[v] > sze[son[u]])
            son[u] = v;
    }
}
void gettop(int u, int tp) {
    in[u] = ++*in;
    top[u] = tp;
    if (son[u])
        gettop(son[u], tp);
    for (auto &v : G[0][u]) {
        if (v != son[u] && v != fa[u])
            gettop(v, v);
    }
    out[u] = *in;
}
int querylca(int u, int v) {
    while (top[u] != top[v]) {
        if (deep[top[u]] < deep[top[v]])
            swap(u, v);
        u = fa[top[u]];
    }
    if (deep[u] > deep[v])
        swap(u, v);
    return u;
}
void init() {
    fa[1] = 0;
    deep[1] = 0;
    *in = 0;
    dfs(1);
    gettop(1, 1);
}
void dp(int u, int fa) {
    f[u] = g[u] = 0;
    for (auto &v : G[1][u]) {
        if (v == fa)
            continue;
        dp(v, u);
        f[u] += f[v];
        g[u] += g[v];
    }
    if (vis[u]) {
        f[u] += g[u];
        g[u] = 1;
    } else {
        f[u] += (g[u] > 1);
        g[u] = (g[u] == 1);
    }
}
bool Not() {
    for (int i = 1; i <= *a; ++i) {
        if (vis[fa[a[i]]]) {
            return true;
        }
    }
    return false;
}
void gao() {
    if (Not()) {
        puts("-1");
        return;
    }
    int k = *a;
    sort(a + 1, a + 1 + k, [&](int x, int y) {
        return in[x] < in[y];
    });
    for (int i = k; i > 1; --i) {
        a[++*a] = querylca(a[i], a[i - 1]);
    }
    //按照dfs序排序 并且去掉重复元素
    sort(a + 1, a + 1 + a[0], [&](int x, int y) {
        return in[x] < in[y];
    });
    a[0] = unique(a + 1, a + 1 + a[0]) - a - 1;
    for (int i = 1, top = 0; i <= a[0]; ++i) {
        //判断当前点是否在栈顶节点的子树中
        while (top && out[Sta[top]] < in[a[i]]) --top;
        //和栈顶节点连边
        if (top) {
            G[1][Sta[top]].push_back(a[i]);
            G[1][a[i]].push_back(Sta[top]);
        }
        Sta[++top] = a[i];
    }
    dp(a[1], a[1]);
    printf("%d\n", f[a[1]]);
}
}  // namespace Tree

int main() {
    while (scanf("%d", &n) != EOF) {
        G[0].clear();
        G[0].resize(n + 1);
        G[1].clear();
        G[1].resize(n + 1);
        memset(vis, 0, sizeof vis);
        for (int i = 1, u, v; i < n; ++i) {
            scanf("%d%d", &u, &v);
            G[0][u].push_back(v);
            G[0][v].push_back(u);
        }
        Tree::init();
        scanf("%d", &q);
        while (q--) {
            scanf("%d", a);
            for (int i = 1; i <= *a; ++i) {
                scanf("%d", a + i);
                vis[a[i]] = 1;
            }
            Tree::gao();
            for (int i = 1; i <= *a; ++i) {
                vis[a[i]] = 0;
                G[1][a[i]].clear();
            }
        }
    }
    return 0;
}
