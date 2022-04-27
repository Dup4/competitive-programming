#include <bits/stdc++.h>
#define SZ(x) ((int)x.size())
using namespace std;
typedef long long ll;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const int N = 110;
int n, m;
int dist[20][20];
ll f[1 << 15][15];
vector<int> vec[1 << 15];

int main() {
    while (scanf("%d%d", &n, &m) != EOF) {
        memset(dist, -1, sizeof dist);
        memset(f, -1, sizeof f);
        for (int S = 0, len = (1 << n); S < len; ++S) {
            for (int i = 0; i < n; ++i)
                if ((S >> i) & 1)
                    vec[S].push_back(i + 1);
            if (SZ(vec[S]) == 1)
                f[S][*vec[S].begin()] = 0;
        }
        for (int i = 1, u, v, w; i <= m; ++i) {
            scanf("%d%d%d", &u, &v, &w);
            dist[u][v] = dist[v][u] = w;
        }
        ll res = 0;
        for (int S = 1; S < (1 << n); ++S) {
            for (auto &u : vec[S]) {
                // 枚举子集
                for (int T = (S - 1) & S; T != 0; T = (T - 1) & S) {
                    for (auto &v : vec[T]) {
                        if (dist[u][v] == -1 || f[T][v] == -1 || f[S - T][u] == -1)
                            continue;
                        f[S][u] =
                                max(f[S][u], f[T][v] + f[S - T][u] + 1ll * dist[u][v] * SZ(vec[T]) * (n - SZ(vec[T])));
                    }
                }
                if (S == (1 << n) - 1)
                    res = max(res, f[S][u]);
            }
        }
        printf("%lld\n", res);
    }
    return 0;
}
