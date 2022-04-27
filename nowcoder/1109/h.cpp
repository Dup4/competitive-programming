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
constexpr int N = 1e5 + 10;
int n, fa[N];
struct node {
    int x, y;
    ll z;
    bool operator<(const node &other) const {
        return z < other.z;
    }
};
node f[N][2], g[N];
vector<node> G;
struct Edge {
    int v, nx;
    ll w;
} e[N << 1];
int h[N];
inline void addedge(int u, int v, int w) {
    e[++*h] = {v, h[u], w};
    h[u] = *h;
}
void dfs(int u) {
    f[u][0] = {u, u, 0};
    f[u][1] = {u, u, 0};
    for (int i = h[u]; i; i = e[i].nx) {
        int v = e[i].v;
        ll w = e[i].w;
        if (v == fa[u])
            continue;
        fa[v] = u;
        dfs(v);
        if (f[v][0].z + w > f[u][0].z) {
            f[u][1] = f[u][0];
            f[u][0] = f[v][0];
            f[u][0].z += w;
            f[u][0].x = v;
        } else if (f[v][0].z + w > f[u][1].z) {
            f[u][1] = f[v][0];
            f[u][1].z += w;
            f[u][1].x = v;
        }
    }
}
void dfs2(int u) {
    if (g[u].y != u && g[u].y)
        G.push_back({u, g[u].y, g[u].z});
    if (f[u][0].y != u && f[u][0].y)
        G.push_back({u, f[u][0].y, f[u][0].z});
    if (f[u][1].y != u && f[u][1].y)
        G.push_back({u, f[u][1].y, f[u][1].z});
    for (int i = h[u]; i; i = e[i].nx) {
        int v = e[i].v;
        ll w = e[i].w;
        if (v == fa[u])
            continue;
        g[v] = g[u];
        if (f[u][0].x == v) {
            g[v] = max(g[v], f[u][1]);
        } else {
            g[v] = max(g[v], f[u][0]);
        }
        g[v].z += w;
        dfs2(v);
    }
}
int pre[N];
int find(int x) {
    return pre[x] == 0 ? x : pre[x] = find(pre[x]);
}
void Kruskal() {
    ll res = 0;
    sort(G.begin(), G.end(), [&](node x, node y) {
        return x.z > y.z;
    });
    int cnt = 1;
    memset(pre, 0, sizeof pre);
    for (auto &it : G) {
        int u = it.x, v = it.y;
        ll w = it.z;
        u = find(u), v = find(v);
        if (u == v)
            continue;
        ++cnt;
        res += w;
        pre[u] = v;
    }
    assert(cnt == n);
    pt(res);
}

void run() {
    G.clear();
    memset(h, 0, sizeof h);
    for (int i = 1, u, v, w; i < n; ++i) {
        cin >> u >> v >> w;
        addedge(u, v, w);
        addedge(v, u, w);
    }
    dfs(1);
    g[1] = {0, 1, 0};
    dfs2(1);
    Kruskal();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout << fixed << setprecision(20);
    while (cin >> n) run();
    return 0;
}
