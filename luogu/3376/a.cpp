#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f3f3f3f3f;
template <class Type>
struct Dinic {
    static const int M = 2e6 + 10;
    static const int N = 1e5 + 10;
    struct Edge {
        int to, nxt;
        Type flow;
        Edge() {}
        Edge(int to, int nxt, Type flow) : to(to), nxt(nxt), flow(flow) {}
    } edge[M];
    int S, T;
    int head[N], tot;
    int dep[N];
    void init() {
        memset(head, -1, sizeof head);
        tot = 0;
    }
    void set(int S, int T) {
        this->S = S;
        this->T = T;
    }
    void addedge(int u, int v, int w, int rw = 0) {
        edge[tot] = Edge(v, head[u], w);
        head[u] = tot++;
        edge[tot] = Edge(u, head[v], rw);
        head[v] = tot++;
    }
    bool BFS() {
        memset(dep, -1, sizeof dep);
        queue<int> q;
        q.push(S);
        dep[S] = 1;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int i = head[u]; ~i; i = edge[i].nxt) {
                if (edge[i].flow && dep[edge[i].to] == -1) {
                    dep[edge[i].to] = dep[u] + 1;
                    q.push(edge[i].to);
                }
            }
        }
        return dep[T] >= 0;
    }
    Type DFS(int u, Type f) {
        if (u == T || f == 0)
            return f;
        Type w, used = 0;
        for (int i = head[u]; ~i; i = edge[i].nxt) {
            if (edge[i].flow && dep[edge[i].to] == dep[u] + 1) {
                w = DFS(edge[i].to, min(f - used, edge[i].flow));
                edge[i].flow -= w;
                edge[i ^ 1].flow += w;
                used += w;
                if (used == f)
                    return f;
            }
        }
        if (!used)
            dep[u] = -1;
        return used;
    }
    Type solve() {
        Type ans = 0;
        while (BFS()) {
            ans += DFS(S, INF);
        }
        return ans;
    }
};
Dinic<ll> dinic;

int main() {
    int n, m, s, t;
    while (scanf("%d%d%d%d", &n, &m, &s, &t) != EOF) {
        dinic.init();
        for (int i = 1, u, v, w; i <= m; ++i) {
            scanf("%d%d%d", &u, &v, &w);
            dinic.addedge(u, v, w);
        }
        dinic.set(s, t);
        printf("%lld\n", dinic.solve());
    }
    return 0;
}
