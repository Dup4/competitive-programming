#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 1e6 + 10;
int n, w[N], fa[N], deep[N], vis[N];
ll f[N][2], ans;
struct E {
    int u, v, nx, cut;
} e[N << 1];
int h[N], tot;
void add(int u, int v) {
    e[tot] = {u, v, h[u], 0};
    h[u] = tot++;
}

void dfs(int u) {
    for (int i = h[u]; ~i; i = e[i].nx) {
        int v = e[i].v;
        if (deep[v])
            continue;
        fa[v] = u;
        deep[v] = deep[u] + 1;
        dfs(v);
    }
}

void dp(int u, int fa) {
    vis[u] = 1;
    f[u][0] = 0, f[u][1] = w[u];
    for (int i = h[u]; ~i; i = e[i].nx) {
        int v = e[i].v;
        if (v == fa || e[i].cut)
            continue;
        dp(v, u);
        f[u][0] += max(f[v][0], f[v][1]);
        f[u][1] += f[v][0];
    }
}

int main() {
    while (scanf("%d", &n) != EOF) {
        tot = 0;
        memset(h, -1, sizeof h);
        memset(fa, 0, sizeof fa);
        for (int i = 1, x; i <= n; ++i) {
            scanf("%d%d", w + i, &x);
            fa[i] = x;
            //避免加入重边
            if (fa[x] != i) {
                add(x, i);
                add(i, x);
            }
            deep[i] = 0;
            vis[i] = 0;
        }
        for (int i = 1; i <= n; ++i) {
            if (!deep[i]) {
                deep[i] = 1;
                fa[i] = 0;
                dfs(i);
            }
        }
        ans = 0;
        for (int i = 0; i < tot; ++i) {
            int u = e[i].u, v = e[i].v;
            //找环
            if (!vis[u] && !vis[v] && deep[u] < deep[v] && fa[v] != u) {
                //切掉当前边，分别以两个点为根进行dp
                e[i].cut = e[i ^ 1].cut = 1;
                ll t;
                dp(u, u);
                t = f[u][0];
                dp(v, v);
                t = max(t, f[v][0]);
                ans += t;
                e[i].cut = e[i ^ 1].cut = 0;
            }
        }
        //处理原图是树的情况
        for (int i = 1; i <= n; ++i) {
            if (!vis[i]) {
                dp(i, i);
                ans += max(f[i][0], f[i][1]);
            }
        }
        printf("%lld\n", ans);
    }
    return 0;
}
