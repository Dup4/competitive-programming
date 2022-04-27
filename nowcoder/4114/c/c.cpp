#include <bits/stdc++.h>
using namespace std;
int n, m;
vector<vector<int>> G;

struct E {
    int dis[18];
} f[(1 << 17) + 5];

int main() {
    while (scanf("%d%d", &n, &m) != EOF) {
        G.clear();
        G.resize(n + 1);
        for (int i = 1, u, v; i <= m; ++i) {
            scanf("%d%d", &u, &v);
            G[u].push_back(v);
            G[v].push_back(u);
        }
        memset(f, 0x3f, sizeof f);
        memset(f[0].dis, 0, sizeof f[0].dis);
        for (int i = 1; i < (1 << n); ++i) {
            for (int j = 0; j < n; ++j) {
                if ((i >> j) & 1) {
                    int pre = (i ^ (1 << j));
                    E tmp = f[pre];
                    tmp.dis[j + 1] = 0;
                    for (auto &v : G[j + 1]) {
                        if ((pre >> (v - 1)) & 1) {
                            tmp.dis[j + 1] = max(tmp.dis[j + 1], f[pre].dis[v] + 1);
                            tmp.dis[0] = max(tmp.dis[0], tmp.dis[j + 1]);
                        }
                    }
                    if (tmp.dis[0] < f[i].dis[0])
                        f[i] = tmp;
                }
            }
        }
        printf("%d\n", f[(1 << n) - 1].dis[0]);
    }
    return 0;
}
