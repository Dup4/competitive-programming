#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 300010
#define INFLL 0x3f3f3f3f
#define pii pair<int, int>
#define fi first
#define se second
int n, m, k, s, t;
int e[N][3];
int bit[50];
vector<pii> res;
struct Graph {
    struct node {
        int to, nx, w;
        node() {}
        node(int to, int nx, int w) : to(to), nx(nx), w(w) {}
    } a[N << 1];
    int head[N], pos;
    void init() {
        memset(head, 0, sizeof head);
        pos = 0;
    }
    void add(int u, int v, int w) {
        a[++pos] = node(v, head[u], w);
        head[u] = pos;
        a[++pos] = node(u, head[v], w);
        head[v] = pos;
    }
} G;
#define erp(u) \
    for (int it = G.head[u], v = G.a[it].to, w = G.a[it].w; it; it = G.a[it].nx, v = G.a[it].to, w = G.a[it].w)

struct node {
    int to;
    ll w;
    node() {}
    node(int to, ll w) : to(to), w(w) {}
    bool operator<(const node &other) const {
        return w > other.w;
    }
};
ll dist[N];
int used[N];
void Dijkstra() {
    priority_queue<node> pq;
    pq.push(node(s, 0));
    dist[s] = 0;
    while (!pq.empty()) {
        int u = pq.top().to;
        pq.pop();
        if (used[u] || u == t) {
            continue;
        }
        used[u] = 1;
        erp(u) if (dist[v] > dist[u] + w) {
            dist[v] = dist[u] + w;
            pq.push(node(v, dist[v]));
        }
    }
}

bool ok(int l, int r) {
    G.pos = 0;
    G.head[s] = 0;
    G.head[t] = 0;
    for (int i = l; i <= r; ++i) {
        int u = e[i][0], v = e[i][1], w = e[i][2];
        dist[u] = INFLL;
        dist[v] = INFLL;
        used[u] = 0;
        used[v] = 0;
        G.head[u] = 0;
        G.head[v] = 0;
    }
    for (int i = l; i <= r; ++i) {
        int u = e[i][0], v = e[i][1], w = e[i][2];
        G.add(u, v, w);
    }
    dist[s] = INFLL;
    dist[t] = INFLL;
    used[s] = 0;
    used[t] = 0;
    Dijkstra();
    return dist[t] <= k;
}

int main() {
    bit[1] = 1;
    for (int i = 2; i <= 25; ++i) {
        bit[i] = bit[i - 1] << 1;
    }
    while (scanf("%d%d%d", &n, &m, &k) != EOF) {
        scanf("%d%d", &s, &t);
        for (int i = 1; i <= m; ++i) {
            scanf("%d%d%d", &e[i][0], &e[i][1], &e[i][2]);
        }
        res.clear();
        for (int i = 1; i <= m;) {
            int now = i;
            for (int j = 1; j <= 25; ++j) {
                now += bit[j];
                now = min(m, now);
                if (now == m || ok(i, now)) {
                    break;
                }
            }
            int l = i, r = now, fin = -1;
            while (r - l >= 0) {
                int mid = (l + r) >> 1;
                if (ok(i, mid)) {
                    r = mid - 1;
                    fin = mid;
                } else {
                    l = mid + 1;
                }
            }
            if (fin == -1) {
                break;
            }
            res.push_back(pii(i, fin));
            i = fin + 1;
        }
        int k = (int)res.size();
        printf("%d\n", k);
        for (auto it : res) {
            printf("%d %d\n", it.fi, it.se);
        }
    }
    return 0;
}
