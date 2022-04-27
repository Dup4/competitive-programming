#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <numeric>
#include <queue>

typedef long long LL;

const int MAXV = 3010;
const int MAXE = 100010 * 2;
const int INF = 0x3f3f3f3f;

int head[MAXV], val[MAXV], ecnt;
int to[MAXE], next[MAXE], weight[MAXE];
bool vis[MAXV];
int fa[MAXV], link[MAXV];
int n, m;

void init() {
    memset(head + 1, -1, sizeof(int) * n);
    memset(link + 1, -1, sizeof(int) * n);
    for (int i = 1; i <= n; ++i) fa[i] = i;
    ecnt = 0;
}

void add_edge(int u, int v, int w) {
    to[ecnt] = v;
    weight[ecnt] = w;
    next[ecnt] = head[u];
    head[u] = ecnt++;
    to[ecnt] = u;
    weight[ecnt] = w;
    next[ecnt] = head[v];
    head[v] = ecnt++;
}

int findset(int u) {  // 并查集
    return u == fa[u] ? u : fa[u] = findset(fa[u]);
}

void merge(int u, int v) {
    int p = u;
    while (~link[p]) p = link[p];
    link[p] = v;
    fa[v] = u;
}

int MinimumCutPhase(int cnt, int &s, int &t) {
    memset(val + 1, 0, sizeof(int) * n);
    memset(vis + 1, 0, sizeof(bool) * n);
    std::priority_queue<std::pair<int, int>> que;
    t = 1;
    while (--cnt) {
        vis[s = t] = true;
        for (int u = s; ~u; u = link[u]) {
            for (int p = head[u]; ~p; p = next[p]) {
                int v = findset(to[p]);
                if (!vis[v])
                    que.push(std::make_pair(val[v] += weight[p], v));
            }
        }
        t = 0;
        while (!t) {
            if (que.empty())
                return 0;  // 图不连通
            auto pa = que.top();
            que.pop();
            if (val[pa.second] == pa.first)
                t = pa.second;
        }
    }
    return val[t];
}

int StoerWagner() {
    int res = INF;
    for (int i = n, s, t; i > 1; --i) {
        res = std::min(res, MinimumCutPhase(i, s, t));
        if (res == 0)
            break;
        merge(s, t);
    }
    return res;
}

int main() {
    while (scanf("%d%d", &n, &m) != EOF) {
        init();
        for (int i = 0, u, v, w; i < m; ++i) {
            scanf("%d%d%d", &u, &v, &w);
            add_edge(u, v, w);
        }
        printf("%d\n", StoerWagner());
    }
}
