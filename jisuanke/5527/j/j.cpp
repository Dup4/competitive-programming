#include <bits/stdc++.h>
using namespace std;
using pII = pair<int, int>;
using ll = long long;
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
#define fi first
#define se second
const int N = 1e5 + 10;
int n, m;
ll res, dis[N];
vector<vector<pII>> G[3];
vector<vector<int>> po;

int id[N];
struct UFS {
    int fa[N], sze[N];
    void init() {
        for (int i = 1; i <= n; ++i) {
            fa[i] = 0;
            sze[i] = 1;
        }
    }
    int find(int x) {
        return fa[x] == 0 ? x : fa[x] = find(fa[x]);
    }
    void merge(int x, int y) {
        int fx = find(x), fy = find(y);
        if (fx != fy) {
            if (sze[fx] > sze[fy])
                swap(fx, fy);
            fa[fx] = fy;
            sze[fy] += sze[fx];
        }
    }
} ufs;

int Insta[N];
pII fa[N];
void dfs(int u) {
    Insta[u] = 1;
    for (auto &it : G[0][u]) {
        int v = it.fi, w = it.se;
        if (v == fa[u].fi)
            continue;
        if (Insta[v]) {
            int now = u;
            G[2][now].emplace_back(u, w);
            G[2][u].emplace_back(now, w);
            while (now != v) {
                ufs.merge(now, fa[now].fi);
                res -= fa[now].se;
                G[2][now].emplace_back(fa[now].fi, fa[now].se);
                G[2][fa[now].fi].emplace_back(now, fa[now].se);
                now = fa[now].fi;
            }
        } else {
            fa[v] = pII(u, w);
            dfs(v);
        }
    }
    Insta[u] = 0;
}

void dfs1(int u, int fa) {
    Insta[u] = 1;
    for (auto &it : G[1][u]) {
        int v = it.fi, w = it.se;
        if (v == fa)
            continue;
        dis[v] = max(dis[v], dis[u] - w);
        if (!Insta[v]) {
            dfs1(v, u);
        }
    }
    Insta[u] = 0;
}

void dfs2(int u, int fa) {
    for (auto &it : po[u]) {
        for (auto &it2 : G[0][it]) {
            int v = it2.fi, w = it2.se;
            if (id[it] != id[v]) {
                dis[v] = max(dis[v], dis[it] + w);
            }
        }
    }
    for (auto &it : G[2][u]) {
        int v = it.fi;
        dfs1(it.se, it.se);
        if (v != fa) {
            dfs2(v, u);
        }
    }
}

int main() {
    while (scanf("%d%d", &n, &m) != EOF) {
        res = 0;
        memset(dis, 0, sizeof dis);
        for (int i = 0; i < 3; ++i) {
            G[i].clear();
            G[i].resize(n + 1);
        }
        for (int i = 1, u, v, w; i <= m; ++i) {
            scanf("%d%d%d", &u, &v, &w);
            G[0][u].emplace_back(v, w);
            G[0][v].emplace_back(u, w);
            res += 2 * w;
        }
        ufs.init();
        fa[1] = pII(0, 0);
        dfs(1);
        *id = 0;
        for (int i = 1; i <= n; ++i) {
            if (ufs.fa[i] == 0) {
                id[i] = ++*id;
            }
        }
        po.clear();
        po.resize(*id + 1);
        for (int i = 1; i <= n; ++i) {
            if (ufs.fa[i]) {
                id[i] = id[ufs.find(i)];
            }
            po[id[i]].push_back(i);
        }
        for (int i = 1; i <= n; ++i) dbg(i, id[i]);
        for (int u = 1; u <= n; ++u) {
            for (auto &it : G[0][u]) {
                int v = it.fi;
                if (id[u] != id[v]) {
                    G[2][id[u]].emplace_back(id[v], v);
                    G[2][id[v]].emplace_back(id[u], u);
                }
            }
        }
        dis[1] = 0;
        dfs1(1, 1);
        dfs2(id[1], id[1]);
        ll Max = 0;
        for (int i = 1; i <= n; ++i) {
            Max = max(Max, dis[i]);
        }
        printf("%lld\n", res - Max);
    }
    return 0;
}
