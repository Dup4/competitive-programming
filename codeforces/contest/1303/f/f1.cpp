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
constexpr int N = 3e2 + 10, M = 2e6 + 10;
int n, m, q, res[M], a[N][N];

struct UFS {
    int fa[N * N], rk[N * N];
    void init(int n) {
        memset(fa, 0, sizeof(fa[0]) * (n + 5));
        memset(rk, 0, sizeof(rk[0]) * (n + 5));
    }
    int find(int x) {
        return fa[x] == 0 ? x : fa[x] = find(fa[x]);
    }
    bool merge(int x, int y) {
        int fx = find(x), fy = find(y);
        if (fx != fy) {
            if (rk[fx] > rk[fy])
                swap(fx, fy);
            fa[fx] = fy;
            if (rk[fx] == rk[fy])
                ++rk[fy];
            return true;
        }
        return false;
    }
} ufs;

struct E {
    int x, y, id;
};
vector<vector<E>> add, del;

int Move[][2] = {-1, 0, 1, 0, 0, 1, 0, -1};
inline int getId(int x, int y) {
    return (x - 1) * m + y;
}
inline bool ok(int x, int y) {
    return x >= 1 && x <= n && y >= 1 && y <= m;
}

void gao(const vector<E> &vec, int opt) {
    for (auto &it : vec) {
        int x = it.x, y = it.y, id = it.id;
        int cur = 1;
        a[x][y] = 1;
        for (int i = 0; i < 4; ++i) {
            int nx = x + Move[i][0];
            int ny = y + Move[i][1];
            if (a[nx][ny] == 1 && ok(nx, ny)) {
                cur -= ufs.merge(getId(x, y), getId(nx, ny));
            }
        }
        res[id] += cur * opt;
    }
    for (auto &it : vec) {
        int x = it.x, y = it.y;
        a[x][y] = 0;
        ufs.fa[getId(x, y)] = ufs.fa[getId(x, y)] = 0;
    }
}

void run() {
    memset(a, 0, sizeof a);
    memset(res, 0, sizeof res);
    res[0] = 1;
    add.resize(M);
    del.resize(M);
    int maxCol = 0;
    for (int i = 1, x, y, c; i <= q; ++i) {
        rd(x, y, c);
        if (a[x][y] == c)
            continue;
        chmax(maxCol, c);
        add[c].push_back({x, y, i});
        del[a[x][y]].push_back({x, y, i});
        a[x][y] = c;
    }
    for (int x = 1; x <= n; ++x)
        for (int y = 1; y <= m; ++y) del[a[x][y]].push_back({x, y, q + 1});
    memset(a, 0, sizeof a);
    for (int i = 0; i <= maxCol; ++i)
        if (!del[i].empty())
            reverse(del[i].begin(), del[i].end());
    for (int i = 0; i <= maxCol; ++i)
        if (!add[i].empty())
            gao(add[i], 1);
    for (int i = 0; i <= maxCol; ++i)
        if (!del[i].empty())
            gao(del[i], -1);
    int cur = 1;
    for (int i = 1; i <= q; ++i) {
        cur += res[i];
        pt(cur);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout << fixed << setprecision(20);
    //	int _T = nextInt();
    //	while (_T--) run();
    while (cin >> n >> m >> q) run();
    return 0;
}
