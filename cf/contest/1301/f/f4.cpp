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
constexpr int N = 1e3 + 10, M = 1e6 + 100, INF = 0x3f3f3f3f;
int n, m, K, q, a[N][N];
int Move[][2] = {
        -1,
        0,
        1,
        0,
        0,
        -1,
        0,
        1,
};

vector<vector<pII>> G;

inline int id(int x, int y) {
    return (x - 1) * m + y;
}

inline bool ok(int x, int y) {
    if (x < 1 || x > n || y < 1 || y > m)
        return false;
    return true;
}

short dis[41][M];
bool done[M];
void bfs(int col) {
    for (int i = 1; i <= n * m + K; ++i) dis[col][i] = 1000, done[i] = 0;
    memset(done, 0, sizeof done);
    deque<int> deq;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (a[i][j] == col) {
                deq.push_back(id(i, j));
                dis[col][id(i, j)] = 0;
                done[id(i, j)] = 1;
            }
        }
    }
    while (!deq.empty()) {
        int u = deq.front();
        deq.pop_front();
        for (auto &it : G[u]) {
            int v = it.fi, w = it.se;
            if (done[v] == 0) {
                dis[col][v] = dis[col][u] + w;
                done[v] = 1;
                if (w)
                    deq.push_back(v);
                else
                    deq.push_front(v);
            }
        }
        if (u <= n * m) {
            int x = u / m + 1, y = u % m;
            if (!y)
                y = m, --x;
            for (int i = 0; i < 4; ++i) {
                int nx = x + Move[i][0];
                int ny = y + Move[i][1];
                if (ok(nx, ny) && done[id(nx, ny)] == 0) {
                    done[id(nx, ny)] = 1;
                    dis[col][id(nx, ny)] = dis[col][u] + 1;
                    deq.push_back(id(nx, ny));
                }
            }
        }
    }
}

int gao(int x[2], int y[2]) {
    int res = abs(x[0] - x[1]) + abs(y[0] - y[1]);
    int u = id(x[0], y[0]), v = id(x[1], y[1]);
    for (int i = 1; i <= K; ++i) {
        chmin(res, 1 + dis[i][u] + dis[i][v]);
    }
    return res;
}

void run() {
    G.clear();
    G.resize(n * m + K + 5);
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            cin >> a[i][j];
            int u = id(i, j);
            G[u].emplace_back(n * m + a[i][j], 0);
            G[n * m + a[i][j]].emplace_back(u, 1);
        }
    }
    for (int i = 1; i <= K; ++i) bfs(i);
    cin >> q;
    for (int i = 1, x[2], y[2]; i <= q; ++i) {
        cin >> x[0] >> y[0] >> x[1] >> y[1];
        pt(gao(x, y));
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout << fixed << setprecision(20);
    while (cin >> n >> m >> K) run();
    return 0;
}
