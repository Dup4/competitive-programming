#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pII = pair<int, int>;
#define fi first
#define se second
const int N = 2e5 + 10;
int n, m, q, a[N], d[N], e[N][3], big[N], S = 450;
ll f[N][2], g[3];
vector<vector<pII>> G;
vector<int> vec;
void up(int u, int vis) {
    for (auto &it : G[u]) {
        int v = it.fi, w = it.se;
        if (big[u] == big[v]) {
            g[a[u] + a[v]] += w * vis;
        } else {
            f[v][a[u]] += w * vis;
        }
    }
}

int main() {
    int kase = 1;
    while (scanf("%d%d", &n, &m) != EOF) {
        printf("Case %d:\n", kase++);
        S = sqrt(n + m) + 10;
        G.clear();
        G.resize(n + 1);
        for (int i = 0; i <= n; ++i) {
            d[i] = big[i] = f[i][0] = f[i][1] = 0;
        }
        memset(g, 0, sizeof g);
        vec.clear();
        for (int i = 1; i <= n; ++i) scanf("%d", a + i);
        for (int i = 1; i <= m; ++i) {
            scanf("%d%d%d", e[i], e[i] + 1, e[i] + 2);
            ++d[e[i][0]];
            ++d[e[i][1]];
        }
        for (int i = 1; i <= n; ++i) {
            if (d[i] >= S) {
                big[i] = 1;
                vec.push_back(i);
            }
        }
        //		assert(1);
        //	assert(vec.size() <= S + 10);
        for (int i = 1; i <= m; ++i) {
            int u = e[i][0], v = e[i][1], w = e[i][2];
            if (big[u] == big[v]) {
                G[u].push_back(pII(v, w));
                G[v].push_back(pII(u, w));
            } else {
                if (big[u])
                    swap(u, v);
                G[u].push_back(pII(v, w));
                f[v][a[u]] += w;
            }
        }
        for (int u = 1; u <= n; ++u) {
            for (auto &it : G[u]) {
                int v = it.fi, w = it.se;
                if (v > u || big[u] != big[v])
                    continue;
                g[a[u] + a[v]] += w;
            }
        }
        //   for (int i = 1; i <= n; ++i) assert(G[i].size() <= S + 100);
        scanf("%d", &q);
        char op[10];
        int x, y;
        while (q--) {
            scanf("%s%d", op, &x);
            if (op[0] == 'A') {
                scanf("%d", &y);
                if (x > y)
                    swap(x, y);
                ll res = g[x + y];
                for (auto &u : vec) {
                    if (a[u] <= y && a[u] >= x) {
                        res += f[u][x + y - a[u]];
                    }
                }
                printf("%lld\n", res);
            } else {
                up(x, -1);
                a[x] ^= 1;
                up(x, 1);
            }
        }
    }
    return 0;
}
