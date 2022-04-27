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

template <class T>
struct LP {
    static const T INF = 0x3f3f3f3f;
    int n, m;
    vector<T> v;
    vector<vector<T>> a;
    LP(const vector<vector<T>> &_a, int _n, int _m) {
        a = _a;
        n = _n;
        m = _m;
        v.resize(m + 1);
    }
    void pivot(int x, int y) {
        int tp = 0;
        for (int i = 0; i <= m; i++)
            if (a[x][i])
                v[++tp] = i;
        for (int i = 0; i <= n; i++) {
            if (i != x && a[i][y]) {
                int k = a[i][y];
                a[i][y] = 0;
                for (int j = 1; j <= tp; j++) a[i][v[j]] -= k * a[x][v[j]];
            }
        }
    }
    T solve() {
        a[n + 1][0] = INF;
        while (1) {
            int x = 0, y = n + 1;
            for (int i = 1; i <= m; i++)
                if (a[0][i] > 0) {
                    x = i;
                    break;
                }
            if (!x)
                return -a[0][0];
            for (int i = 1; i <= n; i++)
                if (a[i][x] > 0 && a[i][0] < a[y][0])
                    y = i;
            pivot(y, x);
        }
    }
};

void run() {
    ll A, B;
    rd(A, B);
    vector<vector<int>> a(5, vector<int>(5, 0));
    a[1][0] = A;
    a[2][0] = B;
    a[0][1] = 1, a[0][2] = 1;
    a[1][1] = 2, a[1][2] = 4;
    a[2][1] = 3, a[2][2] = 1;
    LP<int> lp(a, 2, 2);
    pt(lp.solve());
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout << fixed << setprecision(20);
    int _T = nextInt();
    while (_T--) run();
    //	while (cin >> n) run();
    //    for (int kase = 1; kase <= _T; ++kase) {
    //        cout << "Case #" << kase << ":\n";
    //        run();
    //    }
    return 0;
}
