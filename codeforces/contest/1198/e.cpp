#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f
const int N = 1e5 + 10;
struct Dicnic {
    static const int M = 2e6 + 10;
    static const int N = 1e5 + 10;
    struct Edge {
        int to, nxt;
        ll flow;
        Edge() {}
        Edge(int to, int nxt, ll flow) : to(to), nxt(nxt), flow(flow) {}
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
    ll DFS(int u, ll f) {
        if (u == T || f == 0)
            return f;
        ll w, used = 0;
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
    ll solve() {
        ll ans = 0;
        while (BFS()) {
            ans += DFS(S, INFLL);
        }
        return ans;
    }
} dicnic;

int S, T, n, m;
struct Hash {
    int a[N], cnt;
    void init() {
        cnt = 0;
    }
    void add(int x) {
        a[++cnt] = x;
    }
    void work() {
        sort(a + 1, a + 1 + cnt);
        cnt = unique(a + 1, a + 1 + cnt) - a - 1;
    }
    int get(int x) {
        return lower_bound(a + 1, a + 1 + cnt, x) - a;
    }
} hx, hy;

struct node {
    int x[2], y[2];
    node() {}
    void scan() {
        scanf("%d%d%d%d", x, y, x + 1, y + 1);
        //	--x[0]; --y[0];
        ++x[1];
        ++y[1];
        hx.add(x[0]);
        hx.add(x[1]);
        hy.add(y[0]);
        hy.add(y[1]);
    }
} a[N];

int main() {
    while (scanf("%d%d", &n, &m) != EOF) {
        hx.init();
        hy.init();
        hx.add(1);
        hx.add(n + 1);
        hy.add(1);
        hy.add(n + 1);
        for (int i = 1; i <= m; ++i) a[i].scan();
        hx.work();
        hy.work();
        S = 0;
        T = 1;
        dicnic.init();
        for (int i = 2; i <= hx.cnt; ++i) {
            dicnic.addedge(S, i, hx.a[i] - hx.a[i - 1]);
        }
        for (int i = 2; i <= hy.cnt; ++i) {
            dicnic.addedge(i + hx.cnt, T, hy.a[i] - hy.a[i - 1]);
        }
        for (int i = 2; i <= hx.cnt; ++i) {
            for (int j = 2; j <= hy.cnt; ++j) {
                for (int k = 1; k <= m; ++k) {
                    if (a[k].x[0] <= hx.a[i - 1] && a[k].x[1] >= hx.a[i] && a[k].y[0] <= hy.a[j - 1] &&
                            a[k].y[1] >= hy.a[j]) {
                        dicnic.addedge(i, hx.cnt + j, INF);
                        break;
                    }
                }
            }
        }
        dicnic.set(S, T);
        printf("%lld\n", dicnic.solve());
    }
    return 0;
}
