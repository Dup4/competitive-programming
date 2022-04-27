#include <bits/stdc++.h>
using namespace std;

#define ll long long
const int N = 1e5 + 10;
const ll INF = 0x3f3f3f3f3f3f3f3f;
int n, k, d[N], sze[N];
struct Graph {
    struct node {
        int to, nx, w;
        node() {}
        node(int to, int nx, int w) : to(to), nx(nx), w(w) {}
    } a[N << 1];
    int head[N], pos;
    void init(int n) {
        memset(head, 0, sizeof(head[0]) * (n + 1));
        pos = 0;
    }
    void add(int u, int v, int w) {
        a[++pos] = node(v, head[u], w);
        head[u] = pos;
        a[++pos] = node(u, head[v], w);
        head[v] = pos;
    }
} G;
#define erp(u) \
    for (int it = G.head[u], v = G.a[it].to, w = G.a[it].w; it; it = G.a[it].nx, v = G.a[it].to, w = G.a[it].w)

ll f[N][110];
void DFS(int u, int pre) {
    for (int i = 0; i <= k; ++i) f[u][i] = INF;
    f[u][0] = 0;
    sze[u] = 0;
    if (d[u] == 1) {
        sze[u] = 1;
        f[u][1] = 0;
        return;
    }
    erp(u) if (v != pre) {
        DFS(v, u);
        int limit = min(k, sze[u] + sze[v]);
        for (int i = sze[u]; i >= 0; --i) {
            for (int j = min(sze[v], limit - i); j >= 0; --j) {
                f[u][i + j] = min(f[u][i + j], f[u][i] + f[v][j] + 1ll * w * j * (k - j));
            }
        }
        sze[u] = limit;
    }
}

int main() {
    int T;
    scanf("%d", &T);
    for (int kase = 1; kase <= T; ++kase) {
        printf("Case #%d: ", kase);
        scanf("%d%d", &n, &k);
        G.init(n);
        memset(d, 0, sizeof(d[0]) * (n + 1));
        for (int i = 1, u, v, w; i < n; ++i) {
            scanf("%d%d%d", &u, &v, &w);
            G.add(u, v, w);
            ++d[u], ++d[v];
        }
        if (n == 1) {
            puts("0");
        } else if (n == 2) {
            if (k == 1)
                puts("0");
            else
                printf("%d\n", G.a[1].w);
        } else {
            int rt = 1;
            for (int i = 1; i <= n; ++i)
                if (d[i] > 1) {
                    rt = i;
                    break;
                }
            DFS(rt, rt);
            printf("%lld\n", f[rt][k]);
        }
    }
    return 0;
}
