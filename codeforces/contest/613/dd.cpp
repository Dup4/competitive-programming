#include <bits/stdc++.h>
using namespace std;

/*
        CF613D
*/

#define N 100011
int n, q;
int a[N << 1], Sta[N << 1], vis[N];
vector<vector<int> > G[2];
#define erp(G, u) for (int Sze = (int)G[u].size(), i = 0, v = G[u][i]; i < Sze; ++i, v = G[u][i])
void add(vector<vector<int> > &G, int u, int v) {
    G[u].push_back(v);
    G[v].push_back(u);
}

int fa[N], deep[N], sze[N], son[N], top[N], in[N], out[N], cnt;
void DFS(int u) {
    sze[u] = 1;
    erp(G[0], u) if (v != fa[u]) {
        fa[v] = u;
        deep[v] = deep[u] + 1;
        DFS(v);
        sze[u] += sze[v];
        if (!son[u] || sze[v] > sze[son[u]]) {
            son[u] = v;
        }
    }
}
void gettop(int u, int tp) {
    in[u] = ++cnt;
    top[u] = tp;
    if (!son[u]) {
        out[u] = cnt;
        return;
    }
    gettop(son[u], tp);
    erp(G[0], u) if (v != son[u] && v != fa[u]) {
        gettop(v, v);
    }
    out[u] = cnt;
}
int querylca(int u, int v) {
    while (top[u] != top[v]) {
        if (deep[top[u]] < deep[top[v]]) {
            swap(u, v);
        }
        u = fa[top[u]];
    }
    if (deep[u] > deep[v]) {
        swap(u, v);
    }
    return u;
}

bool Not(int k) {
    for (int i = 1; i <= k; ++i) {
        if (vis[fa[a[i]]]) {
            puts("-1");
            return true;
        }
    }
    return false;
}

int f[N], g[N];
void dp(int u, int fa) {
    f[u] = g[u] = 0;
    erp(G[1], u) if (v != fa) {
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

void init() {
    for (int i = 0; i < 2; ++i) {
        G[i].clear();
        G[i].resize(n + 1);
    }
    fa[1] = 0;
    deep[1] = 0;
    memset(son, 0, sizeof son);
    memset(vis, 0, sizeof vis);
    cnt = 0;
}
int main() {
    while (scanf("%d", &n) != EOF) {
        init();
        for (int i = 1, u, v; i < n; ++i) {
            scanf("%d%d", &u, &v);
            add(G[0], u, v);
        }
        DFS(1);
        gettop(1, 1);
        scanf("%d", &q);
        while (q--) {
            scanf("%d", a);
            int k = a[0];
            for (int i = 1; i <= k; ++i) {
                scanf("%d", a + i);
                vis[a[i]] = 1;
            }
            if (Not(k)) {
                for (int i = 1; i <= k; ++i) {
                    vis[a[i]] = 0;
                }
                continue;
            }
            sort(a + 1, a + 1 + k, [&](int x, int y) {
                return in[x] < in[y];
            });
            for (int i = k; i > 1; --i) {
                a[++a[0]] = querylca(a[i], a[i - 1]);
            }
            //按照DFS序排序 并且去掉重复元素
            sort(a + 1, a + 1 + a[0], [&](int x, int y) {
                return in[x] < in[y];
            });
            a[0] = unique(a + 1, a + 1 + a[0]) - a - 1;
            for (int i = 1, top = 0; i <= a[0]; ++i) {
                //判断当前点是否在栈顶节点的子树中
                while (top && out[Sta[top]] < in[a[i]]) {
                    --top;
                }
                //和栈顶节点连边
                if (top) {
                    add(G[1], Sta[top], a[i]);
                }
                Sta[++top] = a[i];
            }
            dp(a[1], a[1]);
            printf("%d\n", f[a[1]]);
            for (int i = 1; i <= a[0]; ++i) {
                vis[a[i]] = 0;
                G[1][a[i]].clear();
            }
        }
    }
    return 0;
}
