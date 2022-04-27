#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pIL = pair<int, ll>;
#define fi first
#define se second
#define dbg(x...)                             \
    do {                                      \
        cout << "\033[32;1m" << #x << " -> "; \
        err(x);                               \
    } while (0)
void err() {
    cout << "\033[39;0m" << endl;
}
template <class T, class... Ts>
void err(const T &arg, const Ts &...args) {
    cout << arg << ' ';
    err(args...);
}
const int N = 2e5 + 10;
int n, rt, use[N], a[N];
vector<vector<int>> G;

int fa[N], md[N], hson[N], deep[N];

void pre(int u) {
    hson[u] = 0;
    for (auto &v : G[u]) {
        if (v == fa[u])
            continue;
        fa[v] = u;
        deep[v] = deep[u] + 1;
        pre(v);
        if (!hson[u] || md[v] > md[hson[u]])
            hson[u] = v;
    }
    md[u] = md[hson[u]] + 1;
}

pIL tmp[N << 2], *f[N], *id = tmp;

void dfs(int u) {
    if (hson[u]) {
        int v = hson[u];
        f[v] = f[u] + 1;
        dfs(v);
    }
    for (auto &v : G[u]) {
        if (v == fa[u] || v == hson[u])
            continue;
        f[v] = id;
        id += md[v] * 2;
        dfs(v);
    }
    f[u][0] = pIL(deep[u], a[u]);
    for (auto &v : G[u]) {
        if (v == fa[u] || v == hson[u])
            continue;
        for (int i = 1; i <= md[v]; ++i)
            if (f[u][i].se || f[v][i - 1].se) {
                if (f[u][i].se == 0)
                    f[u][i].fi = deep[v];
                if (f[u][i].fi > deep[v]) {
                    int need = f[u][i].fi - deep[v];
                    f[u][i].se = max(1ll, f[u][i].se - need);
                    f[u][i].fi = deep[u] + 1;
                }
                if (f[v][i - 1].se == 0)
                    f[v][i - 1].fi = deep[v];
                if (f[v][i - 1].fi > deep[v]) {
                    int need = f[v][i - 1].fi - deep[v];
                    f[v][i - 1].se = max(1ll, f[v][i - 1].se - need);
                    f[v][i - 1].fi = deep[v];
                }
                f[u][i].se += f[v][i - 1].se;
                if (use[i] == 0 && f[u][i].se > 1) {
                    --f[u][i].se;
                    use[i] = 1;
                    f[u][i].fi = deep[u];
                }
            }
    }
    for (auto &v : G[u]) {
        if (v == fa[u] || v == hson[u])
            continue;
        for (int i = 0; i <= md[v]; ++i) {
            use[i] = 0;
        }
    }
}

int main() {
    scanf("%d%d", &n, &rt);
    memset(use, 0, sizeof use);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", a + i);
        if (a[i] > 1)
            --a[i];
    }
    G.clear();
    G.resize(n + 1);
    for (int i = 1, u, v; i < n; ++i) {
        scanf("%d%d", &u, &v);
        G[u].push_back(v);
        G[v].push_back(u);
    }
    fa[rt] = rt;
    deep[rt] = 1;
    pre(rt);
    f[rt] = id;
    id += md[rt] * 2;
    dfs(rt);
    ll res = 0;
    for (int i = 0; i <= md[rt]; ++i)
        if (f[rt][i].se > 0) {
            // dbg(i, f[rt][i].se);
            if (f[rt][i].fi > 1) {
                int need = f[rt][i].fi - 1;
                f[rt][i].se = max(1ll, f[rt][i].se - need);
            }
            res += f[rt][i].se;
        }
    printf("%lld\n", res);
    return 0;
}
