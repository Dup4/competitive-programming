#include <bits/stdc++.h>
using namespace std;
#define debug(...)           \
    {                        \
        printf("#  ");       \
        printf(__VA_ARGS__); \
        puts("");            \
    }
#define ll long long
#define pii pair<int, int>
#define fi first
#define se second
#define endl "\n"
constexpr int N = 1e5 + 10;
constexpr int mod = 1e9 + 7;
constexpr int INT = 0x3f3f3f3f;
template <class T1, class T2>
inline void chadd(T1 &x, T2 y) {
    x += y;
    if (x >= mod)
        x -= mod;
    else if (x < mod)
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
inline void out(T s) {
    cout << s << "\n";
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
int n, m, s, t;
vector<vector<pii>> G[2];
ll dis[2][N], res[N];
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
void Dijkstra(int s, ll *dis, vector<vector<pii>> &G) {
    memset(used, 0, sizeof used);
    dis[s] = 0;
    priority_queue<node> pq;
    pq.push(node(s, 0));
    while (!pq.empty()) {
        int u = pq.top().u;
        pq.pop();
        if (used[u])
            continue;
        used[u] = 1;
        for (auto it : G[u]) {
            int v = it.fi, w = it.se;
            if (dis[v] > dis[u] + w) {
                dis[v] = dis[u] + w;
                pq.push(node(v, dis[v]));
            }
        }
    }
}
void run() {
    G[0].clear();
    G[0].resize(n + 1);
    G[1].clear();
    G[1].resize(n + 1);
    for (int i = 1, u, v, a, b; i <= m; ++i) {
        cin >> u >> v >> a >> b;
        G[0][u].push_back(pii(v, a));
        G[0][v].push_back(pii(u, a));
        G[1][u].push_back(pii(v, b));
        G[1][v].push_back(pii(u, b));
    }
    cin >> s >> t;
    memset(dis, 0x3f, sizeof dis);
    Dijkstra(s, dis[0], G[0]);
    Dijkstra(t, dis[1], G[1]);
    ll Min = 1e18;
    for (int i = n; i >= 1; --i) {
        Min = min(dis[0][i] + dis[1][i], Min);
        res[i] = Min;
    }
    for (int i = 1; i <= n; ++i) cout << res[i] << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout << fixed << setprecision(20);
    while (cin >> n >> m) run();
    return 0;
}
