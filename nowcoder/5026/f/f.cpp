#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define SZ(x) int((x).size())
#define endl "\n"
using db = double;
using ll = long long;
using ull = unsigned long long;
using pII = pair<int, int>;
using pLL = pair<ll, ll>;
constexpr int mod = 1e9 + 7;
template <class T1, class T2>
inline void chadd(T1 &x, T2 y, int Mod = mod) {
    x += y;
    while (x >= Mod) x -= Mod;
    while (x < 0) x += Mod;
}
template <class T1, class T2>
inline void chmax(T1 &x, T2 y) {
    if (x < y)
        x = y;
}
template <class T1, class T2>
inline void chmin(T1 &x, T2 y) {
    if (x > y)
        x = y;
}
inline int nextInt() {
    int x;
    cin >> x;
    return x;
}
void rd() {}
template <class T, class... Ts>
void rd(T &arg, Ts &...args) {
    cin >> arg;
    rd(args...);
}
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
template <template <typename...> class T, typename t, typename... A>
void err(const T<t> &arg, const A &...args) {
    for (auto &v : arg) cout << v << ' ';
    err(args...);
}
void ptt() {
    cout << endl;
}
template <class T, class... Ts>
void ptt(const T &arg, const Ts &...args) {
    cout << ' ' << arg;
    ptt(args...);
}
template <class T, class... Ts>
void pt(const T &arg, const Ts &...args) {
    cout << arg;
    ptt(args...);
}
void pt() {}
template <template <typename...> class T, typename t, typename... A>
void pt(const T<t> &arg, const A &...args) {
    for (int i = 0, sze = arg.size(); i < sze; ++i) cout << arg[i] << " \n"[i == sze - 1];
    pt(args...);
}
inline ll qpow(ll base, ll n) {
    assert(n >= 0);
    ll res = 1;
    while (n) {
        if (n & 1)
            res = res * base % mod;
        base = base * base % mod;
        n >>= 1;
    }
    return res;
}
// head
constexpr int N = 2e5 + 10, M = 18;
const ll INF = 1e14;
int n, m, _n, q, a[N];

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

ll res;
int fa[N], in[N], out[N], r[N << 1];
ll dis[N];
int _dis[N];
void dfs(int u) {
    r[++*r] = u;
    in[u] = *r;
    for (int i = G.h[u]; ~i; i = G.e[i].nx) {
        int v = G.e[i].to;
        ll w = G.e[i].w;
        if (v == fa[u])
            continue;
        fa[v] = u;
        dis[v] = dis[u] + w;
        dfs(v);
        r[++*r] = u;
    }
    out[u] = *r;
}

struct RMQ {
    int Min[N][M];
    int mm[N];
    void init(int n, int *b) {
        mm[0] = -1;
        for (int i = 1; i <= n; ++i) {
            mm[i] = ((i & (i - 1)) == 0) ? mm[i - 1] + 1 : mm[i - 1];
            Min[i][0] = b[i];
        }
        for (int j = 1; j <= mm[n]; ++j) {
            for (int i = 1; i + (1 << j) - 1 <= n; ++i) {
                Min[i][j] = min(Min[i][j - 1], Min[i + (1 << (j - 1))][j - 1]);
            }
        }
    }
    int queryMin(int x, int y) {
        assert(x <= y);
        int k = mm[y - x + 1];
        return min(Min[x][k], Min[y - (1 << k) + 1][k]);
    }
} rmq;

struct SEG {
    struct node {
        int ls, rs;
        ll val, LM, MR;
        void init(ll _val) {
            ls = rs = 0;
            val = _val;
            LM = MR = _val;
        }
    } t[N * 50], res;
    int cnt;
    void init() {
        cnt = 0;
        t[0].val = t[0].LM = t[0].MR = INF;
    }
    int newnode(int val) {
        ++cnt;
        t[cnt].init(val);
        return cnt;
    }
    void pushup(int id, int l, int r) {
        int mid = (l + r) >> 1;
        int ls = t[id].ls, rs = t[id].rs;
        t[id].val = min(t[ls].val, t[rs].val);
        t[id].LM = min({t[ls].LM, t[rs].LM, t[ls].val - 2ll * rmq.queryMin(mid + 1, r)});
        t[id].MR = min({t[ls].MR, t[rs].MR, -2ll * rmq.queryMin(l, mid) + t[rs].val});
    }
    void update(int &id, int l, int r, int pos, ll v) {
        if (!id)
            id = newnode(v);
        //	dbg(id, l, r, pos, v);
        if (l == r) {
            t[id].init(v);
            return;
        }
        int mid = (l + r) >> 1;
        if (pos <= mid)
            update(t[id].ls, l, mid, pos, v);
        else
            update(t[id].rs, mid + 1, r, pos, v);
        pushup(id, l, r);
    }
    void query(int id, int l, int r, int ql, int qr) {
        dbg(id, l, r, ql, qr);
        //	return;
        if (ql > qr)
            return;
        int mid = (l + r) >> 1;
        if (!id) {
            chmin(res.LM, res.val + rmq.queryMin(l, r));
            return;
        }
        if (l >= ql && r <= qr) {
            dbg(id, l, r, ql, qr);
            res.val = min(res.val, t[id].val);
            res.LM = min({res.LM, t[id].LM, res.val - 2ll * rmq.queryMin(l, r)});
            if (ql < l)
                res.MR = min({res.MR, t[id].MR, -2ll * rmq.queryMin(ql, l - 1) + t[id].val});
            return;
        }
        if (ql <= mid)
            query(t[id].ls, l, mid, ql, qr);
        if (qr > mid)
            query(t[id].rs, mid + 1, r, ql, qr);
    }
} seg;

struct TSEG {
    int t[N << 2];
    void init() {
        memset(t, 0, sizeof t);
    }
    void update(int id, int l, int r, int x, int pos, int v) {
        seg.update(t[id], 1, _n, pos, v);
        // dbg(id, l, r, x, pos, v);
        if (l == r)
            return;
        int mid = (l + r) >> 1;
        if (x <= mid)
            update(id << 1, l, mid, x, pos, v);
        else
            update(id << 1 | 1, mid + 1, r, x, pos, v);
    }
    void query(int id, int l, int r, int ql, int qr, int pos) {
        //	dbg(id, l, r, ql, qr);
        if (l >= ql && r <= qr) {
            seg.res.val = seg.res.LM = seg.res.MR = INF;
            seg.query(t[id], 1, _n, 1, in[pos]);
            dbg(id, l, r, ql, qr, pos, seg.res.LM);
            chmin(res, seg.res.LM);
            seg.res.val = seg.res.LM = seg.res.MR = INF;
            seg.query(t[id], 1, _n, in[pos], _n);
            dbg(id, l, r, ql, qr, pos, seg.res.MR);
            chmin(res, seg.res.MR);
            return;
        }
        int mid = (l + r) >> 1;
        if (ql <= mid)
            query(id << 1, l, mid, ql, qr, pos);
        if (qr > mid)
            query(id << 1 | 1, mid + 1, r, ql, qr, pos);
    }
} tseg;

void run() {
    rd(n, q);
    G.init(n);
    m = 1e4;
    for (int i = 1; i <= n; ++i) rd(a[i]);
    for (int i = 1, u, v, w; i < n; ++i) {
        rd(u, v, w);
        G.addedge(u, v, w);
        G.addedge(v, u, w);
    }
    *r = 0;
    dfs(1);
    _n = *r;
    for (int i = 1; i <= _n; ++i) _dis[i] = dis[r[i]];
    for (int i = 1; i <= n; ++i) dbg(i, in[i], out[i]);
    rmq.init(_n, _dis);
    seg.init();
    tseg.init();
    for (int i = 1; i <= n; ++i) {
        //	dbg(i, a[i], dis[i]);
        tseg.update(1, 1, m, a[i], in[i], dis[i]);
        //	tseg.update(1, 1, m, a[i], out[i], dis[i]);
    }
    //	dbg(seg.t[1].val, seg.t[1].LM, seg.t[1].MR);
    for (int i = 1, op, u, x, y; i <= q; ++i) {
        rd(op, u, x);
        if (op == 1) {
            tseg.update(1, 1, m, x, in[u], dis[u]);
            //		tseg.update(1, 1, m, x, out[u], dis[u]);
        } else {
            rd(y);
            res = INF;
            tseg.query(1, 1, m, x, y, u);
            if (res >= INF)
                pt(-1);
            else
                pt((res + dis[u]) * 2);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout << fixed << setprecision(20);
    run();
    //	while (cin >> n) run();
    //    for (int kase = 1; kase <= _T; ++kase) {
    //        cout << "Case #" << kase << ":\n";
    //        run();
    //    }
    return 0;
}
