#include <bits/stdc++.h>
using namespace std;

/*
        CF613D 给出一些城市，选择一些关键点，使得这些城市被孤立
        求最小关键点数量
        建出虚数 再DP
        f[u] 表示u以及u子树内的最小代价
        g[u] 表示u以及u子树内还要多少关键点没有被孤立
*/

#define N 100010
int n, q;
int a[N << 1], Sta[N << 1], vis[N];
vector<vector<int> > G[2];
#define erp(G, u) for (int Sze = (int)G[u].size(), it = 0, v = G[u][it]; it < Sze; ++it, v = G[u][it])
void add(vector<vector<int> > &G, int u, int v) {
    G[u].push_back(v);
    G[v].push_back(u);
}

int fa[N], deep[N], sze[N], son[N], top[N], p[N];
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
    p[u] = ++p[0];
    top[u] = tp;
    if (!son[u]) {
        return;
    }
    gettop(son[u], tp);
    erp(G[0], u) if (v != son[u] && v != fa[u]) {
        gettop(v, v);
    }
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
    //将用到的点加入a[]，方便清空
    a[++a[0]] = u;
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
    p[0] = 0;
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
            int k = a[0], top = 0;
            for (int i = 1; i <= k; ++i) {
                scanf("%d", a + i);
                vis[a[i]] = 1;
            }
            //特判
            if (Not(k)) {
                for (int i = 1; i <= k; ++i) {
                    vis[a[i]] = 0;
                }
                continue;
            }
            //按DFS序排序
            sort(a + 1, a + 1 + k, [&](int x, int y) {
                return p[x] < p[y];
            });
            //超级根
            Sta[top = 1] = 1;
            for (int i = 1; i <= k; ++i) {
                //求出当前点与栈顶元素的lca
                int lca = querylca(a[i], Sta[top]);
                // 1. lca = Sta[top] 说明a[i] -> Sta[top]是一条直链，直接将a[i]加入栈即可
                // 2. lca != Sta[top] 说明a[i]和Sta[top]在不同的子树中
                //那么我们要维护一条链，那么栈中深度比当前点lca的深度大的都要出栈并且连变
                //再把lca加进去，栈中的所有点又是一条链
                while (deep[lca] < deep[Sta[top]]) {
                    if (deep[Sta[top - 1]] <= deep[lca]) {
                        int last = Sta[top--];
                        if (Sta[top] != lca) {
                            Sta[++top] = lca;
                        }
                        add(G[1], last, lca);
                        break;
                    }
                    add(G[1], Sta[top], Sta[top - 1]);
                    --top;
                }
                if (Sta[top] != a[i]) {
                    Sta[++top] = a[i];
                }
            }
            while (top > 1) {
                add(G[1], Sta[top], Sta[top - 1]);
                --top;
            }
            a[0] = 0;
            dp(1, 1);
            printf("%d\n", f[1]);
            //清空操作
            for (int i = 1; i <= a[0]; ++i) {
                vis[a[i]] = 0;
                G[1][a[i]].clear();
            }
        }
    }
    return 0;
}
