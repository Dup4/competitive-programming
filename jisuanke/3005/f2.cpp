#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ui = unsigned int;
const int N = 1e6 + 10;
int n, q;
ui p[N];
ll ans[5010];
vector<vector<int>> G;
int fa[N], deep[N];
struct node {
    int k, id, f;
};
vector<vector<node>> qvec;
struct BIT {
    ll a[N];
    void init() {
        memset(a, 0, sizeof a);
    }
    inline void update(int x, ll v) {
        for (; x <= n; x += x & -x) a[x] += v;
    }
    inline ll query(int x) {
        ll res = 0;
        for (; x > 0; x -= x & -x) res += a[x];
        return res;
    }
    inline ll query(int l, int r) {
        r = min(r, n);
        if (l > r)
            return 0;
        return query(r) - query(l - 1);
    }
} bit;
void pre(int u) {
    for (auto &v : G[u])
        if (v != fa[u]) {
            deep[v] = deep[u] + 1;
            fa[v] = u;
            pre(v);
        }
}
void DFS(int u) {
    for (auto &it : qvec[u]) ans[it.id] -= bit.query(deep[u], deep[u] + it.k) * it.f;
    bit.update(deep[u], p[u]);
    for (auto &v : G[u])
        if (v != fa[u])
            DFS(v);
    for (auto &it : qvec[u]) ans[it.id] += bit.query(deep[u], deep[u] + it.k) * it.f;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) scanf("%u", p + i);
    G.clear();
    G.resize(n + 1);
    qvec.clear();
    qvec.resize(n + 1);
    for (int i = 1, u, v; i < n; ++i) {
        scanf("%d%d", &u, &v);
        G[u].push_back(v);
        G[v].push_back(u);
    }
    scanf("%d", &q);
    fa[1] = 0;
    deep[1] = 1;
    pre(1);
    for (int i = 1, u, k; i <= q; ++i) {
        scanf("%d%d", &u, &k);
        qvec[u].push_back({k, i, 1});
        int v = u;
        while (fa[v] && k) {
            --k;
            qvec[fa[v]].push_back({k, i, 1});
            if (k - 1 >= 0)
                qvec[v].push_back({k - 1, i, -1});
            v = fa[v];
        }
    }
    memset(ans, 0, sizeof ans);
    bit.init();
    DFS(1);
    for (int i = 1; i <= q; ++i) printf("%lld\n", ans[i]);
    return 0;
}
