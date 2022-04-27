#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 1e6 + 10;
int n, w[N], vis[N], x, y, eid;
ll f[N][2], ans;
struct E {
    int v, nx;
} e[N << 1];
int h[N], tot;
void add(int u, int v) {
    e[tot] = {v, h[u]};
    h[u] = tot++;
}

void find_circle(int u, int pre) {
    vis[u] = 1;
    for (int i = h[u]; ~i; i = e[i].nx) {
        if ((i ^ 1) == pre)
            continue;
        int v = e[i].v;
        if (vis[v]) {
            x = u, y = v;
            eid = i;
            continue;
        }
        find_circle(v, i);
    }
}

void dp(int u, int pre) {
    f[u][0] = 0, f[u][1] = w[u];
    for (int i = h[u]; ~i; i = e[i].nx) {
        int v = e[i].v;
        if ((i ^ 1) == pre || i == eid || (i ^ 1) == eid)
            continue;
        dp(v, i);
        f[u][0] += max(f[v][0], f[v][1]);
        f[u][1] += f[v][0];
    }
}

int main() {
    while (scanf("%d", &n) != EOF) {
        tot = 0;
        memset(h, -1, sizeof h);
        for (int i = 1, x; i <= n; ++i) {
            scanf("%d%d", w + i, &x);
            add(x, i);
            add(i, x);
            vis[i] = 0;
        }
        ans = 0;
        for (int i = 1; i <= n; ++i) {
            if (!vis[i]) {
                find_circle(i, -1);
                ll t;
                dp(x, -1);
                t = f[x][0];
                dp(y, -1);
                t = max(t, f[y][0]);
                ans += t;
            }
        }
        printf("%lld\n", ans);
    }
    return 0;
}
