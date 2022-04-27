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
constexpr int N = 1e2 + 10;
int n, c[N], f[1 << 13][14][25];

vector<int> vec[1 << 13];

void run() {
    for (int i = 1; i <= n; ++i) rd(c[i]);
    sort(c + 1, c + 1 + n);
    reverse(c + 1, c + 1 + n);
    if (c[1] != n)
        return pt("NO");
    if (n == 1)
        return pt("YES");
    int lef = 0;
    for (int i = 1; i <= n; ++i) {
        if (c[i] == 1)
            ++lef;
        if (c[i] == 2)
            return pt("NO");
    }
    if (lef <= n / 2)
        return pt("NO");
    memset(f, 0, sizeof f);
    int _n = 0;
    for (int i = 1; i <= n; ++i) {
        if (c[i] == 1) {
            _n = i - 1;
            break;
        }
    }
    n = _n;
    for (int mask = 0; mask < (1 << n); ++mask) {
        for (int j = 0; j < n; ++j)
            if (((mask >> j) & 1) && __builtin_popcount(mask) <= c[j + 1]) {
                vec[mask].push_back(j);
            }
    }
    //	for (int i = 0; i < n; ++i) {
    //		for (int mask = 1 << i; mask < (1 << n); mask = (mask + 1) | (1 << i)) {
    //			vec[mask].push_back(i);
    //		}
    //	}
    for (int i = 0; i < n; ++i)
        for (int j = 1; j <= min(c[i + 1], lef + 1); ++j) f[1 << i][i][j] = 1;
    for (int S = 0; S < (1 << n); ++S) {
        for (auto &u : vec[S]) {
            for (int T = (S - 1) & S; T; T = (T - 1) & S) {
                for (auto &v : vec[T])
                    if (((S - T) >> u) % 2 == 1 && c[v + 1] + 1 < c[u + 1] && f[T][v][c[v + 1]]) {
                        for (int j = 1; j + c[v + 1] <= c[u + 1]; ++j) f[S][u][j + c[v + 1]] |= f[S - T][u][j];
                    }
            }
        }
    }
    if (f[(1 << n) - 1][0][c[1]])
        pt("YES");
    else
        pt("NO");
    //	for (int i = 0; i < n; ++i) {
    //		if (f[(1 << n) - 1][i][c[i]])
    //			return pt("YES");
    //	}
    //	pt("NO");
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout << fixed << setprecision(20);
    while (cin >> n) run();
    //    for (int kase = 1; kase <= _T; ++kase) {
    //        cout << "Case #" << kase << ":\n";
    //        run();
    //    }
    return 0;
}
