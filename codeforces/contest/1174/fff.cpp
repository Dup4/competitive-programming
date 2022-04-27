#include <bits/stdc++.h>
using namespace std;

#define N 200010
int n;
vector<vector<int> > G;

void f5() {
    fflush(stdout);
}

int query(char c, int x) {
    printf("%c %d\n", c, x);
    f5();
    int res;
    scanf("%d", &res);
    return res;
}

int depx, fa[N], deep[N], del[N], sze[N];
void pre(int u) {
    for (auto v : G[u])
        if (v != fa[u]) {
            fa[v] = u;
            deep[v] = deep[u] + 1;
            pre(v);
        }
}

void getsze(int u, int fa) {
    sze[u] = 1;
    for (auto v : G[u])
        if (v != fa && !del[v]) {
            getsze(v, u);
            sze[u] += sze[v];
        }
}

int find(int u, int fa, int sum) {
    for (auto v : G[u])
        if (v != fa && !del[v]) {
            if (sze[v] >= sum / 2) {
                return find(v, u, sum);
            }
        }
    return u;
}

int solve(int u) {
    getsze(u, 0);
    int v = find(u, 0, sze[u]);
    int d = query('d', v);
    if (!d) {
        return v;
    }
    del[v] = 1;
    if (deep[v] + d == depx) {
        return solve(query('s', v));
    } else {
        return solve(fa[v]);
    }
}

int main() {
    while (scanf("%d", &n) != EOF) {
        memset(del, 0, sizeof del);
        G.clear();
        G.resize(n + 1);
        for (int i = 1, u, v; i < n; ++i) {
            scanf("%d%d", &u, &v);
            G[u].push_back(v);
            G[v].push_back(u);
        }
        depx = query('d', 1);
        deep[1] = 0;
        pre(1);
        printf("! %d\n", solve(1));
        f5();
    }
    return 0;
}
