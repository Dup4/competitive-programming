#include <bits/stdc++.h>
using namespace std;

#define N 1000010
#define pii pair<int, int>
#define fi first
#define se second
int n, m;
int del[N];
vector<vector<pii> > G;
int d[N], a[N];
int e[N][2];

int main() {
    while (scanf("%d%d", &n, &m) != EOF) {
        memset(del, 0, sizeof del);
        memset(d, 0, sizeof d);
        G.clear();
        G.resize(n + 1);
        int needdel = m - (n + m + 1) / 2;
        for (int i = 1, u, v; i <= m; ++i) {
            scanf("%d%d", &e[i][0], &e[i][1]);
            u = e[i][0], v = e[i][1];
            G[u].push_back(pii(v, i));
            G[v].push_back(pii(u, i));
            ++d[u];
            ++d[v];
        }
        if (needdel <= 0) {
            printf("%d\n", m);
            for (int i = 1; i <= m; ++i) {
                printf("%d %d\n", e[i][0], e[i][1]);
            }
            continue;
        }
        priority_queue<pii, vector<pii>, greater<pii> > pq;
        for (int i = 1; i <= n; ++i) {
            d[i] = d[i] - (d[i] + 1) / 2;
            pq.push(pii(d[i], i));
        }
        int u, v;
        while (needdel > 0) {
            u = 0;
            while (!pq.empty()) {
                u = pq.top().se;
                pq.pop();
                if (d[u] <= 0) {
                    u = 0;
                    continue;
                } else
                    break;
            }
            if (u == 0)
                break;
            sort(G[u].begin(), G[u].end(), [](pii x, pii y) {
                return d[x.fi] > d[y.fi];
            });
            for (auto it : G[u]) {
                if (del[it.se])
                    continue;
                v = it.fi;
                if (d[v] <= 0)
                    continue;
                del[it.se] = 1;
                --d[u];
                --needdel;
                --d[v];
                if (d[v] > 0) {
                    pq.push(pii(d[v], v));
                }
                if (d[u] <= 0 || needdel <= 0)
                    break;
            }
        }
        int sze = (n + m + 1) / 2;
        printf("%d\n", sze);
        int cnt = 0;
        for (int i = 1; i <= m; ++i) {
            if (del[i] == 0) {
                ++cnt;
                printf("%d %d\n", e[i][0], e[i][1]);
            }
        }
        assert(sze == cnt);
    }
    return 0;
}
