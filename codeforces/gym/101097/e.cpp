#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pii pair<int, int>
#define fi first
#define se second
const int N = 1e6 + 10;
int n;
vector<vector<int>> G;
ll f[N], g[N], res[N];
pii mf[N][2];
int sze[N], fa[N], mg[N];
void DFS(int u) {
    sze[u] = 1;
    f[u] = 0;
    mf[u][0] = pii(0, u);
    mf[u][1] = pii(-1, -1);
    for (auto v : G[u])
        if (v != fa[u]) {
            fa[v] = u;
            DFS(v);
            sze[u] += sze[v];
            f[u] += f[v] + sze[v];
            if (mf[v][0].fi + 1 > mf[u][0].fi) {
                mf[u][1] = mf[u][0];
                mf[u][0] = mf[v][0];
                ++mf[u][0].fi;
                mf[u][0].se = v;
            } else if (mf[v][0].fi + 1 > mf[u][1].fi) {
                mf[u][1] = mf[v][0];
                ++mf[u][1].fi;
                mf[u][1].se = v;
            }
        }
}
void DFS2(int u) {
    for (auto v : G[u])
        if (v != fa[u]) {
            g[v] = 0;
            g[v] += n - sze[v];
            g[v] += g[u];
            g[v] += f[u] - sze[v] - f[v];
            mg[v] = mg[u] + 1;
            if (mf[u][0].se == v) {
                mg[v] = max(mg[v], mf[u][1].fi + 1);
            } else {
                mg[v] = max(mg[v], mf[u][0].fi + 1);
            }
            DFS2(v);
        }
}

int main() {
    freopen("inspection.in", "r", stdin);
    freopen("inspection.out", "w", stdout);
    while (scanf("%d", &n) != EOF) {
        G.clear();
        G.resize(n + 1);
        for (int i = 1, u, v; i < n; ++i) {
            scanf("%d%d", &u, &v);
            G[u].push_back(v);
            G[v].push_back(u);
        }
        //	if (n == 1) {
        //		puts("0");
        //		continue;
        //	} else if (n == 2) {
        //		puts("1\n1");
        //		continue;
        //	}
        g[1] = 0;
        mg[1] = 0;
        DFS(1);
        DFS2(1);
        //	for (int i = 1; i <= n; ++i)
        //		printf("%d %d %d %d %d %lld %lld %d\n", i, mf[i][0].fi, mf[i][0].se, mf[i][1].fi, mf[i][1].se,
        // f[i], g[i], mg[i]);
        for (int u = 1; u <= n; ++u) {
            int Max = 0, num;
            for (auto v : G[u])
                if (v != fa[u]) {
                    if (sze[v] > Max) {
                        Max = sze[v];
                        num = mf[v][0].fi + 1;
                    }
                }
            if (n - sze[u] > Max) {
                Max = max(Max, n - sze[u]);
                num = mg[u];
            }
            // cout << u << " " << mf[u][0].fi << " " << mg[u] << endl;
            if (Max > n - 1 - Max + 1) {
                res[u] = -1;
            } else {
                res[u] = 2ll * (f[u] + g[u]);
                //	cout << u << " " << res[u] << endl;
                if (Max == n - 1 - Max + 1) {
                    res[u] -= num;
                } else {
                    res[u] -= max(mf[u][0].fi, mg[u]);
                    //	cout << u << " " << res[u] << endl;
                }
            }
        }
        for (int i = 1; i <= n; ++i) printf("%lld\n", res[i]);
    }
    return 0;
}
