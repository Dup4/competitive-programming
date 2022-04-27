#include <bits/stdc++.h>
using namespace std;
const int N = 2e4 + 10;
int n, m;

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

// 0-index
// i 正 i ^ 1 负
struct TWOSAT {
    int sta[N], top;
    bool vis[N];
    bool dfs(int u) {
        if (vis[u ^ 1])
            return false;
        if (vis[u])
            return true;
        vis[u] = true;
        sta[top++] = u;
        for (int i = G.h[u]; ~i; i = G.e[i].nx) {
            if (!dfs(G.e[i].to))
                return false;
        }
        return true;
    }
    bool gao(int n) {
        memset(vis, false, sizeof vis);
        for (int i = 0; i < n; i += 2) {
            if (vis[i] || vis[i ^ 1])
                continue;
            top = 0;
            if (!dfs(i)) {
                while (top) vis[sta[--top]] = false;
                if (!dfs(i ^ 1))
                    return false;
            }
        }
        return true;
    }
} twoSAT;

int main() {
    while (scanf("%d%d", &n, &m) != EOF) {
        G.init(n * 2);
        for (int i = 1, u, v; i <= m; ++i) {
            scanf("%d%d", &u, &v);
            --u, --v;
            G.addedge(u, v ^ 1);
            G.addedge(v, u ^ 1);
        }
        if (twoSAT.gao(n << 1)) {
            for (int i = 0; i < (n << 1); ++i)
                if (twoSAT.vis[i])
                    printf("%d\n", i + 1);
        } else {
            puts("NIE");
        }
    }
    return 0;
}
