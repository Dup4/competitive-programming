#include <bits/stdc++.h>
using namespace std;
using pII = pair<int, int>;
#define fi first
#define se second
template <class T1, class T2>
void chmax(T1 &x, T2 y) {
    if (x < y)
        x = y;
}
template <class T1, class T2>
void chmin(T1 &x, T2 y) {
    if (x > y)
        x = y;
}
const int N = 1e5 + 10, M = 22, INF = 0x3f3f3f3f;
vector<vector<pII>> G;
vector<int> white;
// 0 白点 1 黑点
int n, max_dis[N], col[N];

struct E {
    int a, b, c;
    E(int a = 0, int b = 0, int c = 0) : a(a), b(b), c(c) {}
    void up(E other) {
        chmax(a, other.a);
        chmin(b, other.b);
        chmax(c, other.c);
    }
    int query(E other) {
        int res = a - other.b;
        chmax(res, other.a - b);
        chmax(res, c);
        chmax(res, other.c);
        return res;
    }
};

struct LCA {
    int fa[N][M], Max[N][M], Min[N][M], deg[N];
    void bfs() {
        queue<int> que;
        deg[1] = 0;
        fa[1][0] = 1;
        Max[1][0] = -INF;
        Min[1][0] = INF;
        que.push(1);
        while (!que.empty()) {
            int u = que.front();
            que.pop();
            for (int i = 1; i < M; ++i) {
                Max[u][i] = max(Max[u][i - 1], Max[fa[u][i - 1]][i - 1]);
                Min[u][i] = min(Min[u][i - 1], Min[fa[u][i - 1]][i - 1]);
                fa[u][i] = fa[fa[u][i - 1]][i - 1];
            }
            for (auto &it : G[u]) {
                int v = it.fi, w = it.se;
                if (v == fa[u][0])
                    continue;
                deg[v] = deg[u] + 1;
                fa[v][0] = u;
                Max[v][0] = Min[v][0] = w;
                que.push(v);
            }
        }
    }
    E dis(int u, int v) {
        if (u == v)
            return E(-INF, INF, 0);
        if (deg[u] > deg[v])
            swap(u, v);
        int ma = -INF, mi = INF, hu = deg[u], hv = deg[v], tu = u, tv = v;
        for (int det = hv - hu, i = 0; det; det >>= 1, ++i) {
            if (det & 1) {
                ma = max(ma, Max[tv][i]);
                mi = min(mi, Min[tv][i]);
                tv = fa[tv][i];
            }
        }
        if (tu == tv)
            return E(ma, mi, ma - mi);
        for (int i = M - 1; i >= 0; --i) {
            if (fa[tu][i] == fa[tv][i])
                continue;
            ma = max(ma, max(Max[tu][i], Max[tv][i]));
            mi = min(mi, min(Min[tu][i], Min[tv][i]));
            tu = fa[tu][i];
            tv = fa[tv][i];
        }
        ma = max(ma, max(Max[tu][0], Max[tv][0]));
        mi = min(mi, min(Min[tu][0], Min[tv][0]));
        return E(ma, mi, ma - mi);
    }
} lca;

struct PD {
    int all, rt, vis[N], sze[N], f[N], fa[N];
    E info, g[N];
    void findrt(int u, int fa) {
        sze[u] = 1;
        f[u] = 0;
        for (auto &it : G[u]) {
            int v = it.fi;
            if (v == fa || vis[v])
                continue;
            findrt(v, u);
            sze[u] += sze[v];
            f[u] = max(f[u], sze[v]);
        }
        f[u] = max(f[u], all - sze[u]);
        if (f[u] < f[rt])
            rt = u;
    }
    void dfs(int u, int pre, int ma, int mi) {
        chmax(max_dis[u], info.query(E(ma, mi, ma - mi)));
        if (col[u]) {
            chmax(max_dis[rt], ma - mi);
        }
        for (auto &it : G[u]) {
            int v = it.fi, w = it.se;
            if (v == pre || vis[v])
                continue;
            dfs(v, u, max(ma, w), min(mi, w));
        }
    }
    void up(int u, int pre, int ma, int mi) {
        if (col[u]) {
            info.up(E(ma, mi, ma - mi));
        }
        for (auto &it : G[u]) {
            int v = it.fi, w = it.se;
            if (v == pre || vis[v])
                continue;
            up(v, u, max(ma, w), min(mi, w));
        }
    }
    void gao(int u, int ff) {
        vis[u] = 1;
        fa[u] = ff;
        info = E(-INF, INF, 0);
        for (auto &it : G[u]) {
            int v = it.fi, w = it.se;
            if (vis[v])
                continue;
            dfs(v, u, w, w);
            up(v, u, w, w);
        }
        info = E(-INF, INF, 0);
        reverse(G[u].begin(), G[u].end());
        for (auto &it : G[u]) {
            int v = it.fi, w = it.se;
            if (vis[v])
                continue;
            dfs(v, u, w, w);
            up(v, u, w, w);
        }
        for (auto &it : G[u]) {
            int v = it.fi;
            if (vis[v])
                continue;
            all = f[0] = sze[v];
            rt = 0;
            findrt(v, 0);
            gao(rt, u);
        }
    }
    void init() {
        for (int i = 0; i <= n; ++i) vis[i] = 0;
        all = f[0] = n;
        rt = 0;
        findrt(1, 0);
        gao(rt, 0);
        for (int i = 1; i <= n; ++i) {
            g[i] = E(-INF, INF, 0);
            vis[i] = 0;
        }
    }
    void add(int u) {
        vis[u] = 1;
        int it = u;
        while (it) {
            g[it].up(lca.dis(u, it));
            it = fa[it];
        }
    }
    int query(int u) {
        int it = fa[u];
        int res = 0;
        while (it) {
            E t = lca.dis(u, it);
            if (vis[it]) {
                chmax(res, t.c);
            }
            chmax(res, t.query(g[it]));
            it = fa[it];
        }
        return res;
    }
} pd;

int main() {
    while (scanf("%d", &n) != EOF) {
        for (int i = 0; i <= n; ++i) max_dis[i] = 0;
        G.clear();
        G.resize(n + 1);
        white.clear();
        for (int i = 1; i <= n; ++i) scanf("%d", col + i);
        for (int i = 1, u, v, w; i < n; ++i) {
            scanf("%d%d%d", &u, &v, &w);
            G[u].push_back(pII(v, w));
            G[v].push_back(pII(u, w));
        }
        lca.bfs();
        pd.init();
        for (int i = 1; i <= n; ++i)
            if (col[i] == 0)
                white.push_back(i);
        sort(white.begin(), white.end(), [&](int x, int y) {
            return max_dis[x] < max_dis[y];
        });
        int res_pos = 0, res_dis = max_dis[white[0]];
        //按顺序枚举
        int bord = 0, sze = white.size();
        for (int i = 1; i <= n; ++i)
            if (!col[i]) {
                while (bord < sze) {
                    int now = pd.query(i);
                    if (now > res_dis) {
                    }
                }
            }
        printf("%d %d\n", res_pos, res_dis);
    }
    return 0;
}
