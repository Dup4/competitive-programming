#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 400010
int n, a[N];
vector<vector<int>> G;
// 0 表示当前点不选
// 1 表示当前点链的一端
// 2 表示当前点是拐点
// 第三维表示已经选了0, 1, 2, 3条链
ll f[N][3][4];

void Max(ll &x, ll y) {
    if (x < y)
        x = y;
}
void DFS(int u, int fa) {
    f[u][1][0] = a[u];
    for (auto v : G[u])
        if (v != fa) {
            DFS(v, u);
            //转移2状态
            for (int k = 2; ~k; --k) {
                for (int i = k, j; ~i; --i) {
                    j = k - i;
                    //链+链
                    Max(f[u][2][k], f[u][1][i] + f[v][1][j]);
                    //拐点+空
                    Max(f[u][2][k], f[u][2][i] + f[v][0][j]);
                }
            }

            //转移1状态
            for (int k = 2; ~k; --k) {
                for (int i = k, j; ~i; --i) {
                    j = k - i;
                    Max(f[u][1][k], f[u][0][i] + a[u] + f[v][1][j]);
                    Max(f[u][1][k], f[u][1][i] + f[v][0][j]);
                }
            }

            //转移0状态
            for (int k = 3; ~k; --k) {
                for (int i = k, j; ~i; --i) {
                    j = k - i;
                    f[u][0][k] = max(f[u][0][k], f[u][0][i] + f[v][0][j]);
                    if (j) {
                        f[u][0][k] = max(f[u][0][k], f[u][0][i] + f[v][1][j - 1]);
                        f[u][0][k] = max(f[u][0][k], f[u][0][i] + f[v][2][j - 1]);
                    }
                }
            }
        }
    for (int k = 3; k; --k) {
        Max(f[u][0][k], f[u][1][k - 1]);
        Max(f[u][0][k], f[u][2][k - 1]);
    }
}

int main() {
    while (scanf("%d", &n) != EOF) {
        memset(f, 0, sizeof f);
        G.clear();
        G.resize(n + 1);
        for (int i = 1; i <= n; ++i) {
            scanf("%d", a + i);
        }
        for (int i = 1, u, v; i < n; ++i) {
            scanf("%d%d", &u, &v);
            G[u].push_back(v);
            G[v].push_back(u);
        }
        DFS(1, 0);
        printf("%lld\n", f[1][0][3]);
    }
    return 0;
}
