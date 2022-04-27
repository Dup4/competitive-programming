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
using pII = pair<int, int>;
using pLL = pair<ll, ll>;
using VI = vector<int>;
using VL = vector<ll>;
constexpr int mod = 1e9 + 7;
template <class T1, class T2>
inline void chadd(T1 &x, T2 y) {
    x += y;
    if (x >= mod)
        x -= mod;
    else if (x < 0)
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
template <class T>
inline void out(T s) {
    cout << s << "\n";
}
template <class T>
inline void out(vector<T> &vec) {
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
const int N = 1e6 + 10;
const int M = 25;
struct Graph {
    struct node {
        int to, nx;
        node() {}
        node(int to, int nx) : to(to), nx(nx) {}
    } a[N * 10];
    int head[N], pos;
    void init() {
        memset(head, -1, sizeof head);
        pos = 0;
    }
    void add(int u, int v) {
        a[pos] = node(v, head[u]);
        head[u] = pos++;
    }
} G[3];
#define erp(G, u) for (int it = G.head[u], v = G.a[it].to; ~it; it = G.a[it].nx, v = G.a[it].to)
int n, m, f[N][M], deep[N], d[N];
struct Dominator_Tree {
    int que[N], l, r;
    void add(int fa, int x) {
        if (fa != x)
            G[2].add(fa, x);
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
    int getlca(int x) {
        int lca = 0;
        erp(G[1], x) lca = querylca(lca, v);
        return lca;
    }
    void work() {
        int S = 1;
        add(S, S);
        deep[S] = 0;
        l = 1, r = 0;
        que[++r] = S;
        while (l <= r) {
            int u = que[l];
            ++l;
            erp(G[0], u) {
                --d[v];
                if (d[v] == 0) {
                    que[++r] = v;
                    add(getlca(v), v);
                }
            }
        }
    }
} dt;
int Move[][2] = {
        {-1, 0},
        {0, -1},
};
inline bool ok(int x, int y) {
    if (x < 1 || x > n || y < 1 || y > m)
        return 0;
    return 1;
}
inline int id(int x, int y) {
    return (x - 1) * m + y;
}
void run() {
    vector<string> S(n + 1);
    vector<vector<int>> g(n + 1, vector<int>(m + 1, 0));
    for (int i = 1; i <= n; ++i) {
        cin >> S[i];
        S[i].insert(S[i].begin(), '0');
    }
    g[1][1] = 1;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j) {
            if (i == 1 && j == 1)
                continue;
            g[i][j] = 0;
            if (S[i][j] == '#')
                continue;
            for (int k = 0; k < 2; ++k) {
                int px = i + Move[k][0];
                int py = j + Move[k][1];
                if (ok(px, py)) {
                    g[i][j] |= g[px][py];
                }
            }
        }
    if (!g[n][m])
        return out(0);
    if (n == 1 || m == 1)
        return out(1);
    if (S[n - 1][m] == '#' || S[n][m - 1] == '#')
        return out(1);
    for (int i = 0; i <= n * m + 1; ++i) {
        deep[i] = 0;
        f[i][0] = 0;
        d[i] = 0;
    }
    for (int i = 0; i < 3; ++i) G[i].init();
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (g[i][j] == 0)
                continue;
            for (int k = 0; k < 2; ++k) {
                int nx = i - Move[k][0];
                int ny = j - Move[k][1];
                if (ok(nx, ny) && g[nx][ny]) {
                    G[0].add(id(i, j), id(nx, ny));
                    G[1].add(id(nx, ny), id(i, j));
                    ++d[id(nx, ny)];
                }
            }
        }
    }
    //	for (int i = 1; i <= n * m; ++i)
    //		erp(G[0], i)
    //			cout << i << " " << v << endl;
    dt.work();
    if (deep[id(n, m)] == 1)
        out(2);
    else
        out(1);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout << fixed << setprecision(20);
    while (cin >> n >> m) run();
    return 0;
}
