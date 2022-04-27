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
constexpr int N = 1e5 + 10;
constexpr ll INF = 1e18;
int n, p, K;
ll f[N][(1 << 7) + 5], g[2][(1 << 7) + 5];

struct E {
    int a, s[8];
    bool operator<(const E &other) const {
        return a > other.a;
    }
} e[N];

void run() {
    for (int i = 1; i <= n; ++i) rd(e[i].a);
    for (int i = 1; i <= n; ++i)
        for (int j = 0; j < p; ++j) rd(e[i].s[j]);
    sort(e + 1, e + 1 + n);
    memset(f, -0x3f, sizeof f);
    f[n + 1][0] = 0;
    for (int i = n; i >= 1; --i) {
        for (int j = 0; j < 1 << p; ++j) {
            chmax(f[i][j], f[i + 1][j]);
            for (int k = 0; k < p; ++k) {
                if (((j >> k) & 1) == 0) {
                    chmax(f[i][j | (1 << k)], f[i][j] + e[i].s[k]);
                }
            }
        }
    }
    memset(g, -0x3f, sizeof g);
    g[0][0] = 0;
    ll res = 0;
    for (int i = 1; i <= n; ++i) {
        int id = i & 1;
        memset(g[id], -0x3f, sizeof g[id]);
        for (int j = 0; j < 1 << p; ++j) {
            chmax(g[id][j], g[id ^ 1][j] + e[i].a);
            for (int k = 0; k < p; ++k) {
                if (((j >> k) & 1) == 0) {
                    chmax(g[id][j | (1 << k)], g[id ^ 1][j] + e[i].s[k]);
                }
            }
        }
        if (i - K >= 0 && i - K <= p) {
            for (int j = 0; j < 1 << p; ++j) {
                if (__builtin_popcount(j) == i - K) {
                    chmax(res, g[id][j] + f[i + 1][((1 << p) - 1) ^ j]);
                    // dbg(i, j, ((1 << p) - 1) ^ j, res, g[id][j], f[i + 1][((1 << p) - 1) ^ j]);
                }
            }
        }
    }
    pt(res);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout << fixed << setprecision(20);
    while (cin >> n >> p >> K) run();
    //	while (cin >> n) run();
    //    for (int kase = 1; kase <= _T; ++kase) {
    //        cout << "Case #" << kase << ":\n";
    //        run();
    //    }
    return 0;
}
