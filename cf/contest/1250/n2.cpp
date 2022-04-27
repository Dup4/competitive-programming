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
int n, m, vis[N];
struct Edge {
    int to, id;

    Edge() {}

    Edge(int to, int id) : to(to), id(id) {}
};

struct node {
    int id, u, v;

    node() {}

    node(int id, int u, int v) : id(id), u(u), v(v) {}
};

bool F;
vector<vector<Edge> > G;
vector<node> res;

void gao(int u, int pre) {
    vis[u] = 1;
    for (auto &it : G[u]) {
        if (it.to == pre)
            continue;
        if (vis[it.to]) {
            if (!F) {
                res.push_back(node(it.id, it.to, 1));
            }
            F = true;
        } else {
            if (G[it.to].size() == 1) {
                if (!F) {
                    res.pu
                }
            }
            gao(it.to, u);
        }
    }
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
        }
        hs.gao();
        m = hs.a.size();
        G.clear();
        G.resize(m + 1);
        for (int i = 1; i <= n; ++i) {
            e[i].u = hs.get(e[i].u);
            e[i].v = hs.get(e[i].v);
            G[e[i].u].push_back(Edge(e[i].v, i));
            G[e[i].v].push_back(Edge(e[i].u, i));
        }
        for (int i = 1; i <= m; ++i) vis[i] = 0;
        gao(1, 1);
        res.clear();
        for (int i = 1; i <= m; ++i) {
            if (vis[i])
                continue;
            F = false;
            gao(i, i);
        }
        int sze = res.size();
        printf("%d\n", sze);
        for (int i = 0; i < sze; ++i) {
            printf("%d %d %d\n", res[i].id, hs.a[res[i].u - 1], hs.a[res[i].v - 1]);
        }
    }
    return 0;
}
