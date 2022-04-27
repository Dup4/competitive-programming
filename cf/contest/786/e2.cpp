#include <bits/stdc++.h>
using namespace std;
const int N = 2e4 + 10, M = 16, INF = 0x3f3f3f3f;
const int MM = 1e5 + 10;
int n, m, S, T, tot;
#define Type int
namespace Dinic {
struct Edge {
    int to, nxt;
    Type flow;
    Edge() {}
    Edge(int to, int nxt, Type flow) : to(to), nxt(nxt), flow(flow) {}
} edge[MM];
int S, T;
int head[N * M], tot;
int dep[N * M];
void init() {
    memset(head, -1, sizeof head);
    tot = 0;
}
void set(int _S, int _T) {
    S = _S;
    T = _T;
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
};  // namespace Dinic

struct Tree {
    int fa[N][M], id[N][M], deep[N];
    struct E {
        int to, nx;
    } e[N << 1];
    int h[N];
    void init() {
        memset(h, 0, sizeof h);
        deep[1] = 0;
    }
    void addedge(int u, int v) {
        e[++*h] = {v, h[u]};
        h[u] = *h;
        e[++*h] = {u, h[v]};
        h[v] = *h;
    }
    void dfs(int u) {
        for (int i = 1; i < M; ++i) {
            fa[u][i] = fa[fa[u][i - 1]][i - 1];
            id[u][i] = ++tot;
            Dinic::addedge(id[u][i], id[u][i - 1], INF);
            Dinic::addedge(id[u][i], id[fa[u][i - 1]][i - 1], INF);
        }
        for (int i = h[u]; i; i = e[i].nx) {
            int v = e[i].to;
            if (v == fa[u][0])
                continue;
            fa[v][0] = u;
            deep[v] = deep[u] + 1;
            id[v][0] = m + (i + 1) / 2;
            Dinic::addedge(id[v][0], T, 1);
            dfs(v);
        }
    }
    int lca(int u, int v) {
        if (deep[u] < deep[v])
            swap(u, v);
        int deg = deep[u] - deep[v];
        for (int i = 0; i < M; ++i) {
            if ((deg >> i) & 1) {
                u = fa[i][i];
            }
        }
        if (u == v)
            return u;
        for (int i = M - 1; i >= 0; --i) {
            if (fa[u][i] != fa[v][i]) {
                u = fa[u][i];
                v = fa[v][i];
            }
        }
        return fa[u][0];
    }
    void tagedge(int f, int x, int y) {
        int deg = deep[x] - deep[y];
        for (int i = M - 1; i >= 0; --i) {
            if ((deg >> i) & 1) {
                Dinic::addedge(f, id[x][i], INF);
                x = fa[x][i];
            }
        }
    }
} tree;

void out(const vector<int> &vec) {
    int sze = vec.size();
    printf("%d", sze);
    for (auto &it : vec) printf(" %d", it);
    puts("");
}

int main() {
    while (scanf("%d%d", &n, &m) != EOF) {
        tree.init();
        Dinic::init();
        S = n + m, T = S + 1, tot = T;
        Dinic::set(S, T);
        for (int i = 1; i <= m; ++i) {
            Dinic::addedge(S, i, 1);
        }
        for (int i = 1, u, v; i < n; ++i) {
            scanf("%d%d", &u, &v);
            tree.addedge(u, v);
        }
        tree.dfs(1);
        for (int i = 1, u, v; i <= m; ++i) {
            scanf("%d%d", &u, &v);
            int lca = tree.lca(u, v);
            tree.tagedge(i, u, lca);
            tree.tagedge(i, v, lca);
        }
        int res = Dinic::solve();
        vector<int> A, B;
        for (int i = 1; i <= m; ++i) {
            if (Dinic::dep[i] == -1) {
                A.push_back(i);
            }
        }
        for (int i = m + 1; i <= n + m - 1; ++i) {
            if (Dinic::dep[i] != -1) {
                B.push_back(i - m);
            }
        }
        printf("%d\n", res);
        out(A);
        out(B);
    }
    return 0;
}
