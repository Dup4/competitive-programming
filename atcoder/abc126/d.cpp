#include <bits/stdc++.h>
using namespace std;

#define N 100010
int n;
struct Graph {
    struct node {
        int to, nx, w;
        node() {}
        node(int to, int nx, int w) : to(to), nx(nx), w(w) {}
    } a[N << 1];
    int head[N], pos;
    void init() {
        memset(head, 0, sizeof head);
        pos = 0;
    }
    void add(int u, int v, int w) {
        w &= 1;
        a[++pos] = node(v, head[u], w);
        head[u] = pos;
        a[++pos] = node(u, head[v], w);
        head[v] = pos;
    }
} G;
#define erp(u) \
    for (int it = G.head[u], v = G.a[it].to, w = G.a[it].w; it; it = G.a[it].nx, v = G.a[it].to, w = G.a[it].w)

int res[N];
void DFS(int u, int fa) {
    erp(u) if (v != fa) {
        if (w & 1) {
            res[v] = res[u] ^ 1;
        } else {
            res[v] = res[u];
        }
        DFS(v, u);
    }
}

int main() {
    while (scanf("%d", &n) != EOF) {
        G.init();
        for (int i = 1, u, v, w; i < n; ++i) {
            scanf("%d%d%d", &u, &v, &w);
            G.add(u, v, w);
        }
        res[1] = 0;
        DFS(1, 1);
        for (int i = 1; i <= n; ++i) {
            printf("%d\n", res[i]);
        }
    }
    return 0;
}
