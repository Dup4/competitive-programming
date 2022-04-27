#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 10, INF = 0x3f3f3f3f;
struct Hash {
    vector<int> a;
    void init() {
        a.clear();
    }
    void add(int x) {
        a.push_back(x);
    }
    void gao() {
        sort(a.begin(), a.end());
        a.erase(unique(a.begin(), a.end()), a.end());
    }
    int get(int x) {
        return lower_bound(a.begin(), a.end(), x) - a.begin() + 1;
    }
} hs;
struct E {
    int u, v;
    E() {}
    E(int u, int v) : u(u), v(v) {}
} e[N];
struct node {
    int id, u, v;
};
vector<vector<node>> G;
vector<node> res;
int n, m, d[N], fa[N], vis[N], Insta[N], used[N], usede[N], F;
int find(int x) {
    return fa[x] == 0 ? x : fa[x] = find(fa[x]);
}
void merge(int u, int v) {
    u = find(u);
    v = find(v);
    if (u != v)
        fa[u] = v;
}
void dfs(int u) {
    used[u] = 1;
    Insta[u] = 1;
    for (auto &it : G[u])
        if (!usede[it.id]) {
            usede[it.id] = 1;
            int v = it.v;
            if (Insta[v]) {
                if (!F) {
                    res.push_back({it.id, hs.a[it.u - 1], hs.a[0]});
                    F = 1;
                    return;
                }
            }
            if (used[v] == 0) {
                dfs(v);
            }
            if (F)
                return;
        }
    Insta[u] = 0;
}

int main() {
    int _T;
    scanf("%d", &_T);
    while (_T--) {
        scanf("%d", &n);
        hs.init();
        for (int i = 1, u, v; i <= n; ++i) {
            scanf("%d%d", &u, &v);
            hs.add(u);
            hs.add(v);
            e[i] = E(u, v);
            usede[i] = 0;
        }
        hs.gao();
        m = hs.a.size();
        for (int i = 1; i <= m; ++i) {
            d[i] = fa[i] = 0;
            vis[i] = 0;
            Insta[i] = used[i] = 0;
        }
        G.clear();
        G.resize(m + 1);
        for (int i = 1; i <= n; ++i) {
            e[i].u = hs.get(e[i].u);
            e[i].v = hs.get(e[i].v);
            ++d[e[i].u];
            ++d[e[i].v];
            merge(e[i].u, e[i].v);
            int u = e[i].u, v = e[i].v;
            G[u].push_back({i, u, v});
            G[v].push_back({i, v, u});
        }
        int rt = 1, frt = find(rt);
        vis[frt] = 1;
        res.clear();
        for (int i = 1; i <= n; ++i) {
            int &u = e[i].u, &v = e[i].v;
            if (d[u] > d[v])
                swap(u, v);
            int fu = find(u);
            if (vis[fu])
                continue;
            if (d[u] == 1) {
                res.push_back({i, hs.a[u - 1], hs.a[0]});
                vis[fu] = 1;
            }
        }
        for (int i = 1; i <= m; ++i) {
            int fi = find(i);
            if (vis[fi])
                continue;
            F = 0;
            vis[fi] = 1;
            dfs(i);
        }
        int sze = res.size();
        printf("%d\n", sze);
        for (int i = 0; i < sze; ++i) {
            printf("%d %d %d\n", res[i].id, res[i].u, res[i].v);
        }
    }
    return 0;
}
