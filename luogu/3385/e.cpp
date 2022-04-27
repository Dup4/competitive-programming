#include <bits/stdc++.h>
#define SZ(x) (int((x).size()))
const int N = 4e3 + 10, INF = 0x3f3f3f3f;
using namespace std;
int n, m;

struct Graph {
    struct E {
        int to, nx, w;
    } e[N << 1];
    int h[N], cnt;
    void init(int n) {
        for (int i = 0; i <= n; ++i) h[i] = -1;
        cnt = -1;
    }
    void addedge(int u, int v, int w = 0) {
        e[++cnt] = {v, h[u], w};
        h[u] = cnt;
    }
} G;

namespace SPFA {
struct Node {
    int fa, val, depth;
    vector<int> ch;
    void init() {
        fa = val = depth = 0;
        ch.clear();
    }
} node[N << 1];
int dis[N];
void Change(int x, int val) {
    node[x].val = val;
    for (int i = 0; i < SZ(node[x].ch); ++i) {
        node[node[x].ch[i]].val = val;
        Change(node[x].ch[i], val);
    }
}
void Maintain(int x) {
    for (int i = 0; i < SZ(node[x].ch); ++i) {
        node[node[x].ch[i]].depth = node[x].depth + 1;
        Maintain(node[x].ch[i]);
    }
}
int queuery(int x) {
    return node[x].val;
}
void Link(int x, int y) {
    node[x].fa = y;
    node[x].depth = node[y].depth + 1;
    Maintain(x);
    node[y].ch.push_back(x);
}
void Cut(int x) {
    Node &s = node[node[x].fa];
    node[x].depth = 1;
    Maintain(x);
    for (int i = 0; i < SZ(s.ch); ++i) {
        if (s.ch[i] == x) {
            for (int j = i; j < SZ(s.ch) - 1; ++j) {
                s.ch[j] = s.ch[j + 1];
            }
            s.ch.pop_back();
            break;
        }
    }
    node[x].fa = 0;
}
int lca(int x, int y) {
    if (x == y)
        return true;
    for (int i = 0; i < SZ(node[x].ch); ++i) {
        if (lca(node[x].ch[i], y))
            return true;
    }
    return false;
}
bool gao(int S) {
    queue<int> que;
    for (int i = 0; i <= n; ++i) dis[i] = INF;
    dis[S] = 0;
    node[S].depth = 1;
    que.push(S);
    Change(S, 1);
    while (!que.empty()) {
        int u = que.front();
        que.pop();
        if (node[u].val == 0)
            continue;
        for (int i = G.h[u]; ~i; i = G.e[i].nx) {
            int v = G.e[i].to, w = G.e[i].w;
            if (dis[v] > dis[u] + w) {
                if (lca(v, u))
                    return 1;
                dis[v] = dis[u] + w;
                que.push(v);
                Change(v, 0);
                node[v].val = 1;
                Cut(v);
                Link(v, u);
            }
        }
    }
    return 0;
}
void init(int n) {
    for (int i = 1; i <= n; ++i) node[i].init();
}
}  // namespace SPFA

int main() {
    int _T;
    scanf("%d", &_T);
    while (_T--) {
        scanf("%d%d", &n, &m);
        G.init(n);
        SPFA::init(n);
        for (int i = 1, u, v, w; i <= m; ++i) {
            scanf("%d%d%d", &u, &v, &w);
            G.addedge(u, v, w);
            if (w >= 0)
                G.addedge(v, u, w);
        }
        if (SPFA::gao(1))
            puts("YE5");
        else
            puts("N0");
    }
    return 0;
}
