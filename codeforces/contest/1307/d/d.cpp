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
constexpr int N = 4e5 + 10, INF = 0x3f3f3f3f;
int n, m, K, res, a[N];
vector<pII> vec;

struct Graph {
    struct E {
        int to, nx;
    } e[N << 1];
    int h[N], cnt;
    void init(int n) {
        for (int i = 1; i <= n; ++i) h[i] = -1;
        cnt = -1;
    }
    void addedge(int u, int v) {
        e[++cnt] = {v, h[u]};
        h[u] = cnt;
    }
} G;

int dis[2][N];
struct Dijkstra {
    struct node {
        int u, w;
        node(int u = 0, int w = 0) : u(u), w(w) {}
        bool operator<(const node &other) const {
            return w > other.w;
        }
    };
    bool used[N];
    void gao(int rt, int *dis) {
        for (int i = 1; i <= n; ++i) {
            dis[i] = INF;
            used[i] = 0;
        }
        dis[rt] = 0;
        priority_queue<node> pq;
        pq.push(node(rt, 0));
        while (!pq.empty()) {
            int u = pq.top().u;
            pq.pop();
            if (used[u])
                continue;
            used[u] = 1;
            for (int i = G.h[u]; ~i; i = G.e[i].nx) {
                int v = G.e[i].to, w = 1;
                if (dis[v] > dis[u] + w) {
                    dis[v] = dis[u] + w;
                    pq.push(node(v, dis[v]));
                }
            }
        }
    }
} dij;

void gao(int u, int limit) {
    auto pos = upper_bound(vec.begin(), vec.end(), pII(limit, 0));
    if (pos == vec.end())
        --pos;
    for (int j = 0; j < 10; ++j) {
        if (pos->se != u) {
            int v = pos->se;
            int Min = 1 + min(dis[0][u] + dis[1][v], dis[0][v] + dis[1][u]);
            chmax(res, Min);
        }
        if (pos == vec.begin())
            break;
        --pos;
    }
}

void run() {
    G.init(n + 1);
    for (int i = 1; i <= K; ++i) rd(a[i]);
    for (int i = 1, u, v; i <= m; ++i) {
        rd(u, v);
        G.addedge(u, v);
        G.addedge(v, u);
    }
    dij.gao(1, dis[0]);
    dij.gao(n, dis[1]);
    res = -1;
    vec.clear();
    for (int i = 1; i <= K; ++i) vec.push_back(pII(dis[1][a[i]], a[i]));
    sort(vec.begin(), vec.end());
    for (int i = 1; i <= K; ++i) {
        gao(a[i], dis[0][n] - 1 - dis[0][a[i]]);
    }
    vec.clear();
    for (int i = 1; i <= K; ++i) vec.push_back(pII(dis[0][a[i]], a[i]));
    sort(vec.begin(), vec.end());
    for (int i = 1; i <= K; ++i) gao(a[i], dis[0][n] - 1 - dis[1][a[i]]);
    if (res == -1)
        res = dis[0][n];
    chmin(res, dis[0][n]);
    pt(res);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout << fixed << setprecision(20);
    while (cin >> n >> m >> K) run();
    //	while (cin >> n) run();
    //    for (int kase = 1; kase <= _T; ++kase) {
    //        cout << "Case #" << kase << ":\n";
    //        run();
    //    }
    return 0;
}
