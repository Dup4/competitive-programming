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
constexpr int mod = 998244353;
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
constexpr int N = 1e6 + 10;
ll n, inv2;
vector<int> g;

namespace DIVCNT {
struct point {
    ll x, y;
    point(ll _x = 0, ll _y = 0) {
        x = _x;
        y = _y;
    }
    point operator+(const point &t) const {
        return point(x + t.x, y + t.y);
    }
} st[N], L, R, M;
ll n;
inline bool inR(ll x, ll y) {
    return x * y <= n;
}
inline double slope(ll x) {
    return (double)n / x / x;
}
inline ll gao(ll _n) {
    n = _n;
    ll ret = 0;
    int t = 0, rt = cbrt(n);
    st[++t] = point(1, 0);
    st[++t] = point(1, 1);
    ll m = sqrt(n), x = n / m, y = m + 1;
    while (1) {
        for (L = st[t--]; !inR(x + L.x, y - L.y); x += L.x, y -= L.y)
            ret += x * L.y % mod + (L.y + 1) * (L.x - 1) % mod * inv2 % mod;
        if (y <= rt)
            break;
        for (R = st[t]; inR(x + R.x, y - R.y); R = st[--t]) L = R;
        while (1) {
            M = L + R;
            if (!inR(x + M.x, y - M.y))
                st[++t] = (R = M);
            else {
                if (slope(x + M.x) <= (double)R.y / R.x)
                    break;
                L = M;
            }
        }
    }
    for (int i = 1; i < y; i++) chadd(ret, n / i);
    return (ret * 2 % mod - 1ll * m * m % mod + mod) % mod;
}
};  // namespace DIVCNT

void run() {
    rd(n);
    ll res = DIVCNT::gao(n);
    for (int i = 1;; ++i) {
        if ((1ll << i) > n)
            break;
        ll g = ((1ll << i) - (1ll << (i - 1)) + mod) % mod;
        chadd(res, g * DIVCNT::gao(n / (1ll << i)) % mod);
    }
    pt(res);
}

int main() {
    inv2 = (mod + 1) / 2;
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout << fixed << setprecision(20);
    // pt(f(4));
    run();
    //    for (int kase = 1; kase <= _T; ++kase) {
    //        cout << "Case #" << kase << ":\n";
    //        run();
    //    }
    return 0;
}
