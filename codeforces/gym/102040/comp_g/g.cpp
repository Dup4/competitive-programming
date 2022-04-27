#include <bits/stdc++.h>
using namespace std;
using pII = pair<int, int>;
#define fi first
#define se second
template <class T1, class T2>
void chmin(T1 &x, T2 y) {
    if (x > y)
        x = y;
}
const int N = 1e5 + 10, M = 20, S = 200, INF = 0x3f3f3f3f;
vector<vector<int>> G;
int n, q, fa[N], dep[N], d_pos[N], d_posl[N], d_posr[N];
pII a[N];
struct LCA {
    int F[N << 1], P[N];
    struct RMQ {
        int Min[N << 1][M];
        int mm[N << 1], rmq[N << 1];
        void init(int n) {
            mm[0] = -1;
            for (int i = 1; i <= n; ++i) {
                mm[i] = ((i & (i - 1)) == 0) ? mm[i - 1] + 1 : mm[i - 1];
                Min[i][0] = i;
            }
            for (int j = 1; j <= mm[n]; ++j) {
                for (int i = 1; i + (1 << j) - 1 <= n; ++i) {
                    Min[i][j] = rmq[Min[i][j - 1]] < rmq[Min[i + (1 << (j - 1))][j - 1]]
                                        ? Min[i][j - 1]
                                        : Min[i + (1 << (j - 1))][j - 1];
                }
            }
        }
        int queryMin(int x, int y) {
            if (x > y)
                swap(x, y);
            int k = mm[y - x + 1];
            return rmq[Min[x][k]] <= rmq[Min[y - (1 << k) + 1][k]] ? Min[x][k] : Min[y - (1 << k) + 1][k];
        }
    } st;
    void dfs(int u) {
        F[++*F] = u;
        st.rmq[*F] = dep[u];
        P[u] = *F;
        for (auto &v : G[u])
            if (v != fa[u]) {
                fa[v] = u;
                dep[v] = dep[u] + 1;
                dfs(v);
                F[++*F] = u;
                st.rmq[*F] = dep[u];
            }
    }
    void init(int rt) {
        *F = 0;
        fa[rt] = rt;
        dep[rt] = 0;
        dfs(rt);
        st.init(2 * n - 1);
    }
    int query(int u, int v) {
        return F[st.queryMin(P[u], P[v])];
    }
    int dis(int u, int v) {
        return dep[u] + dep[v] - 2 * dep[query(u, v)];
    }
} lca;

struct HLD {
    int f[N];
    void init() {
        for (int i = 1; i <= n; ++i) f[i] = INF + INF;
    }
    void dfs(int u) {
        for (auto &v : G[u])
            if (v != fa[u]) {
                dfs(v);
                chmin(f[u], f[v]);
            }
    }
    void dfs2(int u) {
        f[u] -= 2 * dep[u];
        chmin(f[u], f[fa[u]]);
        for (auto &v : G[u])
            if (v != fa[u]) {
                dfs2(v);
            }
    }
    void up(int x) {
        chmin(f[x], dep[x]);
    }
    void gao() {
        dfs(1);
        dfs2(1);
    }
} hld[310];

int force(int x, int l, int r) {
    int res = INF;
    for (int i = l; i <= r; ++i) chmin(res, lca.dis(x, i));
    return res;
}

int query(int x, int l, int r) {
    if (l == -1 || r == -1)
        return INF;
    int res = INF;
    if (d_pos[l] == d_pos[r])
        chmin(res, force(x, l, r));
    else {
        chmin(res, force(x, l, d_posr[d_pos[l]]));
        for (int i = d_pos[l] + 1; i < d_pos[r]; ++i) chmin(res, hld[i].f[x] + dep[x]);
        chmin(res, force(x, d_posl[d_pos[r]], r));
    }
    return res;
}

int main() {
    for (int i = 1; i <= 100000; ++i) {
        d_pos[i] = (i - 1) / S + 1;
        if (i == 1 || d_pos[i] != d_pos[i - 1])
            d_posl[d_pos[i]] = i;
        d_posr[d_pos[i]] = i;
    }
    int _T;
    scanf("%d", &_T);
    for (int kase = 1; kase <= _T; ++kase) {
        printf("Case %d:\n", kase);
        for (int i = 1; i <= 100000; ++i) a[i] = pII(-1, -1);
        scanf("%d", &n);
        G.clear();
        G.resize(n + 1);
        for (int i = 1, u, v; i < n; ++i) {
            scanf("%d%d", &u, &v);
            G[u].push_back(v);
            G[v].push_back(u);
        }
        lca.init(1);
        for (int i = 1; i <= d_pos[n]; ++i) hld[i].init();
        for (int i = 1; i <= n; ++i) {
            hld[d_pos[i]].up(i);
        }
        for (int i = 1; i <= d_pos[n]; ++i) hld[i].gao();
        scanf("%d", &q);
        int op, l, r, x, m, p;
        while (q--) {
            scanf("%d", &op);
            if (op == 1) {
                scanf("%d%d%d", &x, &l, &r);
                a[x] = pII(l, r);
            } else if (op == 2) {
                scanf("%d", &x);
                a[x] = pII(-1, -1);
            } else {
                scanf("%d%d", &x, &m);
                int res = INF;
                for (int i = 1; i <= m; ++i) {
                    scanf("%d", &p);
                    chmin(res, query(x, a[p].fi, a[p].se));
                }
                if (res >= INF)
                    res = -1;
                printf("%d\n", res);
            }
        }
    }
    return 0;
}
