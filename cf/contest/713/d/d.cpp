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
constexpr int N = 1e3 + 10, INF = 0x3f3f3f3f;
int n, m, q, a[N][N], f[N][N];

struct RMQ {
    int f[N][N][11][11];
    int mm[N];
    void init(int n, int m, int a[][N]) {
        mm[0] = -1;
        for (int i = 1; i < N; ++i) {
            mm[i] = ((i & (i - 1)) == 0) ? mm[i - 1] + 1 : mm[i - 1];
        }
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                f[i][j][0][0] = a[i][j];
            }
        }
        for (int ii = 0; ii <= mm[n]; ++ii) {
            for (int jj = 0; jj <= mm[m]; ++jj) {
                if (ii + jj) {
                    for (int i = 1; i + (1 << ii) - 1 <= n; ++i) {
                        for (int j = 1; j + (1 << jj) - 1 <= m; ++j) {
                            if (ii) {
                                f[i][j][ii][jj] = max(f[i][j][ii - 1][jj], f[i + (1 << (ii - 1))][j][ii - 1][jj]);
                            } else {
                                f[i][j][ii][jj] = max(f[i][j][ii][jj - 1], f[i][j + (1 << (jj - 1))][ii][jj - 1]);
                            }
                        }
                    }
                }
            }
        }
    }
    void Max(int &x, int y) {
        if (x < y)
            x = y;
    }
    void Min(int &x, int y) {
        if (x > y)
            x = y;
    }
    int query(int x1, int y1, int x2, int y2) {
        int k1 = mm[x2 - x1 + 1];
        int k2 = mm[y2 - y1 + 1];
        x2 = x2 - (1 << k1) + 1;
        y2 = y2 - (1 << k2) + 1;
        pII res = pII(-INF, INF);
        Max(res.fi, f[x1][y1][k1][k2]);
        Max(res.fi, f[x1][y2][k1][k2]);
        Max(res.fi, f[x2][y1][k1][k2]);
        Max(res.fi, f[x2][y2][k1][k2]);
        return res.fi;
    }
} rmq;

void run() {
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            rd(a[i][j]);
            if (!a[i][j])
                f[i][j] = 0;
            else
                f[i][j] = min({f[i - 1][j - 1], f[i - 1][j], f[i][j - 1]}) + 1;
        }
    }
    rmq.init(n, m, f);
    rd(q);
    while (q--) {
        int x[2], y[2];
        rd(x[0], y[0], x[1], y[1]);
        int l = 0, r = min(x[1] - x[0], y[1] - y[0]) + 1, res = 0;
        while (r - l >= 0) {
            int mid = (l + r) >> 1;
            if (rmq.query(x[0] + mid - 1, y[0] + mid - 1, x[1], y[1]) >= mid) {
                res = mid;
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
        pt(res);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout << fixed << setprecision(20);
    while (cin >> n >> m) run();
    //	while (cin >> n) run();
    //    for (int kase = 1; kase <= _T; ++kase) {
    //        cout << "Case #" << kase << ":\n";
    //        run();
    //    }
    return 0;
}
