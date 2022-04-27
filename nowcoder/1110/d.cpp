#include <bits/stdc++.h>
using namespace std;
#define debug(...)           \
    {                        \
        printf("#  ");       \
        printf(__VA_ARGS__); \
        puts("");            \
    }
#define fi first
#define se second
#define endl "\n"
using ll = long long;
using ull = unsigned long long;
using pII = pair<int, int>;
using pLL = pair<ll, ll>;
using VI = vector<int>;
using VL = vector<ll>;
constexpr int mod = 1e9 + 7;
template <class T1, class T2>
inline void chadd(T1 &x, T2 y) {
    x += y;
    while (x >= mod) x -= mod;
    while (x < 0) x += mod;
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
template <class T>
inline void pt(T s) {
    cout << s << "\n";
}
template <class T>
inline void pt(vector<T> &vec) {
    for (auto &it : vec) cout << it << " ";
    cout << endl;
}
inline ll gcd(ll a, ll b) {
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
constexpr int N = 3e2 + 10, M = 10;
int n, m, q, black[N];
vector<vector<int>> G[2];
int f[N][M], deep[N], d[N], que[N], ql, qr, use[N];
bitset<N> T;
struct DT {
    bitset<N> B[N];
    vector<vector<int>> F;
    int g[N], vis[N], rt, res;
    void add(int fa, int x) {
        if (fa != x)
            F[fa].push_back(x);
        f[x][0] = fa;
        deep[x] = deep[fa] + 1;
        for (int i = 1; i < M; ++i) f[x][i] = f[f[x][i - 1]][i - 1];
    }
    int querylca(int u, int v) {
        if (!u)
            return v;
        if (!v)
            return u;
        if (deep[u] > deep[v])
            swap(u, v);
        for (int det = deep[v] - deep[u], i = 0; det; det >>= 1, ++i) {
            if (det & 1) {
                v = f[v][i];
            }
        }
        if (u == v)
            return u;
        for (int i = M - 1; i >= 0; --i) {
            if (f[u][i] == f[v][i])
                continue;
            u = f[u][i];
            v = f[v][i];
        }
        return f[u][0];
    }
    int getlca(int u) {
        int lca = 0;
        B[u].reset();
        for (auto &v : G[1][u])
            if (vis[v]) {
                B[u][v] = 1;
                lca = querylca(lca, v);
            }
        g[u] = lca;
        return lca;
    }
    void pre(int u) {
        if (vis[u])
            return;
        vis[u] = 1;
        for (auto &v : G[0][u]) {
            pre(v);
        }
    }
    void init(int _rt) {
        deep[rt] = 0;
        rt = _rt;
        for (int i = 1; i <= n; ++i) B[i].reset();
        F.clear();
        F.resize(n + 1);
        memset(vis, 0, sizeof vis);
        memset(d, 0, sizeof d);
        pre(rt);
        add(rt, rt);
        ql = 1, qr = 0;
        for (int u = 1; u <= n; ++u)
            if (vis[u]) {
                for (auto &v : G[0][u])
                    if (vis[v])
                        ++d[v];
            }
        for (int u = 1; u <= n; ++u)
            if (vis[u] && d[u] == 0) {
                que[++qr] = u;
                add(rt, u);
            }
        while (ql <= qr) {
            int u = que[ql];
            ++ql;
            for (auto &v : G[0][u])
                if (vis[v]) {
                    if (--d[v] == 0) {
                        que[++qr] = v;
                        add(getlca(v), v);
                    }
                }
        }
    }
    void dfs(int u) {
        if (black[u])
            use[u] = 1, T[u] = 1;
        if (u != rt) {
            if (black[u] || use[g[u]]) {
                use[u] = 1;
                T[u] = 1;
            } else if ((T | B[u]) == T) {
                use[u] = 1;
                T[u] = 1;
            } else
                ++res;
        }
        for (auto &v : F[u]) dfs(v);
    }
    int get(int now) {
        if (black[rt]) {
            return res = 0;
        }
        if (vis[now] == 0)
            return res;
        memset(use, 0, sizeof use);
        T.reset();
        res = 0;
        dfs(rt);
        return res;
    }
} dt[N];
void run() {
    G[0].clear();
    G[0].resize(n + 1);
    G[1].clear();
    G[1].resize(n + 1);
    memset(black, 0, sizeof black);
    for (int i = 1, u, v; i <= m; ++i) {
        cin >> u >> v;
        G[0][u].push_back(v);
        G[1][v].push_back(u);
    }
    for (int i = 1; i <= n; ++i) dt[i].init(i), dt[i].get(i);
    while (q--) {
        int x = rd();
        black[x] ^= 1;
        int res = 0;
        for (int i = 1; i <= n; ++i) res += dt[i].get(x);
        pt(res);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout << fixed << setprecision(20);
    while (cin >> n >> m >> q) run();
    return 0;
}
