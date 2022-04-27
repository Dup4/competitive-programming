#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 200010
int n, vis[N];
ll res;
struct Graph {
    struct node {
        int to, nx, w;
        node() {}
        node(int to, int nx, int w) : to(to), nx(nx), w(w) {}
    } a[N << 1];
    int head[N], pos;
    void init(int n) {
        pos = 0;
        for (int i = 1; i <= n; ++i) {
            head[i] = -1;
        }
    }
    void add(int u, int v, int w) {
        a[pos] = node(v, head[u], w);
        head[u] = pos++;
        a[pos] = node(u, head[v], w);
        head[v] = pos++;
    }
} G;
#define erp(u) \
    for (int it = G.head[u], v = G.a[it].to, w = G.a[it].w; ~it; it = G.a[it].nx, v = G.a[it].to, w = G.a[it].w)

int root, sum, f[N], sze[N];
void getroot(int u, int fa) {
    sze[u] = 1;
    f[u] = 0;
    erp(u) if (v != fa && !vis[v]) {
        getroot(v, u);
        sze[u] += sze[v];
        f[u] = max(f[u], sze[v]);
    }
    f[u] = max(f[u], sum - sze[u]);
    if (f[u] < f[root]) {
        root = u;
    }
}

// 0代表全0 1代表全1 2代表上0下1 3代表上1下0 4代表根节点 5代表混合
int deep[N], cnt[10];
void getdeep(int u, int fa) {
    switch (deep[u]) {
        case 0:
            res += 1 + cnt[0];
            res += 1 + cnt[0] + cnt[1] + cnt[2];
            break;
        case 1:
            res += 1 + cnt[0] + cnt[1] + cnt[3];
            res += 1 + cnt[1];
            break;
        case 2:
            res += 1 + cnt[0];
            break;
        case 3:
            res += 1 + cnt[1];
            break;
        case 4:
        case 5:
            break;
    }
    erp(u) if (v != fa && !vis[v]) {
        switch (w) {
            case 0:
                switch (deep[u]) {
                    case 0:
                        deep[v] = 0;
                        break;
                    case 1:
                        deep[v] = 3;
                        break;
                    case 2:
                        deep[v] = 5;
                        break;
                    case 3:
                        deep[v] = 3;
                        break;
                    case 4:
                        deep[v] = 0;
                        break;
                    case 5:
                        deep[v] = 5;
                        break;
                    default:
                        assert(0);
                }
                break;
            case 1:
                switch (deep[u]) {
                    case 0:
                        deep[v] = 2;
                        break;
                    case 1:
                        deep[v] = 1;
                        break;
                    case 2:
                        deep[v] = 2;
                        break;
                    case 3:
                        deep[v] = 5;
                        break;
                    case 4:
                        deep[v] = 1;
                        break;
                    case 5:
                        deep[v] = 5;
                        break;
                    default:
                        assert(0);
                }
                break;
            default:
                assert(0);
        }
        getdeep(v, u);
    }
}

void add(int u, int fa) {
    ++cnt[deep[u]];
    erp(u) if (v != fa && !vis[v]) {
        add(v, u);
    }
}

void solve(int u) {
    vis[u] = 1;
    memset(cnt, 0, sizeof cnt);
    deep[u] = 4;
    ++cnt[4];
    erp(u) if (!vis[v]) {
        deep[v] = w;
        getdeep(v, u);
        add(v, u);
    }
    erp(u) if (!vis[v]) {
        sum = f[0] = sze[v];
        root = 0;
        getroot(v, 0);
        solve(root);
    }
}

void init() {
    G.init(n);
    res = 0;
    memset(vis, 0, sizeof vis);
}
int main() {
    while (scanf("%d", &n) != EOF) {
        init();
        for (int i = 1, u, v, w; i < n; ++i) {
            scanf("%d%d%d", &u, &v, &w);
            G.add(u, v, w);
        }
        sum = f[0] = n;
        root = 0;
        getroot(1, 0);
        solve(root);
        printf("%lld\n", res);
    }
    return 0;
}
