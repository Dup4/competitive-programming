#pragma GCC optimize("Ofast,unroll-loops,no-stack-protector,fast-math")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#include <bits/stdc++.h>
#define fi first
#define se second
#define endl "\n"
using namespace std;
using db = double;
using ll = long long;
using ull = unsigned long long;
using pII = pair<int, int>;
using pLL = pair<ll, ll>;
constexpr int mod = 1e9 + 7;
template <class T1, class T2>
inline void chadd(T1 &x, T2 y) {
    x += y;
    while (x >= mod) x -= mod;
    while (x < 0) x += mod;
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
inline void pt() {
    cout << endl;
}
template <class T, class... Ts>
void pt(const T &arg, const Ts &...args) {
    cout << arg << ' ';
    pt(args...);
}
template <template <typename...> class T, typename t, typename... A>
void pt(const T<t> &arg, const A &...args) {
    for (auto &v : arg) cout << v << ' ';
    pt(args...);
}
ll gcd(ll a, ll b) {
    return b ? gcd(b, a % b) : a;
}
inline ll qpow(ll base, ll n) {
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
constexpr int N = 1e5 + 10, inv2 = (mod + 1) / 2;
int n, k;
ll gao(ll a, ll b, ll c, ll n) {
    if (a == 0) {
        return (n + 1) * (b / c) % mod;
    }
    if (a >= c || b >= c) {
        ll tmp = gao(a % c, b % c, c, n);
        ll res = (tmp + (a / c) % mod * (n % mod) % mod * ((n + 1) % mod) % mod * inv2 % mod +
                         (b / c) % mod * ((n + 1) % mod) % mod) %
                 mod;
        res = (res + mod) % mod;
        return res;
    }
    ll m = ((__int128)a * n + b) / c;
    ll tmp = gao(c, c - b - 1, a, m - 1);
    ll res = ((__int128)n * (m % mod) % mod - tmp + mod) % mod;
    res = (res + mod) % mod;
    return res;
}
void run() {
    ll res = (1ll * (n + 1) * 2 * k % mod - k + mod) % mod;
    for (int i = 1; i <= n; ++i) {
        for (int j = 31; j >= 0; --j) {
            ll tmp = (gao(i, 0, 1ll << j, n) - 2ll * gao(i, 0, 1ll << (j + 1), n) % mod + mod) % mod;
            //	dbg(i, j, tmp);
            if ((k >> j) & 1) {
                chadd(res, (1ll << j) % mod * (1ll * n - tmp) % mod);
            } else {
                chadd(res, (1ll << j) % mod * tmp % mod);
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
    while (cin >> n >> k) run();
    return 0;
}
