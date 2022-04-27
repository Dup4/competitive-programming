#include <bits/stdc++.h>
using namespace std;
int n, m, s, t;
namespace HLPP {
static const int N = 2e4 + 10;
static const int M = 2e5 + 10;
static const int INF = 0x3f3f3f3f;
int s, t, n;
struct E {
    int to, nx, w;
} edge[M << 1];
int head[N], tot;
int h[N], e[N], gap[N << 1], inq[N];
void init(int _s, int _t, int _n) {
    s = _s;
    t = _t;
    n = _n;
    tot = 0;
}
struct cmp {
    bool operator()(int a, int b) const {
        return h[a] < h[b];
    }
};
queue<int> q;
priority_queue<int, vector<int>, cmp> pq;
void addedge(int u, int v, int w, int rw = 0) {
    tot += 2;
    edge[tot] = {v, head[u], w};
    head[u] = tot;
    edge[tot + 1] = {u, head[v], rw};
    head[v] = tot + 1;
}
bool bfs() {
    memset(h + 1, 0x3f, sizeof(int) * n);
    h[t] = 0;
    q.push(t);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int i = head[u]; i; i = edge[i].nx) {
            int v = edge[i].to;
            if (edge[i ^ 1].w && h[v] > h[u] + 1) {
                h[v] = h[u] + 1, q.push(v);
            }
        }
    }
    return h[s] != INF;
}
void push(int u) {  //推送
    int d;
    for (int i = head[u]; i; i = edge[i].nx) {
        int v = edge[i].to;
        if (edge[i].w && h[v] + 1 == h[u]) {
            d = min(e[u], edge[i].w);
            edge[i].w -= d;
            edge[i ^ 1].w += d;
            e[u] -= d;
            e[v] += d;
            if (v != s && v != t && !inq[v]) {
                pq.push(v);
                inq[v] = 1;
            }
            if (!e[u])
                break;
        }
    }
}
void relabel(int u) {  //重贴标签
    h[u] = INF;
    for (int i = head[u]; i; i = edge[i].nx) {
        int v = edge[i].to;
        if (edge[i].w && h[v] + 1 < h[u]) {
            h[u] = h[v] + 1;
        }
    }
    return;
}
int gao() {
    if (!bfs())
        return 0;
    h[s] = n;
    memset(gap, 0, sizeof(gap[0]) * (n << 1));
    for (int i = 1; i <= n; ++i) {
        if (h[i] < INF) {
            ++gap[h[i]];
        }
    }
    for (int i = head[s]; i; i = edge[i].nx) {
        int v = edge[i].to, d = edge[i].w;
        if (d) {
            edge[i].w -= d;
            edge[i ^ 1].w += d;
            e[s] -= d;
            e[v] += d;
            if (v != s && v != t && !inq[v]) {
                pq.push(v);
                inq[v] = 1;
            }
        }
    }
    while (!pq.empty()) {
        int u = pq.top();
        pq.pop();
        inq[u] = 0;
        push(u);
        if (e[u]) {
            if (!--gap[h[u]]) {
                for (int i = 1; i <= n; ++i) {
                    if (i != s && i != t && h[i] > h[u] && h[i] < n + 1) {
                        h[i] = n + 1;
                    }
                }
            }
            relabel(u);
            ++gap[h[u]];
            pq.push(u);
            inq[u] = 1;
        }
    }
    return e[t];
}
};  // namespace HLPP

int main() {
    int n, m, s, t;
    while (scanf("%d%d%d%d", &n, &m, &s, &t) != EOF) {
        HLPP::init(s, t, n);
        for (int i = 1, u, v, w; i <= m; ++i) {
            scanf("%d%d%d", &u, &v, &w);
            HLPP::addedge(u, v, w);
        }
        printf("%d\n", HLPP::gao());
    }
    return 0;
}
