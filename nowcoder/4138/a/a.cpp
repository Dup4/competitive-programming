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
template <class T1, class T2>
T1 gcd(T1 a, T2 b) {
    return b ? gcd(b, a % b) : a;
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
int n, a[N], b[N], f[N], g[N], sf[N], sg[N];

struct BIT {
    int a[N];
    void init() {
        memset(a, 0, sizeof a);
    }
    void update(int x, int v) {
        for (; x < N; x += x & -x) chadd(a[x], v);
    }
    int query(int x) {
        int res = 0;
        for (; x > 0; x -= x & -x) chadd(res, a[x]);
        return res;
    }
    int query(int l, int r) {
        if (l > r)
            return 0;
        return (query(r) - query(l - 1) + mod) % mod;
    }
} bit[4];

void run() {
    for (int i = 1; i <= n; ++i) cin >> a[i], b[a[i]] = i;
    bit[0].init();
    bit[1].init();
    for (int i = 1; i <= n; ++i) {
        bit[0].update(i, f[i]);
        bit[1].update(i, g[i]);
    }
    int res = 0;
    for (int i = 1; i <= n; ++i) {
        bit[0].update(b[i], mod - f[b[i]]);
        bit[1].update(b[i], mod - g[b[i]]);
        bit[2].update(b[i], f[b[i]]);
        bit[3].update(b[i], g[b[i]]);
        chadd(res, mod - 1ll * f[n - 1] * g[b[i]] % mod * bit[2].query(1, b[i] - 1) % mod);
        chadd(res, mod - 1ll * f[n - 1] * f[b[i]] % mod * bit[3].query(b[i] + 1, n) % mod);
        //	chadd(res, mod - 1ll * f[n - 1] * g[b[i]] % mod * sf[b[i] - 1] % mod);
        //	chadd(res, mod - 1ll * f[n - 1] * f[b[i]] % mod * (sg[n] - sg[b[i]] + mod) % mod);
        pt(res);
        chadd(res, 1ll * f[n - 1] * g[b[i]] % mod * bit[0].query(1, b[i] - 1) % mod);
        chadd(res, 1ll * f[n - 1] * f[b[i]] % mod * bit[1].query(b[i] + 1, n) % mod);
    }
}

int main() {
    int inv2 = (mod + 1) / 2;
    f[0] = 1;
    g[0] = 1;
    sf[0] = 0;
    sg[0] = 0;
    for (int i = 1; i < N; ++i) {
        f[i] = 1ll * f[i - 1] * 2 % mod;
        sf[i] = sf[i - 1];
        chadd(sf[i], f[i]);
        g[i] = 1ll * g[i - 1] * inv2 % mod;
        sg[i] = sg[i - 1];
        chadd(sg[i], g[i]);
    }
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout << fixed << setprecision(20);
    while (cin >> n) run();
    return 0;
}
