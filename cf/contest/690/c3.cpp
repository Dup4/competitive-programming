#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 10;
const int M = 23;
int n, fa[N][M], dep[N], dis[N][M], u, v;
int getdis(int u, int v) {
    if (u == v)
        return 0;
    if (dep[u] > dep[v])
        swap(u, v);
    int res = 0, hu = dep[u], hv = dep[v], tu = u, tv = v;
    for (int det = hv - hu, i = 0; det; det >>= 1, ++i) {
        if (det & 1) {
            res += dis[tv][i];
            tv = fa[tv][i];
        }
    }
    if (tu == tv)
        return res;
    for (int i = M - 1; i >= 0; --i) {
        if (fa[tu][i] == fa[tv][i])
            continue;
        res += dis[tu][i] + dis[tv][i];
        tu = fa[tu][i], tv = fa[tv][i];
    }
    return res + dis[tu][0] + dis[tv][0];
}

inline void gao(int x) {
    int t1 = getdis(u, v), t2 = getdis(x, u), t3 = getdis(x, v);
    if (t1 < t2 || t1 < t3) {
        if (t2 > t3)
            v = x;
        else
            u = x;
    }
}

int main() {
    while (scanf("%d", &n) != EOF) {
        dep[1] = 0;
        for (int i = 0; i < M; ++i) fa[1][i] = 1, dis[1][i] = 0;
        u = v = 1;
        for (int i = 2, p; i <= n; ++i) {
            scanf("%d", &p);
            fa[i][0] = p;
            dep[i] = dep[p] + 1;
            dis[i][0] = 1;
            for (int j = 1; j < M; ++j) {
                fa[i][j] = fa[fa[i][j - 1]][j - 1];
                dis[i][j] = dis[i][j - 1] + dis[fa[i][j - 1]][j - 1];
            }
            gao(i);
            printf("%d%c", getdis(u, v), " \n"[i == n]);
        }
    }
    return 0;
}
