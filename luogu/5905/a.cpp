#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 6e3 + 10, INF = 1e9;
int n, m;

struct Graph {
    struct E {
        int to, nx;
        ll w;
    } e[N << 1];
    int h[N], cnt;
    void init(int n) {
        for (int i = 0; i <= n; ++i) h[i] = -1;
        cnt = -1;
    }
    void addedge(int u, int v, ll w = 0) {
        e[++cnt] = {v, h[u], w};
        h[u] = cnt;
    }
} G;

struct SPFA {
    ll dis[N];
    int cnt[N];
    bool used[N];
    // true 没有负环
    // false 有负环
    bool gao(int s) {
        for (int i = 0; i <= n; ++i) {
            dis[i] = INF;
            cnt[i] = 0;
            used[i] = 0;
        }
        queue<int> que;
        dis[s] = 0;
        used[s] = 1;
        que.push(s);
        while (!que.empty()) {
            int u = que.front();
            que.pop();
            used[u] = 0;
            for (int i = G.h[u]; ~i; i = G.e[i].nx) {
                int v = G.e[i].to;
                ll w = G.e[i].w;
                if (dis[v] > dis[u] + w) {
                    dis[v] = dis[u] + w;
                    if (!used[v]) {
                        used[v] = 1;
                        que.push(v);
                        ++cnt[v];
                        if (cnt[v] == n)
                            return false;
                    }
                }
            }
        }
        return true;
    }
} spfa;

struct Dijkstra {
    struct node {
        int u;
        ll w;
        node(int u = 0, ll w = 0) : u(u), w(w) {}
        bool operator<(const node &other) const {
            return w > other.w;
        }
    };
    ll dis[N];
    bool used[N];
    void gao(int s) {
        for (int i = 0; i <= n; ++i) {
            dis[i] = INF;
            used[i] = 0;
        }
        priority_queue<node> pq;
        dis[s] = 0;
        pq.push(node(s, dis[s]));
        while (!pq.empty()) {
            int u = pq.top().u;
            pq.pop();
            if (used[u])
                continue;
            used[u] = 1;
            for (int i = G.h[u]; ~i; i = G.e[i].nx) {
                int v = G.e[i].to;
                ll w = G.e[i].w;
                if (!used[v] && dis[v] > dis[u] + w) {
                    dis[v] = dis[u] + w;
                    pq.push(node(v, dis[v]));
                }
            }
        }
    }
} dij;

int main() {
    scanf("%d%d", &n, &m);
    G.init(n);
    for (int i = 1, u, v, w; i <= m; ++i) {
        scanf("%d%d%d", &u, &v, &w);
        G.addedge(u, v, w);
    }
    for (int i = 1; i <= n; ++i) G.addedge(0, i, 0);
    if (!spfa.gao(0)) {
        puts("-1");
        return 0;
    }
    ll *h = spfa.dis;
    for (int u = 1; u <= n; ++u) {
        for (int i = G.h[u]; ~i; i = G.e[i].nx) {
            int v = G.e[i].to;
            G.e[i].w += h[u] - h[v];
        }
    }
    for (int i = 1; i <= n; ++i) {
        dij.gao(i);
        ll *f = dij.dis;
        ll res = 0;
        for (int j = 1; j <= n; ++j) {
            if (f[j] == INF)
                res += 1ll * j * INF;
            else
                res += 1ll * j * (f[j] + h[j] - h[i]);
        }
        printf("%lld\n", res);
    }
    return 0;
}
