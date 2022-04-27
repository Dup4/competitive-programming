#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e5 + 10;
int n, m, q, a[N];
ll v[N], w[N];

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

namespace MoTree {
int belong[N], blk;
int fa[N], deep[N], son[N], sze[N], top[N], id[N];
stack<int> sta;
void dfs(int u) {
    son[u] = 0;
    sze[u] = 1;
    int ss = sta.size();
    for (int i = G.h[u]; ~i; i = G.e[i].nx) {
        int v = G.e[i].to;
        if (v == fa[u])
            continue;
        fa[v] = u;
        deep[v] = deep[u] + 1;
        dfs(v);
        sze[u] += sze[v];
        if (!son[u] || sze[v] > sze[son[u]])
            son[u] = v;
        if ((int)sta.size() - ss >= blk) {
            ++*belong;
            while ((int)sta.size() != ss) belong[sta.top()] = *belong, sta.pop();
        }
    }
    sta.push(u);
}
void gettop(int u, int tp) {
    id[u] = ++*id;
    top[u] = tp;
    if (son[u])
        gettop(son[u], tp);
    for (int i = G.h[u]; ~i; i = G.e[i].nx) {
        int v = G.e[i].to;
        if (v == fa[u] || v == son[u])
            continue;
        gettop(v, v);
    }
}
int querylca(int u, int v) {
    while (top[u] != top[v]) {
        if (deep[top[u]] < deep[top[v]])
            swap(u, v);
        u = fa[top[u]];
    }
    if (deep[u] > deep[v])
        swap(u, v);
    return u;
}
struct qnode {
    int u, v, t, id;
    bool operator<(const qnode &other) const {
        if (belong[u] == belong[other.u]) {
            if (belong[v] == belong[other.v])
                return t < other.t;
            return belong[v] < belong[other.v];
        }
        return belong[u] < belong[other.u];
    }
} que[N];
int ques;
struct mnode {
    int x, y, b;
} upd[N];
int upds;
void addQuery(int u, int v) {
    ++ques;
    que[ques] = {u, v, upds, ques};
}
void addModify(int x, int y) {
    ++upds;
    upd[upds] = {x, y, 0};
}
ll ans[N], now;
int b[N], vis[N];
void back(int t) {
    if (vis[upd[t].x]) {
        now -= w[b[upd[t].y]--] * v[upd[t].y];
        now += w[++b[upd[t].b]] * v[upd[t].b];
    }
    a[upd[t].x] = upd[t].b;
}
void change(int t) {
    if (vis[upd[t].x]) {
        now -= w[b[upd[t].b]--] * v[upd[t].b];
        now += w[++b[upd[t].y]] * v[upd[t].y];
    }
    a[upd[t].x] = upd[t].y;
}
void update(int u) {
    if (vis[u])
        now -= w[b[a[u]]--] * v[a[u]];
    else
        now += w[++b[a[u]]] * v[a[u]];
    vis[u] ^= 1;
}
void move(int u, int v) {
    if (deep[u] < deep[v])
        swap(u, v);
    while (deep[u] > deep[v]) update(u), u = fa[u];
    while (u != v) update(u), update(v), u = fa[u], v = fa[v];
}
void init() {
    int limit = max(n, m);
    memset(vis, 0, sizeof(vis[0]) * (limit + 5));
    memset(b, 0, sizeof(b[0]) * (limit + 5));
    ques = upds = 0;
}
void gao() {
    for (int i = 1; i <= upds; i++) upd[i].b = a[upd[i].x], a[upd[i].x] = upd[i].y;
    for (int i = upds; i; i--) back(i);
    *belong = 0;
    *id = 0;
    fa[1] = 1;
    blk = (int)pow(n, 0.6);
    dfs(1);
    gettop(1, 1);
    if (!sta.empty()) {
        ++*belong;
        while (!sta.empty()) belong[sta.top()] = *belong, sta.pop();
    }
    for (int i = 1; i <= n; i++) {
        if (id[que[i].u] > id[que[i].v])
            swap(que[i].u, que[i].v);
    }
    sort(que + 1, que + 1 + ques);
    int u = 1, v = 1, t = 0;
    for (int i = 1; i <= ques; i++) {
        if (u != que[i].u)
            move(u, que[i].u), u = que[i].u;
        if (v != que[i].v)
            move(v, que[i].v), v = que[i].v;
        int f = querylca(u, v);
        update(f);
        while (t < que[i].t) change(++t);
        while (t > que[i].t) back(t--);
        ans[que[i].id] = now;
        update(f);
    }
    for (int i = 1; i <= ques; i++) printf("%lld\n", ans[i]);
}
}  // namespace MoTree

int main() {
    scanf("%d%d%d", &n, &m, &q);
    G.init(n);
    MoTree::init();
    for (int i = 1; i <= m; i++) scanf("%lld", v + i);
    for (int i = 1; i <= n; ++i) scanf("%lld", w + i);
    for (int i = 1, u, v; i < n; ++i) {
        scanf("%d%d", &u, &v);
        G.addedge(u, v);
        G.addedge(v, u);
    }
    for (int i = 1; i <= n; ++i) scanf("%d", a + i);
    for (int i = 1; i <= q; ++i) {
        int op, x, y;
        scanf("%d%d%d", &op, &x, &y);
        if (!op)
            MoTree::addModify(x, y);
        else
            MoTree::addQuery(x, y);
    }
    MoTree::gao();
    return 0;
}
