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
constexpr int N = 1e3 + 5;
int n, a[N], g[N][130], pre[10];
short f[N][257][130];
void run() {
    memset(pre, 0, sizeof pre);
    memset(f, -1, sizeof f);
    for (int i = 1; i <= n; ++i) {
        rd(a[i]);
        g[i][1] = i;
        for (int j = 1; j <= 125; ++j) {
            g[i][j + 1] = g[pre[a[i]]][j];
        }
        pre[a[i]] = i;
    }
    memset(f[0][0], 0, sizeof f[0][0]);
    for (int mask = 0; mask < (1 << 8); ++mask)
        for (int i = 0; i < 2; ++i) f[0][mask][i] = 0;
    for (int i = 1; i <= n; ++i) {
        int num = a[i] - 1;
        for (int mask = 0; mask < (1 << 8); ++mask) {
            for (int j = 1; j <= 126; ++j) {
                chmax(f[i][mask][j], f[i - 1][mask][j]);
            }
        }
        for (int mask = 0; mask < (1 << 8); ++mask)
            if (((mask >> num) & 1) == 0) {
                for (int j = 1; j <= 126; ++j) {
                    if (g[i][j]) {
                        if (f[g[i][j] - 1][mask][j] != -1)
                            chmax(f[i][mask | (1 << num)][j], f[g[i][j] - 1][mask][j] + j);
                        if (f[g[i][j] - 1][mask][j + 1] != -1)
                            chmax(f[i][mask | (1 << num)][j + 1], f[g[i][j] - 1][mask][j + 1] + j);
                    }
                }
            }
    }
    int res = 0;
    for (int i = 1; i <= 126; ++i) {
        chmax(res, f[n][(1 << 8) - 1][i]);
    }
    pt(res);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout << fixed << setprecision(20);
    while (cin >> n) run();
    //	while (cin >> n) run();
    //    for (int kase = 1; kase <= _T; ++kase) {
    //        cout << "Case #" << kase << ":\n";
    //        run();
    //    }
    return 0;
}
