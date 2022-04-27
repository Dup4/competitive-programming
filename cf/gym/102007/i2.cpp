#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int N = 1e5 + 10;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;

struct Dicnic {
    static const int M = 2e6 + 10;
    static const int N = 1e4 + 10;

    struct Edge {
        int to, nxt;
        ll flow;

        Edge() {}

        Edge(int to, int nxt, ll flow) : to(to), nxt(nxt), flow(flow) {}
    } edge[M];

    int S, T;
    int head[N], tot;
    int dep[N];

    void Init() {
        memset(head, -1, sizeof head);
        tot = 0;
    }

    void set(int _S, int _T) {
        S = _S;
        T = _T;
    }

    void addedge(int u, int v, int w, int rw = 0) {
        cout << u << " " << v << " " << w << endl;
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
        if (u == T || f == 0) {
            return f;
        }
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
        ll res = 0;
        while (BFS()) {
            res += DFS(S, INFLL);
        }
        return res;
    }
} dicnic;

struct Edge {
    int to, nxt;
    ll w;

    Edge() {}

    Edge(int to, int nxt, ll w) : to(to), nxt(nxt), w(w) {}
} edge[N << 1];

int n, m, s;
int a[N], c[N], p[N];
int head[N], used[N], tot;
ll dis[11][N];

void Init() {
    memset(head, -1, sizeof head);
    tot = 0;
}

void addedge(int u, int v, int w) {
    edge[tot] = Edge(v, head[u], w);
    head[u] = tot++;
    edge[tot] = Edge(u, head[v], w);
    head[v] = tot++;
}

struct qnode {
    int u;
    ll w;

    qnode() {}

    qnode(int u, ll w) : u(u), w(w) {}

    bool operator<(const qnode &other) const {
        return w > other.w;
    }
};

void Dij(int id, int S) {
    for (int i = 1; i <= n; ++i) {
        dis[id][i] = INFLL;
        used[i] = false;
    }
    dis[id][S] = 0;
    priority_queue<qnode> pq;
    pq.push(qnode(S, 0));
    while (!pq.empty()) {
        int u = pq.top().u;
        pq.pop();
        if (used[u])
            continue;
        used[u] = true;
        for (int i = head[u]; ~i; i = edge[i].nxt) {
            int v = edge[i].to, w = edge[i].w;
            if (!used[v] && dis[id][v] > dis[id][u] + w) {
                dis[id][v] = dis[id][u] + w;
                pq.push(qnode(v, dis[id][v]));
            }
        }
    }
}

ll sum;
ll mark[1 << 11];

bool check(ll x) {
    memset(mark, 0, sizeof mark);
    for (int i = 1; i <= n; ++i) {
        int S = 0;
        for (int j = 1; j <= s; ++j) {
            if (dis[j][i] <= x) {
                S |= 1 << (j - 1);
            }
        }
        mark[S] += p[i];
    }
    dicnic.Init();
    int S = (1 << s) + s, T = S + 1, tmp = 1 << s;
    cout << "#S " << S << endl;
    cout << "#T " << T << endl;
    dicnic.set(S, T);
    for (int i = 0; i < tmp; ++i) {
        dicnic.addedge(S, i, mark[i]);
        for (int j = 0; j < s; ++j) {
            if (i & (1 << j)) {
                dicnic.addedge(i, j + tmp, mark[i]);
            }
        }
    }
    for (int i = (1 << s), j = 1; j <= s; ++j, ++i) {
        dicnic.addedge(i, T, c[j]);
    }
    ll res = dicnic.solve();
    cout << res << endl;
    return res == sum;
}

int main() {
    while (scanf("%d %d %d", &n, &m, &s) != EOF) {
        Init();
        sum = 0;
        for (int i = 1; i <= n; ++i) {
            scanf("%d", p + i);
            sum += p[i];
        }
        for (int i = 1, u, v, w; i <= m; ++i) {
            scanf("%d %d %d", &u, &v, &w);
            addedge(u, v, w);
        }
        for (int i = 1; i <= s; ++i) {
            scanf("%d %d", a + i, c + i);
        }
        for (int i = 1; i <= s; ++i) {
            Dij(i, a[i]);
        }
        cout << check(5) << endl;
    }
    return 0;
}
