#include <bits/stdc++.h>
using namespace std;
#define endl "\n"
#define fi first
#define se second
#define SZ(x) ((int)(x).size())
#define mkp make_pair
#define all(x) (x).begin(), (x).end()
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
constexpr int N = 1e3 + 10;
int n, m, a[N][N], b[N][N], c[N];

int query(int a[N][N], int sx, int sy, int ex, int ey) {
    return a[ex][ey] - a[sx - 1][ey] - a[ex][sy - 1] + a[sx - 1][sy - 1];
}

void run() {
    rd(n, m);
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j < m; ++j) {
            rd(a[i][j]);
            a[i][j] += a[i][j - 1] + a[i - 1][j] - a[i - 1][j - 1];
        }
    }
    for (int i = 1; i < n; ++i) {
        for (int j = 1; j <= m; ++j) {
            rd(b[i][j]);
            b[i][j] += b[i][j - 1] + b[i - 1][j] - b[i - 1][j - 1];
        }
    }
    ll res = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = i + 1; j <= n; ++j) {
            int len = j - i;
        }
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            for (int k = 1; k <= min(n - i, m - j); ++k) {
                int _i = i + k;
                int _j = j + k;
                if (query(a, i, j, i, _j - 1) == k && query(a, _i, j, _i, _j - 1) == k &&
                        query(b, i, _j, _i - 1, _j) == k && query(b, i, j, _i - 1, j) == k) {
                    ++res;
                    //	dbg(i, j, _i, _j);
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
    int _T = 1;
    // nextInt();
    while (_T--) run();
    //    for (int kase = 1; kase <= _T; ++kase) {
    //        cout << "Case #" << kase << ": ";
    //        run();
    //    }
    //	while (cin >> n) run();
    //	run();
    return 0;
}
