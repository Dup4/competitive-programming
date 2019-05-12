#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 200010
int n;
struct Graph {
    struct node {
        int to, nx, w;
        node () {}
        node (int to, int nx, int w) : to(to), nx(nx), w(w) {}
    }a[N << 1];
    int head[N], pos;
    void init(int n) {
        for (int i = 1; i <= n; ++i) {
            head[i] = 0;
        }
        pos = 0;
    }
    void add(int u, int v, int w) {
        a[++pos] = node(v, head[u], w); head[u] = pos;
        a[++pos] = node(u, head[v], w); head[v] = pos;
    }
}G;
#define erp(u) for (int it = G.head[u], v = G.a[it].to, w = G.a[it].w; it; it = G.a[it].nx, v = G.a[it].to, w = G.a[it].w)

ll res;
int vis[N];
int fa[N], sze[N], f[N], sum, root;
void getroot(int u, int fa) {
    sze[u] = 1;
    f[u] = 0;
    erp(u) if (!vis[v] && v != fa) {
        getroot(v, u); 
        sze[u] += sze[v];
        f[u] = max(f[u], sze[v]);
    }
    f[u] = max(f[u], sum - sze[u]);
    if (f[u] < f[root]) {
        root = u;
    }
}

int cnt[4];
int deep[N];
void getdeep(int u, int fa) {
    res += cnt[(3 - deep[u]) % 3];
    erp(u) if (!vis[v] && v != fa) {
        deep[v] = (deep[u] + w) % 3;
        getdeep(v, u);
    }
}

void add(int u, int fa) {
    ++cnt[deep[u]];
    erp(u) if (!vis[v] && v != fa) {
        add(v, u);
    }
}

void solve(int u) {
    vis[u] = 1;
    cnt[0] = 1; cnt[1] = 0; cnt[2] = 0;
    deep[u] = 0;
    erp(u) if (!vis[v]) {
        deep[v] = w % 3;
        getdeep(v, u);
        add(v, u);
    }
    erp(u) if (!vis[v]) {
        sum = f[0] = sze[v]; root = 0;
        getroot(v, 0);
        solve(root);
    }
}

void init(int n) {
    G.init(n);
    for (int i = 1; i <= n; ++i) {
        vis[i] = 0;
    }
}
int main() {
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        init(n);
        for (int i = 1, u, v, w; i < n; ++i) {
            scanf("%d%d%d", &u, &v, &w);
            G.add(u, v, w);
        }
        res = 0;
        sum = f[0] = n; root = 0;
        getroot(1, 0);
        solve(root);
        printf("%lld\n", res);
    }
    return 0;
}
