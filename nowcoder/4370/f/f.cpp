#include <bits/stdc++.h>
#define fi first
#define se second
#define SZ(x) int((x).size())
#define endl "\n"
using namespace std;
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
constexpr int N = 1e5 + 10;
constexpr int MOD = 1e9 + 7;
int n, w[N];
vector<vector<int>> G;

struct SEG {
    struct node {
        int l, r;
        ll sum[3], lazy[3];
        node() {}
        node(int _l, int _r) {
            l = _l, r = _r;
            memset(sum, 0, sizeof sum);
            lazy[0] = 0, lazy[1] = 1, lazy[2] = -1;
        }
    } t[N << 2];
    void pushup(int id) {
        for (int i = 0; i < 3; ++i) {
            t[id].sum[i] = (t[id << 1].sum[i] + t[id << 1 | 1].sum[i]) % MOD;
        }
    }

    // add
    void work1(node &r, ll b) {
        int len = r.r - r.l + 1;
        r.sum[2] = (r.sum[2] + (len * b % MOD * b % MOD * b % MOD) + (3 * b % MOD * b % MOD * r.sum[0] % MOD) +
                           (3 * b % MOD * r.sum[1] % MOD)) %
                   MOD;
        r.sum[1] = (r.sum[1] + (2 * b % MOD * r.sum[0] % MOD) + (len * b % MOD * b % MOD)) % MOD;
        r.sum[0] = (r.sum[0] + len * b % MOD) % MOD;
        r.lazy[0] = (r.lazy[0] + b) % MOD;
    }

    // mul
    void work2(node &r, ll b) {
        r.sum[0] = (r.sum[0] * b) % MOD;
        r.sum[1] = (r.sum[1] * b % MOD * b) % MOD;
        r.sum[2] = (r.sum[2] * b % MOD * b % MOD * b) % MOD;
        r.lazy[0] = r.lazy[0] * b % MOD;
        r.lazy[1] = r.lazy[1] * b % MOD;
    }

    // change
    void work3(node &r, ll b) {
        int len = r.r - r.l + 1;
        r.sum[0] = len * b % MOD;
        r.sum[1] = r.sum[0] * b % MOD;
        r.sum[2] = r.sum[1] * b % MOD;
        r.lazy[0] = 0;
        r.lazy[1] = 1;
        r.lazy[2] = b;
    }

    void pushdown(int id) {
        if (t[id].l >= t[id].r)
            return;
        if (~t[id].lazy[2]) {
            work3(t[id << 1], t[id].lazy[2]);
            work3(t[id << 1 | 1], t[id].lazy[2]);
            t[id].lazy[2] = -1;
        }
        if (t[id].lazy[1] != 1) {
            work2(t[id << 1], t[id].lazy[1]);
            work2(t[id << 1 | 1], t[id].lazy[1]);
            t[id].lazy[1] = 1;
        }
        if (t[id].lazy[0]) {
            work1(t[id << 1], t[id].lazy[0]);
            work1(t[id << 1 | 1], t[id].lazy[0]);
            t[id].lazy[0] = 0;
        }
    }

    void build(int id, int l, int r) {
        t[id] = node(l, r);
        if (l == r)
            return;
        int mid = (l + r) >> 1;
        build(id << 1, l, mid);
        build(id << 1 | 1, mid + 1, r);
    }

    void update(int id, int l, int r, int vis, ll val) {
        if (t[id].l >= l && t[id].r <= r) {
            if (vis == 1)
                work3(t[id], val);
            else if (vis == 2)
                work1(t[id], val);
            else
                work2(t[id], val);
            return;
        }
        pushdown(id);
        int mid = (t[id].l + t[id].r) >> 1;
        if (l <= mid)
            update(id << 1, l, r, vis, val);
        if (r > mid)
            update(id << 1 | 1, l, r, vis, val);
        pushup(id);
    }

    ll query(int id, int l, int r, int p) {
        if (t[id].l >= l && t[id].r <= r)
            return t[id].sum[p];
        int res = 0;
        pushdown(id);
        int mid = (t[id].l + t[id].r) >> 1;
        if (l <= mid)
            res = (res + query(id << 1, l, r, p)) % MOD;
        if (r > mid)
            res = (res + query(id << 1 | 1, l, r, p)) % MOD;
        return res;
    }

} seg;

struct HLD {
    int fa[N], deep[N], sze[N], son[N], top[N], in[N], out[N];
    void dfs(int u) {
        sze[u] = 1;
        son[u] = 0;
        for (auto &v : G[u])
            if (v != fa[u]) {
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
        if (son[u])
            gettop(son[u], tp);
        for (auto &v : G[u]) {
            if (v != son[u] && v != fa[u]) {
                gettop(v, v);
            }
        }
        out[u] = *in;
    }
    void init(int rt) {
        *in = 0;
        fa[rt] = rt;
        dfs(rt);
        gettop(rt, rt);
    }
    void update(int u, int v, int w, int opt) {
        while (top[u] != top[v]) {
            if (deep[top[u]] < deep[top[v]])
                swap(u, v);
            seg.update(1, in[top[u]], in[u], opt, w);
            u = fa[top[u]];
        }
        if (deep[u] > deep[v])
            swap(u, v);
        seg.update(1, in[u], in[v], opt, w);
    }
    ll query(int u, int v) {
        ll res = 0;
        while (top[u] != top[v]) {
            if (deep[top[u]] < deep[top[v]])
                swap(u, v);
            res += seg.query(1, in[top[u]], in[u], 2);
            res %= MOD;
            u = fa[top[u]];
        }
        if (deep[u] > deep[v])
            swap(u, v);
        res += seg.query(1, in[u], in[v], 2);
        res %= MOD;
        return res;
    }
} hld;

void run() {
    rd(n);
    G.clear();
    G.resize(n + 1);
    for (int i = 1, u, v; i < n; ++i) {
        rd(u, v);
        G[u].push_back(v);
        G[v].push_back(u);
    }
    for (int i = 1; i <= n; ++i) rd(w[i]);
    seg.build(1, 1, n);
    hld.init(1);
    for (int i = 1; i <= n; ++i) hld.update(i, i, w[i], 1);
    int q;
    rd(q);
    while (q--) {
        int op, u, v, w;
        rd(op, u, v);
        if (op <= 3) {
            rd(w);
            hld.update(u, v, w, op);
        } else {
            pt(hld.query(u, v));
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout << fixed << setprecision(20);
    int _T = nextInt();
    for (int kase = 1; kase <= _T; ++kase) {
        cout << "Case #" << kase << ":\n";
        run();
    }
    return 0;
}
