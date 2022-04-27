#include <bits/stdc++.h>
using namespace std;

#define N 200010
int n;
vector<vector<int> > G;

int fa[N], sze[N], deep[N], son[N], bigson[N], depx;
void pre(int u) {
    sze[u] = 1;
    son[u] = 0;
    for (auto v : G[u])
        if (v != fa[u]) {
            fa[v] = u;
            deep[v] = deep[u] + 1;
            pre(v);
            sze[u] += sze[v];
            if (!son[u] || sze[v] > sze[son[u]]) {
                son[u] = v;
            }
        }
}

void f5() {
    fflush(stdout);
}

void solve(int u, int dxu) {
    int v, dxv, y;
    if (dxu == -1) {
        printf("d %d\n", u);
        f5();
        scanf("%d", &dxu);
    }
    if (dxu == 0) {
        printf("! %d\n", u);
        f5();
        return;
    }
    if (u == 1) {
        depx = dxu;
    }
    if (!bigson[u]) {
        printf("s %d\n", u);
        f5();
        scanf("%d", &v);
        solve(v, dxu - 1);
    } else {
        v = u;
        for (int i = 1; i <= dxu && son[v]; ++i) {
            v = son[v];
        }
        printf("d %d\n", v);
        f5();
        scanf("%d", &dxv);
        if (dxv == 0) {
            printf("! %d\n", v);
            f5();
            return;
        } else {
            y = u;
            for (int i = 0; i < dxu; ++i) {
                if (deep[v] + depx - 2 * deep[y] == dxv) {
                    break;
                }
                y = son[y];
            }
            printf("s %d\n", y);
            f5();
            scanf("%d", &y);
            solve(y, depx - deep[y]);
        }
    }
}

int main() {
    while (scanf("%d", &n) != EOF) {
        G.clear();
        G.resize(n + 1);
        for (int i = 2, u, v; i <= n; ++i) {
            scanf("%d%d", &u, &v);
            G[u].push_back(v);
            G[v].push_back(u);
        }
        son[0] = 0;
        sze[0] = 0;
        deep[1] = 0;
        pre(1);
        memset(bigson, 0, sizeof bigson);
        for (int i = 1; i <= n; ++i)
            if (son[i]) {
                bigson[son[i]] = 1;
            }
        solve(1, -1);
    }
    return 0;
}
