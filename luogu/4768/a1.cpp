#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define dbg(x...)                             \
    do {                                      \
        cout << "\033[32;1m" << #x << " -> "; \
        err(x);                               \
    } while (0)
void err() {
    cout << "\033[39;0m" << endl;
}
template <class T, class... Ts>
void err(const T &arg, const Ts &...args) {
    cout << arg << ' ';
    err(args...);
}
const int N = 6e5 + 10, M = 20, INF = 0x3f3f3f3f;
int n, m, Q, K, S;

struct Edge {
    int u, v, w, s;
    bool operator<(const Edge &other) const {
        return s > other.s;
    }
} e[N];

struct Graph {
    struct E {
        int to, nx, w, s;
    } e[N << 1];
    int h[N], cnt;
    void init(int n) {
        for (int i = 1; i <= n; ++i) h[i] = -1;
        cnt = -1;
    }
    void addedge(int u, int v, int w, int s) {
        e[++cnt] = {v, h[u], w, s};
        h[u] = cnt;
    }
} G;

int dis[N];
struct Dijkstra {
    struct node {
        int u, w;
        node(int u = 0, int w = 0) : u(u), w(w) {}
        bool operator<(const node &other) const {
            return w > other.w;
        }
    };
    bool used[N];
    void gao(int rt) {
        for (int i = 1; i <= n; ++i) {
            dis[i] = INF;
            used[i] = 0;
        }
        dis[rt] = 0;
        priority_queue<node> pq;
        pq.push(node(rt, 0));
        while (!pq.empty()) {
            int u = pq.top().u;
            pq.pop();
            if (used[u])
                continue;
            used[u] = 1;
            for (int i = G.h[u]; ~i; i = G.e[i].nx) {
                int v = G.e[i].to, w = G.e[i].w;
                if (dis[v] > dis[u] + w) {
                    dis[v] = dis[u] + w;
                    pq.push(node(v, dis[v]));
                }
            }
        }
    }
} dij;

int val[N];
struct MST {
    int fa[N], id;
    int find(int x) {
        return fa[x] == 0 ? x : fa[x] = find(fa[x]);
    }
    void init(int n) {
        for (int i = 1; i <= n * 2; ++i) fa[i] = 0;
        id = n;
    }
    void build(int n, int m) {
        G.init(n + m);
        init(n);
        sort(e + 1, e + 1 + m);
        for (int i = 1; i <= m; ++i) {
            int u = find(e[i].u), v = find(e[i].v), w = e[i].w, s = e[i].s;
            if (u == v)
                continue;
            ++id;
            val[id] = s;
            G.addedge(id, u, w, s);
            G.addedge(id, v, w, s);
            fa[u] = fa[v] = id;
        }
    }
} mst;

struct LCA {
    int fa[N][M];
    int in[N], fin[N], out[N];
    void dfs(int u) {
        if (u <= n) {
            in[u] = ++*in;
            fin[*in] = u;
            val[u] = INF;
        } else {
            in[u] = INF;
        }
        for (int i = 1; i < M; ++i) {
            fa[u][i] = fa[fa[u][i - 1]][i - 1];
        }
        for (int i = G.h[u]; ~i; i = G.e[i].nx) {
            int v = G.e[i].to;
            if (v == fa[u][0])
                continue;
            fa[v][0] = u;
            dfs(v);
            val[u] = min(val[u], val[v]);
            in[u] = min(in[u], in[v]);
        }
        out[u] = *in;
    }
    void init(int rt) {
        *in = 0;
        fa[rt][0] = 0;
        dfs(rt);
    }
    int Jump(int u, int limit) {
        for (int i = M - 1; i >= 0; --i) {
            if (val[fa[u][i]] > limit) {
                u = fa[u][i];
            }
        }
        return u;
    }
} lca;

struct SEG {
    int Min[N << 2];
    void build(int id, int l, int r) {
        Min[id] = INF;
        if (l == r) {
            Min[id] = dis[lca.fin[l]];
            return;
        }
        int mid = (l + r) >> 1;
        build(id << 1, l, mid);
        build(id << 1 | 1, mid + 1, r);
        Min[id] = min(Min[id << 1], Min[id << 1 | 1]);
    }
    int query(int id, int l, int r, int ql, int qr) {
        if (l >= ql && r <= qr)
            return Min[id];
        int mid = (l + r) >> 1;
        int Min = INF;
        if (ql <= mid)
            Min = min(Min, query(id << 1, l, mid, ql, qr));
        if (qr > mid)
            Min = min(Min, query(id << 1 | 1, mid + 1, r, ql, qr));
        return Min;
    }
} seg;

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &m);
        G.init(n);
        for (int i = 1, u, v, w, s; i <= m; ++i) {
            scanf("%d%d%d%d", &u, &v, &w, &s);
            e[i] = {u, v, w, s};
            G.addedge(u, v, w, s);
            G.addedge(v, u, w, s);
        }
        dij.gao(1);
        mst.build(n, m);
        lca.init(mst.id);
        seg.build(1, 1, n);
        scanf("%d%d%d", &Q, &K, &S);
        ll lastans = 0, v, p;
        while (Q--) {
            scanf("%lld%lld", &v, &p);
            v = (v + K * lastans - 1) % n + 1;
            p = (p + K * lastans) % (S + 1);
            int pos = lca.Jump(v, p);
            lastans = seg.query(1, 1, n, lca.in[pos], lca.out[pos]);
            printf("%lld\n", lastans);
        }
    }
    return 0;
}
