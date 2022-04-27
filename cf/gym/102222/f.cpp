#include <bits/stdc++.h>
using namespace std;

#define pii pair<int, int>
#define fi first
#define se second
const int N = 220;
const int M = 2e4 + 10;
int n, q, G[N][N], res[M];
pii w[N];
struct qnode {
    int u, v, w, id;
    qnode() {}
    void scan(int _id) {
        id = _id;
        scanf("%d%d%d", &u, &v, &w);
    }
    bool operator<(const qnode &other) const {
        return w < other.w;
    }
} qrr[M];

void floyd(int k) {
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            G[i][j] = min(G[i][j], G[i][k] + G[k][j]);
        }
    }
}

int main() {
    int T;
    scanf("%d", &T);
    for (int kase = 1; kase <= T; ++kase) {
        printf("Case #%d:\n", kase);
        scanf("%d%d", &n, &q);
        for (int i = 1; i <= n; ++i) {
            scanf("%d", &w[i].fi);
            w[i].se = i;
        }
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= n; ++j) scanf("%d", G[i] + j);
        for (int i = 1; i <= q; ++i) qrr[i].scan(i);
        sort(w + 1, w + 1 + n);
        sort(qrr + 1, qrr + 1 + q);
        int now = 1;
        for (int i = 1; i <= q; ++i) {
            while (now <= n && w[now].fi <= qrr[i].w) {
                floyd(w[now].se);
                ++now;
            }
            res[qrr[i].id] = G[qrr[i].u][qrr[i].v];
        }
        for (int i = 1; i <= q; ++i) printf("%d\n", res[i]);
    }
    return 0;
}
