#include <bits/stdc++.h>
using namespace std;
#define ll long long
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
struct Dinic {
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
} dinic;
const int N = 3e3 + 10;
int n, a[N];
int gcd(int a, int b) {
    return b ? gcd(b, a % b) : a;
}
inline bool issqr(ll x) {
    ll mid = sqrt(x);
    return mid * mid == x;
}

int main() {
    while (scanf("%d", &n) != EOF) {
        dinic.init();
        ll tot = 0;
        int S = n + 1, T = S + 1;
        dinic.set(S, T);
        for (int i = 1; i <= n; ++i) {
            scanf("%d", a + i);
            tot += a[i];
            if (a[i] & 1) {
                dinic.addedge(S, i, a[i]);
            } else {
                dinic.addedge(i, T, a[i]);
            }
        }
        for (int i = 1; i <= n; ++i) {
            for (int j = i + 1; j <= n; ++j) {
                int u = i, v = j;
                if (issqr(1ll * a[u] * a[u] + 1ll * a[v] * a[v]) && gcd(a[u], a[v]) == 1) {
                    if (a[v] & 1)
                        swap(u, v);
                    dinic.addedge(u, v, 0x3f3f3f3f);
                }
            }
        }
        printf("%lld\n", tot - dinic.solve());
    }
    return 0;
}
