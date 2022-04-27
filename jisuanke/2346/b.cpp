#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pii pair<int, int>
#define fi first
#define se second
#define N 1010
const int p = 1e9 + 7;
int n, m;
int f[N][N], S[N];
vector<vector<vector<int> > > g;
int gcd(int a, int b) {
    return b ? gcd(b, a % b) : a;
}
vector<vector<pii> > G;
void add(int &x, int y) {
    x += y;
    if (x >= p) {
        x -= p;
    }
}
void sub(int &x, int y) {
    x -= y;
    if (x < 0) {
        x += p;
    }
}
void DFS(int u, int fa) {
    for (int i = 1; i <= m; ++i) {
        f[u][i] = 0;
    }
    for (auto it : G[u])
        if (it.fi != fa) {
            DFS(it.fi, u);
        }
    for (int i = 1; i <= m; ++i) {
        int tot = 1;
        for (auto it : G[u])
            if (it.fi != fa) {
                int tmp = S[it.fi];
                for (auto it2 : g[i][it.se]) {
                    sub(tmp, f[it.fi][it2]);
                }
                tot = 1ll * tot * tmp % p;
            }
        f[u][i] = tot;
    }
    S[u] = 0;
    for (int i = 1; i <= m; ++i) {
        add(S[u], f[u][i]);
    }
}

int main() {
    while (scanf("%d%d", &n, &m) != EOF) {
        g.clear();
        g.resize(m + 1);
        for (int i = 1; i <= m; ++i) {
            g[i].resize(m + 1);
        }
        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= m; ++j) {
                int GCD = gcd(i, j);
                g[i][GCD].push_back(j);
            }
        }
        G.clear();
        G.resize(n + 1);
        for (int i = 1, u, v, w; i < n; ++i) {
            scanf("%d%d%d", &u, &v, &w);
            G[u].push_back(pii(v, w));
            G[v].push_back(pii(u, w));
        }
        DFS(1, 1);
        int res = S[1];
        printf("%d\n", res);
    }
    return 0;
}
