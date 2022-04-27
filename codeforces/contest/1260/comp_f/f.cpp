#pragma GCC optimize("Ofast,unroll-loops,no-stack-protector,fast-math")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#include <bits/stdc++.h>
#define fi first
#define se second
#define endl "\n"
using namespace std;
using db = double;
using ll = long long;
using ull = unsigned long long;
using pII = pair<int, int>;
using pLL = pair<ll, ll>;
constexpr int mod = 1e9 + 7;
template <class T1, class T2>
inline void chadd(T1 &x, T2 y) {
    x += y;
    if (x >= mod)
        x -= mod;
    if (x < 0)
        x += mod;
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
inline int rd() {
    int x;
    cin >> x;
    return x;
}
template <class T>
inline void rd(T &x) {
    cin >> x;
}
template <class T>
inline void rd(vector<T> &vec) {
    for (auto &it : vec) cin >> it;
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
inline void pt() {
    cout << endl;
}
template <class T, class... Ts>
void pt(const T &arg, const Ts &...args) {
    cout << arg << ' ';
    pt(args...);
}
template <template <typename...> class T, typename t, typename... A>
void pt(const T<t> &arg, const A &...args) {
    for (auto &v : arg) cout << v << ' ';
    pt(args...);
}
ll gcd(ll a, ll b) {
    return b ? gcd(b, a % b) : a;
}
inline ll qpow(ll base, ll n) {
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
int n, m, l[N], r[N], inv[N];
vector<vector<int>> G;
ll P, res;

struct SEG {
    struct node {
        int cnt, sum, lazy;
        node() {
            sum = cnt = lazy = 0;
        }
        void up(int x) {
            sum = (sum + 1ll * x * cnt % mod) % mod;
            lazy = (lazy + x) % mod;
        }
        node operator+(const node &other) const {
            node res = node();
            res.cnt = (cnt + other.cnt) % mod;
            res.sum = (sum + other.sum) % mod;
            return res;
        }
    } t[N << 2];
    void pushdown(int id) {
        int &lazy = t[id].lazy;
        if (lazy) {
            t[id << 1].up(lazy);
            t[id << 1 | 1].up(lazy);
            lazy = 0;
        }
    }
    void build(int id, int l, int r) {
        t[id] = node();
        if (l == r) {
            t[id].cnt = 1;
            return;
        }
        int mid = (l + r) >> 1;
        build(id << 1, l, mid);
        build(id << 1 | 1, mid + 1, r);
        t[id] = t[id << 1] + t[id << 1 | 1];
    }
    void update(int id, int l, int r, int ql, int qr, int v) {
        if (l >= ql && r <= qr) {
            t[id].up(v);
            return;
        }
        int mid = (l + r) >> 1;
        pushdown(id);
        if (ql <= mid)
            update(id << 1, l, mid, ql, qr, v);
        if (qr > mid)
            update(id << 1 | 1, mid + 1, r, ql, qr, v);
        t[id] = t[id << 1] + t[id << 1 | 1];
    }
    int query(int id, int l, int r, int ql, int qr) {
        if (l >= ql && r <= qr)
            return t[id].sum;
        int mid = (l + r) >> 1;
        pushdown(id);
        int res = 0;
        if (ql <= mid)
            chadd(res, query(id << 1, l, mid, ql, qr));
        if (qr > mid)
            chadd(res, query(id << 1 | 1, mid + 1, r, ql, qr));
        return res;
    }
} seg[2];

int rt, all, deep[N], sze[N], f[N], vis[N];
void getrt(int u, int fa) {
    sze[u] = 1;
    f[u] = 0;
    for (auto &v : G[u])
        if (v != fa && !vis[v]) {
            getrt(v, u);
            sze[u] += sze[v];
            chmax(f[u], sze[v]);
        }
    chmax(f[u], all - sze[u]);
    if (f[u] < f[rt])
        rt = u;
}

void getdeep(int u, int fa) {
    res = (res + 1ll * seg[0].query(1, 1, m, l[u], r[u]) * inv[r[u] - l[u] + 1] % mod) % mod;
    res = (res + 1ll * seg[1].query(1, 1, m, l[u], r[u]) * inv[r[u] - l[u] + 1] % mod * deep[u] % mod) % mod;
    for (auto &v : G[u])
        if (v != fa && !vis[v]) {
            deep[v] = deep[u] + 1;
            getdeep(v, u);
        }
}

void add(int u, int fa, int f) {
    seg[0].update(1, 1, m, l[u], r[u], (P * inv[r[u] - l[u] + 1] % mod * deep[u] % mod * f + mod) % mod);
    seg[1].update(1, 1, m, l[u], r[u], (P * inv[r[u] - l[u] + 1] % mod * f + mod) % mod);
    for (auto &v : G[u])
        if (v != fa && !vis[v]) {
            add(v, u, f);
        }
}

void gao(int u) {
    vis[u] = 1;
    seg[1].update(1, 1, m, l[u], r[u], P * inv[r[u] - l[u] + 1] % mod);
    for (auto &v : G[u])
        if (!vis[v]) {
            deep[v] = 1;
            getdeep(v, u);
            add(v, u, 1);
        }
    seg[1].update(1, 1, m, l[u], r[u], (1ll * mod - P * inv[r[u] - l[u] + 1] % mod) % mod);
    for (auto &v : G[u])
        if (!vis[v])
            add(v, u, -1);
    for (auto &v : G[u])
        if (!vis[v]) {
            all = f[0] = sze[v];
            rt = 0;
            getrt(v, 0);
            gao(rt);
        }
}

void run() {
    res = 0;
    P = 1;
    G.clear();
    G.resize(n + 1);
    memset(vis, 0, sizeof vis);
    for (int i = 1; i <= n; ++i) cin >> l[i] >> r[i], P = P * (r[i] - l[i] + 1) % mod;
    for (int i = 1, u, v; i < n; ++i) {
        cin >> u >> v;
        G[u].push_back(v);
        G[v].push_back(u);
    }
    seg[0].build(1, 1, m);
    seg[1].build(1, 1, m);
    all = f[0] = n;
    rt = 0;
    getrt(1, 0);
    gao(rt);
    cout << res << endl;
}

int main() {
    m = 1e5;
    inv[1] = 1;
    for (int i = 2; i < N; ++i) {
        inv[i] = 1ll * inv[mod % i] * (mod - mod / i) % mod;
    }
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout << fixed << setprecision(20);
    while (cin >> n) run();
    return 0;
}
