#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10, M = 1e4 + 10;
int n, q, a[N], ans;

struct Graph {
    struct E {
        int to, nx, w;
    } e[N << 1];
    int h[N], cnt;
    void init(int n) {
        for (int i = 0; i <= n; ++i) h[i] = -1;
        cnt = -1;
    }
    void addedge(int u, int v, int w = 0) {
        e[++cnt] = {v, h[u], w};
        h[u] = cnt;
    }
} G;

namespace MoTree {
Graph BG;
int blo, cnt;
int belong[N], fa[N];
struct Blocks {
    int a[256], sze;
    void ins(int x) {
        ++sze;
        int pos = sze;
        for (int i = sze; i > 1 && a[i - 1] > x; --i) a[i] = a[i - 1], pos = i - 1;
        a[pos] = x;
    }
    void modify(int x, int y) {
        int pos = lower_bound(a + 1, a + sze + 1, x) - a;
        for (; pos < sze && a[pos + 1] < y; ++pos) a[pos] = a[pos + 1];
        for (; pos > 1 && a[pos - 1] > y; --pos) a[pos] = a[pos - 1];
        a[pos] = y;
    }
    int query(int x) {
        int pos = upper_bound(a + 1, a + sze + 1, x) - a;
        return sze - pos + 1;
    }
} b[M];
void getk(int u, int x) {
    ans += b[u].query(x);
    for (int i = BG.h[u]; ~i; i = BG.e[i].nx) getk(BG.e[i].to, x);
}
void getans(int u, int x) {
    if (a[u] > x)
        ++ans;
    for (int i = G.h[u]; ~i; i = G.e[i].nx) {
        int v = G.e[i].to;
        if (v == fa[u])
            continue;
        if (belong[v] == belong[u])
            getans(v, x);
        else
            getk(belong[v], x);
    }
}
void modify(int u, int x) {
    b[belong[u]].modify(a[u], x);
    a[u] = x;
}
void addBlock(int u) {
    if (b[belong[fa[u]]].sze == blo) {
        belong[u] = ++cnt;
        b[cnt].ins(a[u]);
        BG.h[cnt] = -1;
        BG.addedge(belong[fa[u]], cnt);
    } else {
        b[belong[u] = belong[fa[u]]].ins(a[u]);
    }
}
void addItem(int u, int x) {
    a[++n] = x;
    G.h[n] = -1;
    G.addedge(u, n);
    G.addedge(n, u);
    fa[n] = u;
    addBlock(n);
}
void dfs(int u) {
    addBlock(u);
    for (int i = G.h[u]; ~i; i = G.e[i].nx) {
        int v = G.e[i].to;
        if (v == fa[u])
            continue;
        fa[v] = u;
        dfs(v);
    }
}
void init() {
    blo = (int)sqrt(n);
    cnt = 0;
    BG.init(1);
    fa[1] = 0;
    dfs(1);
}
}  // namespace MoTree

int main() {
    scanf("%d", &n);
    G.init(n);
    for (int i = 1, u, v; i < n; ++i) {
        scanf("%d%d", &u, &v);
        G.addedge(u, v);
        G.addedge(v, u);
    }
    for (int i = 1; i <= n; ++i) scanf("%d", a + i);
    MoTree::init();
    ans = 0;
    scanf("%d", &q);
    for (int i = 1; i <= q; ++i) {
        int opt, u, x;
        scanf("%d%d%d", &opt, &u, &x);
        u ^= ans;
        x ^= ans;
        if (opt == 0) {
            ans = 0;
            MoTree::getans(u, x);
            printf("%d\n", ans);
            ans = 0;
        } else if (opt == 1) {
            MoTree::modify(u, x);
        } else if (opt == 2) {
            MoTree::addItem(u, x);
        }
    }
}
