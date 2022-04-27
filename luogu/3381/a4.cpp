#include <bits/stdc++.h>
using namespace std;

struct ZKW_MinCostMaxFlow {
    static const int N = 5e3 + 10;
    static const int M = 5e4 + 10;
    static const int INF = 0x3f3f3f3f;
    struct E {
        int to, nx, cap, flow, cost;
    } edge[M << 1];
    int head[N], tot;
    int cur[N], dis[N];
    bool vis[N];
    int s, t, n;
    void init(int _s, int _t, int _n) {
        s = _s;
        t = _t;
        n = _n;
        tot = 0;
        memset(head, -1, sizeof head);
    }
    void addedge(int u, int v, int cap, int cost) {
        edge[tot] = {v, head[u], cap, 0, cost};
        head[u] = tot++;
        edge[tot] = {u, head[v], 0, 0, -cost};
        head[v] = tot++;
    }
    int aug(int u, int flow) {
        if (u == t)
            return flow;
        vis[u] = true;
        for (int i = cur[u]; i != -1; i = edge[i].nx) {
            int v = edge[i].to;
            if (edge[i].cap > edge[i].flow && !vis[v] && dis[u] == dis[v] + edge[i].cost) {
                int tmp = aug(v, min(flow, edge[i].cap - edge[i].flow));
                edge[i].flow += tmp;
                edge[i ^ 1].flow -= tmp;
                cur[u] = i;
                if (tmp)
                    return tmp;
            }
        }
        return 0;
    }
    bool modify_label() {
        int d = INF;
        for (int u = 1; u <= n; ++u) {
            if (vis[u]) {
                for (int i = head[u]; i != -1; i = edge[i].nx) {
                    int v = edge[i].to;
                    if (edge[i].cap > edge[i].flow && !vis[v]) {
                        d = min(d, dis[v] + edge[i].cost - dis[u]);
                    }
                }
            }
        }
        if (d == INF)
            return false;
        for (int i = 1; i <= n; ++i) {
            if (vis[i]) {
                vis[i] = false;
                dis[i] += d;
            }
        }
        return true;
    }
    //返回flow cost引用传递
    //点的编号从1开始
    int gao(int &cost) {
        cost = 0;
        int flow = 0;
        for (int i = 1; i <= n; ++i) dis[i] = 0;
        while (true) {
            for (int i = 1; i <= n; ++i) cur[i] = head[i];
            while (true) {
                for (int i = 1; i <= n; ++i) vis[i] = false;
                int tmp = aug(s, INF);
                if (tmp == 0)
                    break;
                flow += tmp;
                cost += tmp * dis[s];
            }
            if (!modify_label())
                break;
        }
        return flow;
    }
} MCMF;

int n, m, s, t;
int flow, cost;

int main() {
    while (scanf("%d%d%d%d", &n, &m, &s, &t) != EOF) {
        MCMF.init(s, t, n);
        for (int i = 1, u, v, w, f; i <= m; ++i) {
            scanf("%d%d%d%d", &u, &v, &w, &f);
            MCMF.addedge(u, v, w, f);
        }
        flow = MCMF.gao(cost);
        printf("%d %d\n", flow, cost);
    }
    return 0;
}
