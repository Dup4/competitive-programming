#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int maxn = 1e5 + 10;

struct Edge {
    int to, nxt, w;
    Edge() {}
    Edge(int to, int nxt, int w) : to(to), nxt(nxt), w(w) {}
} edge[maxn << 1];

int n;
int head[maxn], tot;
ll ans;

void Init() {
    for (int i = 1; i <= n; ++i) {
        head[i] = -1;
    }
    ans = 0ll;
    tot = 0;
}

void addedge(int u, int v, int w) {
    edge[tot] = Edge(v, head[u], w);
    head[u] = tot++;
    edge[tot] = Edge(u, head[v], w);
    head[v] = tot++;
}

void DFS(int u, int fa) {
    ll sum = 0;
    ll Min = 1e18;
    int cnt = 0;
    for (int i = head[u]; ~i; i = edge[i].nxt) {
        sum += edge[i].w;
        cnt++;
        Min = min(Min, 1ll * edge[i].w);
        int v = edge[i].to;
        if (v == fa)
            continue;
        DFS(v, u);
    }
    ans += sum - Min + 1ll * (cnt - 1) * Min;
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        Init();
        for (int i = 1, u, v, w; i < n; ++i) {
            scanf("%d %d %d", &u, &v, &w);
            addedge(u, v, w);
        }
        DFS(1, -1);
        printf("%lld\n", ans);
    }
    return 0;
}
