#include <bits/stdc++.h>
using namespace std;

#define ll long long
const int N = 2e5 + 10;
vector<vector<int> > G;
int n, k;
ll a[N], ms[N];
priority_queue<ll> pq;
int fa[N], hson[N];
void pre(int u) {
    hson[u] = 0;
    for (int o = 0, sze = (int)G[u].size(); o < sze; ++o) {
        int v = G[u][o];
        if (v == fa[u])
            continue;
        fa[v] = u;
        pre(v);
        if (!hson[u] || ms[v] > ms[hson[u]])
            hson[u] = v;
    }
    ms[u] = a[u] + ms[hson[u]];
}

void DFS(int u, int tp) {
    // cout << u << " " << tp << endl;
    if (u == tp)
        pq.push(ms[u]);
    if (hson[u])
        DFS(hson[u], tp);
    for (int o = 0, sze = (int)G[u].size(); o < sze; ++o) {
        int v = G[u][o];
        if (v == fa[u] || v == hson[u])
            continue;
        DFS(v, v);
    }
}

int main() {
    while (scanf("%d%d", &n, &k) != EOF) {
        G.clear();
        G.resize(n + 1);
        for (int i = 1; i <= n; ++i) scanf("%lld", a + i);
        for (int i = 1, u, v; i < n; ++i) {
            scanf("%d%d", &u, &v);
            G[u].push_back(v);
            G[v].push_back(u);
        }
        fa[1] = 1;
        pre(1);
        DFS(1, 1);
        ll res = 0;
        while (k && !pq.empty()) {
            --k;
            res += pq.top();
            pq.pop();
        }
        printf("%lld\n", res);
    }
    return 0;
}
