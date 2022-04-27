#include <bits/stdc++.h>
using namespace std;

#define N 1100
int n, leaf[N], W[N], g[N], root;
int e[N][3];
vector<vector<int>> G;
struct node {
    int u, v, w;
    node() {}
    node(int u, int v, int w) : u(u), v(v), w(w) {}
};
vector<node> res;

bool ok() {
    for (int i = 1; i <= n; ++i) {
        if (G[i].size() == 2) {
            return 0;
        }
        if (root == -1 || G[i].size() > G[root].size()) {
            root = i;
        }
    }
    return 1;
}

int getleaf(int u) {
    if (G[u].size() == 0)
        return u;
    for (auto v : G[u]) {
        return getleaf(v);
    }
}

int fa[N];
void pre(int u) {
    for (auto v : G[u])
        if (v != fa[u]) {
            fa[v] = u;
            pre(v);
        }
}

void DFS(int u) {
    if (G[u].empty())
        return;
    for (auto v : G[u]) leaf[v] = getleaf(v);
    int sze = (int)G[u].size();
    if (sze >= 2) {
        g[G[u][0]] = leaf[G[u][1]];
    }
    for (int i = 1; i < sze; ++i) {
        g[G[u][i]] = leaf[G[u][i - 1]];
    }
    for (int sze = (int)G[u].size(), i = 0; i < sze; ++i) {
        int v = G[u][i];
        int nx, nnx;
        if (u == root) {
            if (i == 0) {
                nx = leaf[G[u][1]], nnx = leaf[G[u][2]];
            } else if (i == sze - 1) {
                nx = leaf[G[u][i - 1]], nnx = leaf[G[u][i - 2]];
            } else {
                nx = leaf[G[u][i - 1]], nnx = leaf[G[u][i + 1]];
            }
        } else {
            nx = g[u];
            if (i == 0) {
                nnx = leaf[G[u][1]];
            } else {
                nnx = leaf[G[u][i - 1]];
            }
        }
        res.push_back(node(leaf[v], nx, W[v] / 2));
        res.push_back(node(leaf[v], nnx, W[v] / 2));
        res.push_back(node(nx, nnx, -W[v] / 2));
        // cout << v << " " << nx << " " << nnx << endl;
        int it = leaf[v];
        while (it != v) {
            W[it] -= W[v];
            it = fa[it];
        }
    }
    for (auto v : G[u]) DFS(v);
}

int main() {
    while (scanf("%d", &n) != EOF) {
        G.clear();
        G.resize(n + 1);
        for (int i = 1; i < n; ++i) {
            int &u = e[i][0], &v = e[i][1], &w = e[i][2];
            scanf("%d%d%d", &u, &v, &w);
            G[u].push_back(v);
            G[v].push_back(u);
        }
        root = -1;
        if (!ok()) {
            puts("NO");
        } else {
            if (n == 2) {
                printf("YES\n1\n");
                printf("1 2 %d\n", e[1][2]);
                continue;
            }
            res.clear();
            pre(root);
            G.clear();
            G.resize(n + 1);
            for (int i = 1; i < n; ++i) {
                if (fa[e[i][0]] == e[i][1]) {
                    swap(e[i][0], e[i][1]);
                }
                G[e[i][0]].push_back(e[i][1]);
                W[e[i][1]] = e[i][2];
            }
            DFS(root);
            puts("YES");
            printf("%d\n", (int)res.size());
            assert(res.size() <= 100000);
            for (auto it : res) {
                printf("%d %d %d\n", it.u, it.v, it.w);
            }
        }
    }
    return 0;
}
