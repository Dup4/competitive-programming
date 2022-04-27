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
constexpr int N = 5e5 + 10;
int n, q, e[N][2], P[N], fa[N], g[N], f[N], id[N];
vector<vector<int>> G, h;

void dfs(int u) {
    int now = 0;
    for (auto &v : G[u])
        if (v != fa[u]) {
            fa[v] = u;
            id[v] = now;
            ++now;
            dfs(v);
        }
}

void run() {
    G.clear();
    G.resize(n + 1);
    h.clear();
    h.resize(n + 1);
    for (int i = 1, u, v; i < n; ++i) {
        cin >> u >> v;
        G[u].push_back(v);
        h[u].push_back(0);
        G[v].push_back(u);
        h[v].push_back(0);
        e[i][0] = u;
        e[i][1] = v;
    }
    fa[1] = 0;
    dfs(1);
    for (int i = 1; i <= n; ++i) {
        g[i] = 0;
        f[i] = 1;
    }
    for (int i = 1; i < n; ++i) {
        if (fa[e[i][0]] == e[i][1])
            swap(e[i][0], e[i][1]);
    }
    for (int i = 1; i <= q; ++i) cin >> P[i];
    for (int i = q, p, u, v; i >= 1; --i) {
        p = P[i];
        u = e[p][0], v = e[p][1];
        f[u] -= h[u][id[v]];
        h[u][id[v]] = f[v];
        f[u] += h[u][id[v]];
        g[v] = g[u] + f[u] - f[v];
    }
    for (int i = 1; i <= n; ++i) cout << f[i] + g[i] << " \n"[i == n];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout << fixed << setprecision(20);
    while (cin >> n >> q) run();
    return 0;
}
