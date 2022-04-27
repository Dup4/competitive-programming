#include <bits/stdc++.h>
#define debug(...)           \
    {                        \
        printf("#  ");       \
        printf(__VA_ARGS__); \
        puts("");            \
    }
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
inline void pt() {
    cout << endl;
}
template <class T, class... Ts>
void pt(const T &arg, const Ts &...args) {
    cout << arg << " ";
    pt(args...);
}
template <class T>
inline void pt(const T &s) {
    cout << s << "\n";
}
template <class T>
inline void pt(const vector<T> &vec) {
    for (auto &it : vec) cout << it << " ";
    cout << endl;
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
constexpr int N = 2e5 + 10;
constexpr ll INFLL = 0x3f3f3f3f3f3f3f3f;
int n, m, tot, e[N][4];
vector<vector<int>> f, g;
vector<vector<pII>> G;
ll dis[N];
bool used[N];
struct node {
    int u;
    ll w;
    node() {}
    node(int u, ll w) : u(u), w(w) {}
    bool operator<(const node &other) const {
        return w > other.w;
    }
};
void Dijkstra() {
    for (int i = 1; i <= tot; ++i) {
        dis[i] = INFLL;
        used[i] = 0;
    }
    priority_queue<node> pq;
    for (auto &it : g[1]) {
        dis[it] = 0;
        pq.emplace(it, 0);
    }
    while (!pq.empty()) {
        int u = pq.top().u;
        pq.pop();
        if (used[u])
            continue;
        used[u] = 1;
        for (auto &it : G[u]) {
            int v = it.fi, w = it.se;
            if (dis[v] > dis[u] + w) {
                dis[v] = dis[u] + w;
                pq.emplace(v, dis[v]);
            }
        }
    }
    ll res = 1e18;
    for (auto &it : g[n]) chmin(res, dis[it]);
    pt(res);
}
void run() {
    tot = 0;
    f.clear();
    f.resize(n + 10);
    g.clear();
    g.resize(n + 10);
    G.clear();
    G.resize(m * 2 + 1);
    for (int i = 1; i <= m; ++i) {
        for (int j = 0; j < 4; ++j) e[i][j] = rd();
        f[e[i][0]].push_back(e[i][2]);
        f[e[i][1]].push_back(e[i][2]);
    }
    for (int i = 1; i <= n; ++i) {
        sort(f[i].begin(), f[i].end());
        f[i].erase(unique(f[i].begin(), f[i].end()), f[i].end());
        g[i].resize(f[i].size());
        for (auto &it : g[i]) it = ++tot;
        for (int j = 1, sze = f[i].size(); j < sze; ++j) {
            int u = g[i][j], v = g[i][j - 1], w = f[i][j] - f[i][j - 1];
            G[u].emplace_back(v, w);
            G[v].emplace_back(u, w);
        }
    }
    for (int i = 1; i <= m; ++i) {
        int a = e[i][0], b = e[i][1];
        int u = g[a][lower_bound(f[a].begin(), f[a].end(), e[i][2]) - f[a].begin()];
        int v = g[b][lower_bound(f[b].begin(), f[b].end(), e[i][2]) - f[b].begin()];
        G[u].emplace_back(v, e[i][3]);
        G[v].emplace_back(u, e[i][3]);
    }
    Dijkstra();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout << fixed << setprecision(20);
    while (cin >> n >> m) run();
    return 0;
}
