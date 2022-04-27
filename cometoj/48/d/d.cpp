#include <bits/stdc++.h>
using namespace std;
using pII = pair<int, int>;
#define fi first
#define se second
const int N = 2e5 + 10, mod = 998244353;
int n, res, fa[N], deep[N], inv[N], in[N];
vector<vector<int>> G;
vector<vector<pII>> mergeVec;

inline void chadd(int &x, int y) {
    x += y;
    while (x >= mod) x -= mod;
    while (x < 0) x += mod;
}

struct UFS {
    int fa[N], sze[N];
    void init(int n) {
        for (int i = 1; i <= n; ++i) {
            fa[i] = 0;
            sze[i] = 1;
        }
    }
    int find(int x) {
        return fa[x] == 0 ? x : fa[x] = find(fa[x]);
    }
    void join(int x, int y) {
        int fx = find(x), fy = find(y);
        if (fx != fy) {
            if (sze[fx] > sze[fy])
                swap(fx, fy);
            fa[fx] = fy;
            res = 1ll * res * inv[sze[fx] + 1] % mod;
            res = 1ll * res * inv[sze[fy] + 1] % mod;
            sze[fy] += sze[fx];
            res = 1ll * res * (sze[fy] + 1) % mod;
        }
    }
} ufs;

struct LCA {
    int son[N], sze[N], top[N];
    void DFS(int u) {
        sze[u] = 1;
        son[u] = 0;
        for (auto &v : G[u])
            if (v != fa[u]) {
                deep[v] = deep[u] + 1;
                DFS(v);
                sze[u] += sze[v];
                if (!son[u] || sze[v] > sze[son[u]])
                    son[u] = v;
            }
    }
    void gettop(int u, int tp) {
        top[u] = tp;
        if (!son[u])
            return;
        gettop(son[u], tp);
        for (auto &v : G[u]) {
            if (v != son[u] && v != fa[u]) {
                gettop(v, v);
            }
        }
    }
    void init(int root) {
        fa[root] = root;
        deep[root] = 0;
        DFS(root);
        gettop(root, root);
    }
    int query(int u, int v) {
        while (top[u] != top[v]) {
            if (deep[top[u]] < deep[top[v]]) {
                swap(u, v);
            }
            u = fa[top[u]];
        }
        if (deep[u] > deep[v])
            swap(u, v);
        return u;
    }
} lca;

void bfs() {
    *in = 0;
    queue<int> que;
    que.push(1);
    while (!que.empty()) {
        int u = que.front();
        que.pop();
        in[u] = ++(*in);
        for (auto &v : G[u]) {
            que.push(v);
        }
    }
    vector<int> vec;
    for (int i = 1; i <= n; ++i) vec.push_back(i);
    sort(vec.begin(), vec.end(), [&](int x, int y) {
        return in[x] < in[y];
    });
    for (int i = 0; i < n; ++i) {
        mergeVec[deep[vec[i]]].push_back(pII(1, vec[i]));
        if (i == 0)
            continue;
        if (deep[vec[i - 1]] == deep[vec[i]]) {
            int u = vec[i - 1], v = vec[i];
            mergeVec[deep[vec[i]] - deep[lca.query(u, v)]].push_back(pII(u, v));
        }
    }
}

int main() {
    inv[1] = 1;
    for (int i = 2; i < N; ++i) inv[i] = 1ll * inv[mod % i] * (mod - mod / i) % mod;
    while (scanf("%d", &n) != EOF) {
        G.clear();
        G.resize(n + 5);
        mergeVec.clear();
        mergeVec.resize(n + 5);
        for (int i = 2; i <= n; ++i) {
            scanf("%d", fa + i);
            G[fa[i]].push_back(i);
        }
        ufs.init(n);
        lca.init(1);
        bfs();
        res = 1;
        for (int i = 1; i <= n; ++i) chadd(res, res);
        int ans = 0;
        for (int i = 1; i <= n; ++i) {
            chadd(ans, res - (n + 1));
            for (auto &it : mergeVec[i]) ufs.join(it.fi, it.se);
        }
        printf("%d\n", ans);
    }
    return 0;
}
