#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define INFLL 0x3f3f3f3f3f3f3f3f
#define N 1000010
int n, m, s, t;
struct Graph {
    struct node {
        int to, nx, w;
        node() {}
        node(int to, int nx, int w) : to(to), nx(nx), w(w) {}
    } a[N << 1];
    int head[N], pos;
    void init() {
        memset(head, -1, sizeof head);
        pos = 0;
    }
    void add(int u, int v, int w) {
        a[pos] = node(v, head[u], w);
        head[u] = pos++;
    }
} G;
#define erp(u) \
    for (int it = G.head[u], v = G.a[it].to, w = G.a[it].w; ~it; it = G.a[it].nx, v = G.a[it].to, w = G.a[it].w)

struct node {
    int u;
    ll w;
    node() {}
    node(int u, ll w) : u(u), w(w) {}
    bool operator<(const node &other) const {
        return w > other.w;
    }
};

ll dist[N];
bool used[N];
void Dijkstra(int s) {
    memset(dist, 0x3f, sizeof dist);
    memset(used, 0, sizeof used);
    priority_queue<node> pq;
    dist[s] = 0;
    pq.push(node(s, 0));
    while (!pq.empty()) {
        int u = pq.top().u;
        pq.pop();
        if (used[u])
            continue;
        used[u] = 1;
        erp(u) if (dist[v] > dist[u] + w) {
            dist[v] = dist[u] + w;
            pq.push(node(v, dist[v]));
        }
    }
}

int main() {
    while (scanf("%d%d%d%d", &n, &m, &s, &t) != EOF) {
        G.init();
        for (int i = 1, a, b, c, u, v; i <= m; ++i) {
            scanf("%d%d%d", &a, &b, &c);
            for (int j = 1; j <= c; ++j) {
                scanf("%d", &v);
                if (j > 1) {
                    G.add((i - 1) * n + u, (i - 1) * n + v, b);
                    G.add((i - 1) * n + v, (i - 1) * n + u, b);
                }
                G.add((i - 1) * n + v, m * n + v, 0);
                G.add(m * n + v, (i - 1) * n + v, a);
                u = v;
            }
        }
        Dijkstra(m * n + s);
        ll res = dist[m * n + t];
        if (res == INFLL)
            res = -1;
        printf("%lld\n", res);
    }
    return 0;
}
