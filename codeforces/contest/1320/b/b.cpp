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
constexpr int N = 4e5 + 10;
constexpr ll INF = 0x3f3f3f3f;
int n, m, K, p[N];
vector<vector<int>> G[2];

pLL dis[2][N];
struct Dijkstra {
    struct node {
        int u, w;
        node(int u = 0, int w = 0) : u(u), w(w) {}
        bool operator<(const node &other) const {
            return w > other.w;
        }
    };
    bool used[N];
    void gao(int rt, pLL *dis, vector<vector<int>> &G) {
        for (int i = 1; i <= n; ++i) {
            dis[i] = pII(INF, 0);
            used[i] = 0;
        }
        dis[rt] = pII(0, 1);
        priority_queue<node> pq;
        pq.push(node(rt, 0));
        while (!pq.empty()) {
            int u = pq.top().u;
            pq.pop();
            if (used[u])
                continue;
            used[u] = 1;
            for (auto &v : G[u]) {
                int w = 1;
                if (dis[v].fi > dis[u].fi + w) {
                    dis[v] = pII(dis[u].fi + w, dis[u].se);
                    pq.push(node(v, dis[v].fi));
                } else if (dis[v].fi == dis[u].fi + w) {
                    dis[v].se += dis[u].se;
                }
            }
        }
    }
} dij;

void run() {
    //	G[0].clear(); G[0].resize(n + 1);
    G[1].clear();
    G[1].resize(n + 1);
    for (int i = 1, u, v; i <= m; ++i) {
        rd(u, v);
        //	G[0][u].push_back(v);
        G[1][v].push_back(u);
    }
    rd(K);
    for (int i = 1; i <= K; ++i) rd(p[i]);
    //	dij.gao(p[1], dis[0], G[0]);
    dij.gao(p[K], dis[1], G[1]);
    int res[2] = {0, 0};
    for (int i = 1; i < K; ++i) {
        if (dis[1][p[i]].fi < dis[1][p[i + 1]].fi + 1)
            ++res[0];
    }
    for (int i = 1; i < K; ++i) {
        if (dis[1][p[i]].fi < dis[1][p[i + 1]].fi + 1)
            ++res[1];
        else if (dis[1][p[i]].se != dis[1][p[i + 1]].se)
            ++res[1];
    }
    pt(res[0], res[1]);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout << fixed << setprecision(20);
    while (cin >> n >> m) run();
    //    for (int kase = 1; kase <= _T; ++kase) {
    //        cout << "Case #" << kase << ":\n";
    //        run();
    //    }
    return 0;
}
