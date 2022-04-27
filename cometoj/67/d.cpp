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
constexpr int mod = 998244353;
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
// template <class T> inline void out(T s) { cout << s << "\n"; }
// template <class T> inline void out(vector <T> &vec) { for (auto &it : vec) cout << it << " "; cout << endl; }
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
constexpr int N = 4e5 + 10;
constexpr int M = 25;
int n, m, q;
struct Edge {
    int u, v;
    Edge() {}
    Edge(int u, int v) : u(u), v(v) {}
    bool operator<(const Edge &other) const {
        return u < other.u;
    }
} e[N];
int fa[N], w[N], f[N];
int find(int x) {
    return fa[x] == 0 ? x : fa[x] = find(fa[x]);
}
vector<vector<int>> G;
int pre[N][M], in[N], fin[N], out[N];
void DFS(int u) {
    in[u] = ++*in;
    fin[*in] = u;
    for (auto &v : G[u]) {
        pre[v][0] = u;
        for (int i = 1; i < M; ++i) pre[v][i] = pre[pre[v][i - 1]][i - 1];
        DFS(v);
    }
    out[u] = *in;
}
struct SEG {
    struct node {
        ll v;
        node() {
            v = 1;
        }
        node operator+(const node &other) const {
            node res = node();
            res.v = v * other.v % mod;
            return res;
        }
    } t[N << 2];
    void build(int id, int l, int r) {
        t[id] = node();
        if (l == r) {
            t[id].v = w[fin[l]] % mod;
            return;
        }
        int mid = (l + r) >> 1;
        build(id << 1, l, mid);
        build(id << 1 | 1, mid + 1, r);
        t[id] = t[id << 1] + t[id << 1 | 1];
    }
    void update(int id, int l, int r, int pos, ll v) {
        if (l == r) {
            t[id].v = v % mod;
            return;
        }
        int mid = (l + r) >> 1;
        if (pos <= mid)
            update(id << 1, l, mid, pos, v);
        else
            update(id << 1 | 1, mid + 1, r, pos, v);
        t[id] = t[id << 1] + t[id << 1 | 1];
    }
    ll query(int id, int l, int r, int ql, int qr) {
        if (l >= ql && r <= qr)
            return t[id].v;
        int mid = (l + r) >> 1;
        ll res = 1;
        if (ql <= mid)
            res = res * query(id << 1, l, mid, ql, qr) % mod;
        if (qr > mid)
            res = res * query(id << 1 | 1, mid + 1, r, ql, qr) % mod;
        return res;
    }
} seg;
void run() {
    memset(fa, 0, sizeof fa);
    memset(w, 0, sizeof w);
    *in = 0;
    G.clear();
    G.resize(N);
    for (int i = 1; i <= n; ++i) cin >> w[i], f[i] = i;
    for (int i = n + 1; i <= n + m; ++i) w[i] = 1;
    for (int i = 1, u, v; i <= m; ++i) {
        cin >> u >> v;
        if (u < v)
            swap(u, v);
        e[i] = Edge(u, v);
    }
    sort(e + 1, e + 1 + m);
    for (int i = 1; i <= m; ++i) {
        int u = find(e[i].u), v = find(e[i].v), now = n + i;
        G[now].push_back(u);
        if (u != v)
            G[now].push_back(v);
        f[now] = e[i].u;
        fa[u] = fa[v] = now;
    }
    for (int i = 1; i <= n + m; ++i) {
        sort(G[i].begin(), G[i].end());
        G[i].erase(unique(G[i].begin(), G[i].end()), G[i].end());
    }
    //	for (int i = 1; i <= n + m; ++i) {
    //		cout << i << endl;
    //		for (auto &v : G[i])
    //			cout << v << " ";
    //		cout << endl;
    //	}
    for (int j = 0; j < M; ++j) pre[n + m][j] = n + m;
    DFS(n + m);
    seg.build(1, 1, n + m);
    int op, x, y;
    while (q--) {
        cin >> op >> x >> y;
        if (op == 1) {
            if (x > y)
                cout << "0\n";
            else {
                int anc = x;
                for (int i = M - 1; i >= 0; --i) {
                    if (f[pre[anc][i]] <= y) {
                        anc = pre[anc][i];
                    }
                }
                cout << seg.query(1, 1, n + m, in[anc], out[anc]) << endl;
            }
        } else {
            w[x] = y;
            seg.update(1, 1, n + m, in[x], w[x]);
        }
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
