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
constexpr int N = 5e2 + 10, M = 3e5 + 10, INF = 0x3f3f3f3f;
int n, m, q, ans[M], a[N][N];
char s[N][N];
struct E {
    pII a, b;
};
inline int id(int x, int y) {
    return (x - 1) * m + y;
}

struct RMQ {
    short f[N][N][9][9], g[N][N][9][9];
    int mm[N];
    void init(int n, int m, int a[][N]) {
        mm[0] = -1;
        for (int i = 1; i < N; ++i) {
            mm[i] = ((i & (i - 1)) == 0) ? mm[i - 1] + 1 : mm[i - 1];
        }
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                f[i][j][0][0] = a[i][j];
                g[i][j][0][0] = a[i][j];
            }
        }
        for (int ii = 0; ii <= mm[n]; ++ii) {
            for (int jj = 0; jj <= mm[m]; ++jj) {
                if (ii + jj) {
                    for (int i = 1; i + (1 << ii) - 1 <= n; ++i) {
                        for (int j = 1; j + (1 << jj) - 1 <= m; ++j) {
                            if (ii) {
                                f[i][j][ii][jj] = max(f[i][j][ii - 1][jj], f[i + (1 << (ii - 1))][j][ii - 1][jj]);
                                g[i][j][ii][jj] = min(g[i][j][ii - 1][jj], g[i + (1 << (ii - 1))][j][ii - 1][jj]);
                            } else {
                                f[i][j][ii][jj] = max(f[i][j][ii][jj - 1], f[i][j + (1 << (jj - 1))][ii][jj - 1]);
                                g[i][j][ii][jj] = min(g[i][j][ii][jj - 1], g[i][j + (1 << (jj - 1))][ii][jj - 1]);
                            }
                        }
                    }
                }
            }
        }
    }
    void Max(int &x, short y) {
        if (x < y)
            x = y;
    }
    void Min(int &x, short y) {
        if (x > y)
            x = y;
    }
    pII query(int x1, int y1, int x2, int y2) {
        int k1 = mm[x2 - x1 + 1];
        int k2 = mm[y2 - y1 + 1];
        x2 = x2 - (1 << k1) + 1;
        y2 = y2 - (1 << k2) + 1;
        pII res = pII(-INF, INF);
        Max(res.fi, f[x1][y1][k1][k2]);
        Max(res.fi, f[x1][y2][k1][k2]);
        Max(res.fi, f[x2][y1][k1][k2]);
        Max(res.fi, f[x2][y2][k1][k2]);
        Min(res.se, g[x1][y1][k1][k2]);
        Min(res.se, g[x1][y2][k1][k2]);
        Min(res.se, g[x2][y1][k1][k2]);
        Min(res.se, g[x2][y2][k1][k2]);
        return res;
    }
} rmq;

bool check(int x1, int y1, int x2, int y2, int ch) {
    pII t = rmq.query(x1, y1, x2, y2);
    return t.fi == ch && t.se == ch;
}

bool ok(int x1, int y1, int x2, int y2) {
    if (x1 < 1 || y1 < 1 || x1 == x2 || y1 == y2)
        return 0;
    int midx = (x1 + x2) >> 1;
    int midy = (y1 + y2) >> 1;
    return check(x1, y1, midx, midy, 1) && check(x1, midy + 1, midx, y2, 2) && check(midx + 1, y1, x2, midy, 3) &&
           check(midx + 1, midy + 1, x2, y2, 4);
}

struct BIT {
    int a[N][N], pos[N][N];
    int T;
    void init() {
        memset(a, 0, sizeof a);
        T = 0;
    }
    void update(int x, int y, int v) {
        for (int i = x; i < N; i += i & -i) {
            for (int j = y; j < N; j += j & -j) {
                if (pos[i][j] == T)
                    chmax(a[i][j], v);
                else
                    a[i][j] = v;
            }
        }
    }
    int query(int x, int y) {
        int res = 0;
        for (int i = x; i; i -= i & -i) {
            for (int j = y; j; j -= j & -j) {
                chmax(res, a[i][j]);
            }
        }
        return res;
    }
} bit;

void run() {
    vector<vector<pair<pII, int>>> add(n * m + 5), qvec(n * m + 5);
    for (int i = 1; i <= n; ++i) cin >> (s[i] + 1);
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (s[i][j] == 'R')
                a[i][j] = 1;
            else if (s[i][j] == 'G')
                a[i][j] = 2;
            else if (s[i][j] == 'Y')
                a[i][j] = 3;
            else if (s[i][j] == 'B')
                a[i][j] = 4;
        }
    }
    rmq.init(n, m, a);
    for (int i = 1, x[2], y[2]; i <= q; ++i) {
        cin >> x[0] >> y[0] >> x[1] >> y[1];
        qvec[id(x[0], y[0])].emplace_back(pII(x[1], y[1]), i);
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            int k;
            for (k = i - 1; k >= 1; --k) {
                if (s[k][j] != s[i][j])
                    break;
            }
            ++k;
            int len = i - k + 1;
            int x = i - 2 * len + 1, y = j - 2 * len + 1;
            if (ok(x, y, i, j)) {
                add[id(x, y)].emplace_back(pII(i, j), (j - y + 1) * (i - x + 1));
            }
        }
    }
    for (int i = n; i >= 1; --i) {
        bit.init();
        for (int j = m; j >= 1; --j) {
            for (auto &it : add[id(i, j)]) {
                bit.update(it.fi.fi, it.fi.se, it.se);
                if (i > 1)
                    add[id(i - 1, j)].push_back(it);
            }
            for (auto &it : qvec[id(i, j)]) {
                ans[it.se] = bit.query(it.fi.fi, it.fi.se);
            }
        }
    }
    for (int i = 1; i <= q; ++i) pt(ans[i]);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout << fixed << setprecision(20);
    while (cin >> n >> m >> q) run();
    return 0;
}
