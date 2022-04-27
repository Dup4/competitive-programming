#include <bits/stdc++.h>
using namespace std;
const int INF = 0x3f3f3f3f;
int n, m, q;
struct Dinic {
    static const int M = 2e5 + 10;
    static const int N = 1e3 + 10;
    struct Edge {
        int to, nxt;
        int flow;
        Edge() {}
        Edge(int to, int nxt, int flow) : to(to), nxt(nxt), flow(flow) {}
    } edge[M];
    int S, T;
    int head[N], tot;
    int dep[N];
    queue<int> q;
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
        while (!q.empty()) q.pop();
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
    int DFS(int u, int f) {
        if (u == T || f == 0)
            return f;
        int w, used = 0;
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
    //恢复流量
    void recover() {
        for (int i = 0; i <= tot; i += 2) {
            edge[i].flow = edge[i].flow + edge[i ^ 1].flow;
            edge[i ^ 1].flow = 0;
        }
    }
    int solve() {
        recover();
        int ans = 0;
        while (BFS()) {
            ans += DFS(S, INF);
        }
        return ans;
    }
} dinic;

// MinCutTree
struct MCT {
    static const int N = 1e3 + 10;
    static const int M = 12;
    struct E {
        int to, nx, w;
    } e[N * 2];
    int h[N];
    void init() {
        memset(h, 0, sizeof h);
    }
    void addedge(int u, int v, int w) {
        e[++*h] = E{v, h[u], w};
        h[u] = *h;
    }
    int node[N], tmpS[N], tmpT[N];
    void build(int l, int r) {
        if (l == r)
            return;
        int s = node[l], t = node[l + 1];
        dinic.set(s, t);
        int cut = dinic.solve();
        //树上s-t的边为cut
        addedge(s, t, cut);
        addedge(t, s, cut);
        int cs = 0, ct = 0;
        //根据点所属割集的不同分成两部分
        for (int i = l; i <= r; ++i) {
            //考虑dinic算法中的最后一次bfs,因为现在残量网络上s到达不了t,所以bfs访问到的点就是s所在的点集，它们的dep不-1
            if (dinic.dep[node[i]] != -1)
                tmpS[++cs] = node[i];
            else
                tmpT[++ct] = node[i];
        }
        for (int i = l; i <= l + cs - 1; ++i) node[i] = tmpS[i - l + 1];
        for (int i = l + cs; i <= r; ++i) node[i] = tmpT[i - cs - l + 1];
        //递归处理两个割集
        build(l, l + cs - 1);
        build(l + cs, r);
    }
    int dep[N], fa[N][M], min_dis[N][M];
    void bfs(int s) {
        queue<int> q;
        dep[s] = 0;
        fa[s][0] = 1;
        min_dis[s][0] = 0;
        q.push(s);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int i = 1; i < M; ++i) {
                fa[u][i] = fa[fa[u][i - 1]][i - 1];
                min_dis[u][i] = min(min_dis[u][i - 1], min_dis[fa[u][i - 1]][i - 1]);
            }
            for (int i = h[u]; i; i = e[i].nx) {
                int v = e[i].to, w = e[i].w;
                if (v == fa[u][0])
                    continue;
                dep[v] = dep[u] + 1;
                fa[v][0] = u;
                min_dis[v][0] = w;
                q.push(v);
            }
        }
    }
    int query(int u, int v) {
        if (u == v)
            return INF;
        if (dep[u] > dep[v])
            swap(u, v);
        int res = INF, hu = dep[u], hv = dep[v], tu = u, tv = v;
        for (int det = hv - hu, i = 0; det; det >>= 1, ++i) {
            if (det & 1) {
                res = min(res, min_dis[tv][i]);
                tv = fa[tv][i];
            }
        }
        if (tu == tv)
            return res;
        for (int i = M - 1; i >= 0; --i) {
            if (fa[tu][i] == fa[tv][i])
                continue;
            res = min(res, min(min_dis[tu][i], min_dis[tv][i]));
            tu = fa[tu][i];
            tv = fa[tv][i];
        }
        res = min(res, min(min_dis[tu][0], min_dis[tv][0]));
        return res;
    }
    void gao() {
        init();
        for (int i = 1; i <= n; ++i) node[i] = i;
        build(1, n);
        memset(dep, -1, sizeof dep);
        for (int i = 1; i <= n; ++i) {
            if (dep[i] == -1) {
                bfs(i);
            }
        }
    }
} mct;

int main() {
    while (scanf("%d%d", &n, &m) != EOF) {
        dinic.init();
        for (int i = 1, u, v, w; i <= m; ++i) {
            scanf("%d%d%d", &u, &v, &w);
            dinic.addedge(u, v, w);
            dinic.addedge(v, u, w);
        }
        mct.gao();
        vector<int> vec;
        for (int i = 1; i <= n; ++i) {
            for (int j = i + 1; j <= n; ++j) {
                vec.push_back(mct.query(i, j));
            }
        }
        sort(vec.begin(), vec.end());
        vec.erase(unique(vec.begin(), vec.end()), vec.end());
        cout << vec.size() << endl;
    }
    return 0;
}
