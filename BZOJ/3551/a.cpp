#include <bits/stdc++.h>
using namespace std;
#define dbg(x...)                             \
    do {                                      \
        cout << "\033[32;1m" << #x << " -> "; \
        err(x);                               \
    } while (0)
void err() {
    cout << "\033[39;0m" << endl;
}
template <class T, class... Ts>
void err(const T &arg, const Ts &...args) {
    cout << arg << ' ';
    err(args...);
}
const int N = 2e5 + 10, M = 20, INF = 0x3f3f3f3f;
int n, m, q, h[N];

struct E {
    int u, v, w;
    bool operator<(const E &other) const {
        return w < other.w;
    }
} e[N * 3];

struct Hash {
    vector<int> a;
    int &operator[](int x) {
        return a[x - 1];
    }
    void init() {
        a.clear();
    }
    void add(int x) {
        a.push_back(x);
    }
    void gao() {
        sort(a.begin(), a.end());
        a.erase(unique(a.begin(), a.end()), a.end());
    }
    int query(int x) {
        return lower_bound(a.begin(), a.end(), x) - a.begin() + 1;
    }
} hs;

struct Graph {
    struct E {
        int to, nx, w;
    } e[N << 1];
    int h[N], cnt;
    void init(int n) {
        for (int i = 1; i <= n; ++i) h[i] = -1;
        cnt = -1;
    }
    void addedge(int u, int v, int w) {
        e[++cnt] = {v, h[u], w};
        h[u] = cnt;
    }
} G;

int val[N];
struct MST {
    int fa[N], id;
    int find(int x) {
        return fa[x] == 0 ? x : fa[x] = find(fa[x]);
    }
    void init(int n) {
        for (int i = 1; i <= n * 2; ++i) fa[i] = 0;
        id = n;
    }
    void build(int n, int m) {
        G.init(n * 2);
        init(n);
        sort(e + 1, e + 1 + m);
        for (int i = 1; i <= m; ++i) {
            int u = find(e[i].u), v = find(e[i].v), w = e[i].w;
            if (u == v)
                continue;
            ++id;
            val[id] = w;
            G.addedge(id, u, w);
            G.addedge(id, v, w);
            fa[u] = fa[v] = id;
        }
    }
} mst;

struct SEG {
    struct node {
        int ls, rs, v;
        node() {}
        void init() {
            ls = rs = v = 0;
        }
    } t[N * 18];
    int tot;
    int newnode() {
        ++tot;
        t[tot].init();
        return tot;
    }
    void Copy(int &x) {
        int tmp = newnode();
        t[tmp] = t[x];
        x = tmp;
    }
    void init() {
        tot = 0;
    }
    void pushup(int id) {
        int ls = t[id].ls, rs = t[id].rs;
        t[id].v = t[ls].v + t[rs].v;
    }
    void update(int &id, int l, int r, int pos, int v) {
        if (!id)
            id = newnode();
        if (l == r) {
            t[id].v += v;
            return;
        }
        int mid = (l + r) >> 1;
        if (pos <= mid)
            update(t[id].ls, l, mid, pos, v);
        else
            update(t[id].rs, mid + 1, r, pos, v);
        pushup(id);
    }
    void merge(int &x, int y, int l, int r) {
        if (!x || !y) {
            x |= y;
            return;
        }
        Copy(x);
        if (l == r) {
            t[x].v += t[y].v;
            return;
        }
        int mid = (l + r) >> 1;
        merge(t[x].ls, t[y].ls, l, mid);
        merge(t[x].rs, t[y].rs, mid + 1, r);
        pushup(x);
    }
    int query(int id, int l, int r, int k) {
        if (k <= 0)
            return -1;
        if (!id)
            return -1;
        if (l == r)
            return l;
        int mid = (l + r) >> 1;
        if (t[t[id].ls].v >= k)
            return query(t[id].ls, l, mid, k);
        else
            return query(t[id].rs, mid + 1, r, k - t[t[id].ls].v);
    }
} seg;

struct LCA {
    int fa[N][M];
    int segrt[N];
    void dfs(int u) {
        segrt[u] = 0;
        if (u <= n) {
            val[u] = 0;
            seg.update(segrt[u], 1, n, h[u], 1);
        }
        for (int i = 1; i < M; ++i) {
            fa[u][i] = fa[fa[u][i - 1]][i - 1];
        }
        for (int i = G.h[u]; ~i; i = G.e[i].nx) {
            int v = G.e[i].to;
            if (v == fa[u][0])
                continue;
            fa[v][0] = u;
            dfs(v);
            val[u] = max(val[u], val[v]);
            seg.merge(segrt[u], segrt[v], 1, n);
        }
    }
    void init(int rt) {
        fa[rt][0] = rt;
        dfs(rt);
    }
    int Jump(int u, int limit) {
        for (int i = M - 1; i >= 0; --i) {
            if (val[fa[u][i]] <= limit) {
                u = fa[u][i];
            }
        }
        return u;
    }
} lca;

int main() {
    while (scanf("%d%d%d", &n, &m, &q) != EOF) {
        hs.init();
        for (int i = 1; i <= n; ++i) {
            scanf("%d", h + i);
            hs.add(h[i]);
        }
        hs.gao();
        for (int i = 1; i <= n; ++i) h[i] = hs.query(h[i]);
        for (int i = 1; i <= m; ++i) {
            scanf("%d%d%d", &e[i].u, &e[i].v, &e[i].w);
        }
        mst.build(n, m);
        lca.init(mst.id);
        int lstans = 0;
        for (int i = 1, v, x, k; i <= q; ++i) {
            scanf("%d%d%d", &v, &x, &k);
            v ^= lstans;
            x ^= lstans;
            k ^= lstans;
            int pos = lca.Jump(v, x);
            //	dbg(i, v, pos);
            lstans = seg.query(lca.segrt[pos], 1, n, seg.t[lca.segrt[pos]].v - k + 1);
            if (lstans != -1)
                lstans = hs[lstans];
            printf("%d\n", lstans);
            if (lstans == -1)
                lstans = 0;
        }
    }
    return 0;
}
