#include <bits/stdc++.h>
using namespace std;
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
void err(const T& arg, const Ts&... args) {
    cout << arg << ' ';
    err(args...);
}
const int N = 2e6 + 10;
int n, m, e[N][2], w[N], fa[N], deep[N], vis[N];
vector<vector<int>> G;
ll res;

inline ll calc(ll x) {
    return x * (x - 1) >> 1;
}

struct UFS {
    int fa[N], sze[N];
    void init(int n) {
        for (int i = 1; i <= n; ++i) {
            fa[i] = 0;
            sze[i] = 1;
        }
    }
    int find(int u) {
        return fa[u] == 0 ? u : fa[u] = find(fa[u]);
    }
    bool join(int x, int y) {
        int fx = find(x), fy = find(y);
        if (fx != fy) {
            fa[fx] = fy;
            res -= calc(sze[fx]);
            res -= calc(sze[fy]);
            sze[fy] += sze[fx];
            res += calc(sze[fy]);
            return true;
        }
        return false;
    }
} ufs;

void dfs(int u) {
    vis[u] = 1;
    for (auto& v : G[u])
        if (v != fa[u]) {
            fa[v] = u;
            deep[v] = deep[u] + 1;
            dfs(v);
        }
}

int main() {
    int _T;
    scanf("%d", &_T);
    while (_T--) {
        scanf("%d%d", &n, &m);
        G.clear();
        G.resize(n + 1);
        ufs.init(n);
        for (int i = 1, u, v; i <= m; ++i) {
            scanf("%d%d", e[i], e[i] + 1);
            u = e[i][0], v = e[i][1];
            if (ufs.join(u, v)) {
                w[i] = 0;
                G[u].push_back(v);
                G[v].push_back(u);
            } else {
                w[i] = 1;
            }
        }
        memset(vis, 0, sizeof(vis[0]) * (n + 5));
        for (int i = 1; i <= n; ++i) {
            if (!vis[i]) {
                fa[i] = i;
                deep[i] = 0;
                dfs(i);
            }
        }
        ufs.init(n);
        res = 0;
        ll ans = 0;
        for (int i = 1; i <= m; ++i) {
            if (w[i]) {
                int u = e[i][0], v = e[i][1];
                int fu = ufs.find(u), fv = ufs.find(v);
                while (fu != fv) {
                    if (deep[fu] > deep[fv])
                        fu = ufs.find(fa[fu]);
                    else
                        fv = ufs.find(fa[fv]);
                }
                for (u = ufs.find(u); u != fu; u = ufs.find(fa[u])) ufs.join(u, fu);
                for (v = ufs.find(v); v != fv; v = ufs.find(fa[v])) ufs.join(v, fv);
            }
            ans ^= res * i;
        }
        printf("%lld\n", ans);
    }
    return 0;
}
