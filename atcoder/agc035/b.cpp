#include <bits/stdc++.h>
using namespace std;

#define N 100010
#define pii pair<int, int>
#define fi first
#define se second
int n, m;
int e[N][2];
vector<vector<pii>> G;
int used[N], d[N], del[N], vis[N];

int fa[N], deep[N], sze[N], son[N], top[N];
void DFS(int u) {
    used[u] = 1;
    sze[u] = 1;
    for (auto it : G[u]) {
        int v = it.fi;
        int id = it.se;
        if (v == fa[u])
            continue;
        if (used[v])
            del[id] = 1;
        if (!used[v]) {
            if (e[id][0] != u) {
                e[id][0] = u;
                e[id][1] = v;
                d[u] ^= 1;
                d[v] ^= 1;
            }
            fa[v] = u;
            deep[v] = deep[u] + 1;
            e[id][0] = u;
            e[id][1] = v;
            DFS(v);
            sze[u] += sze[v];
            if (!son[u] || sze[v] > sze[son[u]])
                son[u] = v;
        }
    }
}
void gettop(int u, int tp) {
    top[u] = tp;
    if (!son[u])
        return;
    gettop(son[u], tp);
    for (auto it : G[u])
        if (!del[it.se]) {
            int v = it.fi;
            if (v != fa[u] && v != son[u]) {
                gettop(v, v);
            }
        }
}
int query(int u, int v) {
    while (top[u] != top[v]) {
        if (deep[top[u]] < deep[top[v]])
            swap(u, v);
        u = fa[top[u]];
    }
    if (deep[u] > deep[v])
        swap(u, v);
    return u;
}

void DFS2(int u) {
    for (auto it : G[u])
        if (!del[it.se]) {
            int v = it.fi;
            if (v != fa[u]) {
                DFS2(v);
                vis[u] += vis[v];
            }
        }
}

void DFS3(int u) {
    for (auto it : G[u])
        if (!del[it.se]) {
            int v = it.fi;
            int id = it.se;
            if (v != fa[u]) {
                if (vis[v] % 2) {
                    e[id][0] = v;
                    e[id][1] = u;
                }
                DFS3(v);
            }
        }
}

int main() {
    while (scanf("%d%d", &n, &m) != EOF) {
        G.clear();
        G.resize(n + 1);
        memset(used, 0, sizeof used);
        memset(d, 0, sizeof d);
        memset(son, 0, sizeof son);
        memset(del, 0, sizeof del);
        memset(vis, 0, sizeof vis);
        for (int i = 1; i <= m; ++i) {
            int &u = e[i][0], &v = e[i][1];
            scanf("%d%d", &u, &v);
            d[u] ^= 1;
            G[u].push_back(pii(v, i));
            G[v].push_back(pii(u, i));
        }
        DFS(1);
        gettop(1, 1);
        vector<int> vec;
        for (int i = 1; i <= n; ++i)
            if (d[i]) {
                vec.push_back(i);
            }
        if (vec.size() % 2 == 1) {
            puts("-1");
        } else {
            while (!vec.empty()) {
                int u = vec.back();
                vec.pop_back();
                int v = vec.back();
                vec.pop_back();
                int lca = query(u, v);
                ++vis[u];
                ++vis[v];
                vis[lca] -= 2;
            }
            DFS2(1);
            DFS3(1);
            for (int i = 1; i <= m; ++i) printf("%d %d\n", e[i][0], e[i][1]);
        }
    }
    return 0;
}
