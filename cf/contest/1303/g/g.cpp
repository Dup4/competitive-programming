#include <bits/stdc++.h>
#define fi first
#define se second
#define SZ(x) ((int)x.size())
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
constexpr int N = 2e5 + 10;
constexpr ll INF = 1e18;
int n;
ll a[N];

struct Line {
    mutable ll k, m, p;
    bool operator<(const Line &o) const {
        return k < o.k;
    }
    bool operator<(ll x) const {
        return p < x;
    }
};

struct LineContainer : multiset<Line, less<>> {
    ll div(ll a, ll b) {
        return a / b - ((a ^ b) < 0 && a % b);
    }
    bool isect(iterator x, iterator y) {
        if (y == end()) {
            x->p = INF;
            return false;
        }
        if (x->k == y->k)
            x->p = x->m > y->m ? INF : -INF;
        else
            x->p = div(y->m - x->m, x->k - y->k);
        return x->p >= y->p;
    }
    void add(ll k, ll m) {
        auto z = insert({k, m, 0}), y = z++, x = y;
        while (isect(y, z)) z = erase(z);
        if (x != begin() && isect(--x, y))
            isect(x, y = erase(y));
        while ((y = x) != begin() && (--x)->p >= y->p) isect(x, erase(y));
    }
    ll query(ll x) {
        if (empty())
            return 0;
        auto it = lower_bound(x);
        assert(it != end());
        return (*it).k * x + (*it).m;
    }
};

vector<vector<int>> G;
namespace DCTree {
int all, rt, vis[N];
int sze[N], f[N];
ll deep[N], sum[N], tot[N], res;
LineContainer lc;
void getrt(int u, int fa) {
    f[u] = 0, sze[u] = 1;
    for (auto &v : G[u]) {
        if (v == fa || vis[v])
            continue;
        getrt(v, u);
        sze[u] += sze[v];
        f[u] = max(f[u], sze[v]);
    }
    f[u] = max(f[u], all - sze[u]);
    if (f[u] < f[rt])
        rt = u;
}
void getdeep(int u, int fa) {
    chmax(res, lc.query(deep[u]) + tot[u]);
    for (auto &v : G[u]) {
        if (v == fa || vis[v])
            continue;
        deep[v] = deep[u] + 1;
        sum[v] = sum[u] + a[v];
        tot[v] = tot[u] + sum[v];
        getdeep(v, u);
    }
}
void add(int u, int fa) {
    chmax(res, tot[u]);
    lc.add(sum[u], tot[u]);
    for (auto &v : G[u]) {
        if (v == fa || vis[v])
            continue;
        deep[v] = deep[u] + 1;
        sum[v] = sum[u] + a[v];
        tot[v] = tot[u] + a[v] * deep[v];
        add(v, u);
    }
}
void calc(int u) {
    deep[u] = 0;
    tot[u] = sum[u] = a[u];
    lc.clear();
    lc.add(a[u], a[u]);
    for (auto &v : G[u]) {
        if (vis[v])
            continue;
        deep[v] = 1;
        sum[v] = a[v];
        tot[v] = a[v];
        getdeep(v, u);
        deep[v] = 2;
        sum[v] = sum[u] + a[v];
        tot[v] = tot[u] + a[v] * deep[v];
        add(v, u);
    }
}
void solve(int u) {
    vis[u] = 1;
    calc(u);
    reverse(G[u].begin(), G[u].end());
    calc(u);
    for (auto &v : G[u]) {
        if (vis[v])
            continue;
        all = f[0] = sze[v];
        rt = 0;
        getrt(v, 0);
        solve(rt);
    }
}
void gao() {
    res = *max_element(a + 1, a + 1 + n);
    memset(vis, 0, sizeof vis);
    all = f[0] = n;
    rt = 0;
    getrt(1, 0);
    solve(rt);
    pt(res);
}
};  // namespace DCTree

void run() {
    G.clear();
    G.resize(n + 1);
    for (int i = 1, u, v; i < n; ++i) {
        cin >> u >> v;
        G[u].push_back(v);
        G[v].push_back(u);
    }
    for (int i = 1; i <= n; ++i) rd(a[i]);
    DCTree::gao();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout << fixed << setprecision(20);
    while (cin >> n) run();
    return 0;
}
