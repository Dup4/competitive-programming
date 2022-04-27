#include <bits/stdc++.h>
using namespace std;

#define ll long long
const int N = 1050 + 10;
const int M = 1 << 10;
const int p = 1e9 + 7;
const int inv2 = 5e8 + 4;
const int len = 1 << 10;
int n, m, v[N];
vector<vector<int>> G;

void FWT(int *a, int opt) {
    for (int i = 1; i < len; i <<= 1) {
        for (int o = i << 1, j = 0; j < len; j += o) {
            for (int k = 0; k < i; ++k) {
                int X = a[j + k], Y = a[i + j + k];
                a[j + k] = (X + Y) % p;
                a[i + j + k] = (X + p - Y) % p;
                if (opt == -1) {
                    a[j + k] = 1ll * a[j + k] * inv2 % p;
                    a[i + j + k] = 1ll * a[i + j + k] * inv2 % p;
                }
            }
        }
    }
}

int f[N][M], fa[N], res[N];
void DFS(int u) {
    f[u][v[u]] = 1;
    FWT(f[u], 1);
    for (auto v : G[u])
        if (v != fa[u]) {
            fa[v] = u;
            DFS(v);
            for (int i = 0; i < M; ++i) f[u][i] = 1ll * f[u][i] * f[v][i] % p;
        }
    FWT(f[u], -1);
    f[u][0] = (f[u][0] + 1) % p;
    FWT(f[u], 1);
}

int main() {
    int _T;
    scanf("%d", &_T);
    while (_T--) {
        scanf("%d%d", &n, &m);
        G.clear();
        G.resize(n + 1);
        for (int i = 1; i <= n; ++i) scanf("%d", v + i);
        for (int i = 1, u, v; i < n; ++i) {
            scanf("%d%d", &u, &v);
            G[u].push_back(v);
            G[v].push_back(u);
        }
        memset(f, 0, sizeof f);
        memset(res, 0, sizeof res);
        DFS(1);
        for (int i = 1; i <= n; ++i) {
            FWT(f[i], -1);
            f[i][0] = (f[i][0] + p - 1) % p;
            for (int j = 0; j < m; ++j) res[j] = (res[j] + f[i][j]) % p;
        }
        for (int i = 0; i < m; ++i) printf("%d%c", res[i], " \n"[i == m - 1]);
    }
    return 0;
}
