#include <bits/stdc++.h>
using namespace std;

const int N = 6e5 + 10;
const int M = 25;
const int INF = 0x3f3f3f3f;
int n, m, _n, q, a[N], _a[N], b[N], pre, suf, f[N], g[N], nxf[N], preg[N], fa[N], deep[N], sze[N], son[N], top[N],
        in[N], fin[N], out[N], sta[N];
vector<vector<int>> G;

void dfs(int u) {
    sze[u] = 1;
    son[u] = 0;
    for (auto &v : G[u]) {
        fa[v] = u;
        deep[v] = deep[u] + 1;
        dfs(v);
        sze[u] += sze[v];
        if (!son[u] || sze[v] > sze[son[u]])
            son[u] = v;
    }
}

void gettop(int u, int tp) {
    top[u] = tp;
    in[u] = ++*in;
    fin[*in] = u;
    if (son[u])
        gettop(son[u], tp);
    for (auto &v : G[u])
        if (v != son[u])
            gettop(v, v);
    out[u] = *in;
}

void gettree() {
    G.clear();
    G.resize(_n + 10);
    m = 0;
    int rt = 0;
    *in = 0;
    deep[0] = 0;
    for (int i = 1; i <= _n; ++i) {
        if (a[i] == 0) {
            ++m;
            _a[i] = m;
            fa[m] = rt;
            G[rt].push_back(m);
            rt = m;
        } else {
            _a[i] = rt;
            rt = fa[rt];
        }
    }
    fa[1] = 1;
    deep[1] = 0;
    dfs(1);
    gettop(1, 1);
}

struct SEG {
    int t[N << 2];
    inline void up(int id) {
        t[id] = max(t[id << 1], t[id << 1 | 1]);
    }
    void build(int id, int l, int r) {
        t[id] = 0;
        if (l == r)
            return;
        int mid = (l + r) >> 1;
        build(id << 1, l, mid);
        build(id << 1 | 1, mid + 1, r);
    }
    void update(int id, int l, int r, int pos, int v) {
        if (l == r) {
            t[id] = v;
            return;
        }
        int mid = (l + r) >> 1;
        if (pos <= mid)
            update(id << 1, l, mid, pos, v);
        else
            update(id << 1 | 1, mid + 1, r, pos, v);
        up(id);
    }
    int query(int id, int l, int r, int ql, int qr) {
        if (l >= ql && r <= qr)
            return t[id];
        int mid = (l + r) >> 1;
        int res = 0;
        if (ql <= mid)
            res = max(res, query(id << 1, l, mid, ql, qr));
        if (qr > mid)
            res = max(res, query(id << 1 | 1, mid + 1, r, ql, qr));
        return res;
    }
} seg[2];  // 0 in 1 out

int query(int u, int v, SEG &seg) {
    int res = 0;
    while (top[u] != top[v]) {
        if (deep[top[u]] < deep[top[v]])
            swap(u, v);
        res = max(res, seg.query(1, 1, m, in[top[u]], in[u]));
        u = fa[top[u]];
    }
    if (deep[u] > deep[v])
        swap(u, v);
    res = max(res, seg.query(1, 1, m, in[u], in[v]));
    return res;
}

using pII = pair<int, int>;
#define fi first
#define se second
struct RMQ {
    pII Max[N][M];
    int mm[N];
    function<bool(pII, pII)> cmp;
    void init(int n, int *b, const function<bool(pII, pII)> &_cmp) {
        cmp = _cmp;
        mm[0] = -1;
        for (int i = 1; i <= n; ++i) {
            mm[i] = ((i & (i - 1)) == 0) ? mm[i - 1] + 1 : mm[i - 1];
            Max[i][0] = pII(b[i], i);
        }
        for (int j = 1; j <= mm[n]; ++j) {
            for (int i = 1; i + (1 << j) - 1 <= n; ++i) {
                Max[i][j] = max(Max[i][j - 1], Max[i + (1 << (j - 1))][j - 1], cmp);
            }
        }
    }
    int queryMax(int x, int y) {
        int k = mm[y - x + 1];
        return max(Max[x][k], Max[y - (1 << k) + 1][k], cmp).se;
    }
} rmq_f, rmq_g;

int getin(int l, int r) {
    int pr = preg[r + 1], pl = rmq_g.queryMax(l, r);
    //	cout << pl << " " << pr << endl;
    if (pr < l)
        return 0;
    int u = _a[pl], v = _a[pr];
    return query(u, v, seg[0]);
}

int getout(int l, int r) {
    int pl = nxf[l - 1], pr = rmq_f.queryMax(l, r);
    //	cout << pl << " " << pr << " " << l << " " << r << endl;
    if (pl > r)
        return 0;
    int u = _a[pl], v = _a[pr];
    return query(u, v, seg[1]);
}

int getpos(int x, const function<bool(int, int)> &ok) {
    int l = 1, r = *sta, pos = 1;
    while (r - l >= 0) {
        int mid = (l + r) >> 1;
        if (ok(mid, x)) {
            pos = mid;
            l = mid + 1;
        } else
            r = mid - 1;
    }
    return pos;
}

int main() {
    while (scanf("%d%d", &n, &q) != EOF) {
        pre = suf = 0;
        for (int i = 1; i <= n; ++i) scanf("%d", a + i);
        for (int i = 1; i <= n; ++i) scanf("%d", b + i);
        f[0] = 0;
        for (int i = 1; i <= n; ++i) {
            f[i] = f[i - 1] + (a[i] == 1 ? 1 : -1);
            pre = max(pre, f[i]);
        }
        g[n + 1] = 0;
        for (int i = n; i >= 1; --i) {
            g[i] = g[i + 1] + (a[i] == 1 ? -1 : 1);
            suf = max(suf, g[i]);
        }
        ++pre;
        ++suf;
        _n = pre + n + suf;
        for (int i = n; i >= 1; --i) {
            a[pre + i] = a[i];
            b[pre + i] = b[i];
        }
        for (int i = 1; i <= pre; ++i) {
            a[i] = b[i] = 0;
        }
        for (int i = pre + n + 1; i <= _n; ++i) {
            a[i] = 1;
            b[i] = 0;
        }
        f[0] = 0;
        g[_n + 1] = 0;
        for (int i = 1; i <= _n; ++i) f[i] = f[i - 1] + (a[i] == 1 ? 1 : -1);
        for (int i = _n; i >= 1; --i) g[i] = g[i + 1] + (a[i] == 1 ? -1 : 1);
        gettree();
        seg[0].build(1, 1, m);
        seg[1].build(1, 1, m);
        for (int i = 1; i <= _n; ++i) {
            seg[a[i]].update(1, 1, m, in[_a[i]], b[i]);
        }
        f[_n + 1] = INF;
        f[0] = 0;
        *sta = 0;
        sta[++*sta] = _n + 1;
        for (int i = _n; i >= 0; --i) {
            nxf[i] = sta[getpos(i, [&](int x, int y) {
                return f[sta[x]] > f[y];
            })];
            while (*sta && f[i] > f[sta[*sta]]) --*sta;
            sta[++*sta] = i;
        }
        g[0] = INF;
        g[_n + 1] = 0;
        *sta = 0;
        sta[++*sta] = 0;
        for (int i = 1; i <= _n + 1; ++i) {
            preg[i] = sta[getpos(i, [&](int x, int y) {
                return g[sta[x]] > g[y];
            })];
            while (*sta && g[i] > g[sta[*sta]]) --*sta;
            sta[++*sta] = i;
        }
        rmq_f.init(_n, f, [&](pII x, pII y) {
            if (x.fi != y.fi)
                return x.fi < y.fi;
            return x.se > y.se;
        });
        rmq_g.init(_n, g, [&](pII x, pII y) {
            if (x.fi != y.fi)
                return x.fi < y.fi;
            return x.se < y.se;
        });
        int op, x, y;
        while (q--) {
            scanf("%d%d%d", &op, &x, &y);
            if (op == 1) {
                b[x + pre] = y;
                seg[a[x + pre]].update(1, 1, m, in[_a[x + pre]], y);
            } else {
                printf("%d\n", max(getin(x + pre, y + pre), getout(x + pre, y + pre)));
            }
        }
    }
    return 0;
}
