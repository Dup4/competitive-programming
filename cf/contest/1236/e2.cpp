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
constexpr int N = 1e6 + 10, OFFSET = 2e5;
int n, m, a[N], l[N], r[N], f[N], last[N];
// y - x
void gaol() {
    memset(last, -1, sizeof last);
    for (int i = m; i >= 1; --i) {
        int p = a[i] + 1 + i;
        if (last[p] == -1)
            f[i] = max(1, a[i] - (m - i));
        else
            f[i] = f[last[p]];
        last[a[i] + i] = i;
    }
    for (int i = 1; i <= n; ++i) {
        int p = i;
        //		dbg(i, p, last[p]);
        if (last[p] == -1)
            l[i] = max(1, i - (m + 1));
        else
            l[i] = f[last[p]];
    }
}
void gaor() {
    memset(last, -1, sizeof last);
    for (int i = m; i >= 1; --i) {
        int p = a[i] - 1 - i + OFFSET;
        if (last[p] == -1)
            f[i] = min(n, a[i] + m - i);
        else
            f[i] = f[last[p]];
        last[a[i] - i + OFFSET] = i;
    }
    for (int i = 1; i <= n; ++i) {
        int p = i + OFFSET;
        if (last[p] == -1)
            r[i] = min(n, i + m + 1);
        else
            r[i] = f[last[p]];
    }
}
void run() {
    for (int i = 1; i <= m; ++i) a[i] = rd();
    if (n == 1)
        return pt(0);
    gaol();
    gaor();
    ll ans = 0;
    for (int i = 1; i <= n; ++i) {
        //	dbg(i, l[i], r[i]);
        ans += r[i] - l[i] + 1;
    }
    pt(ans);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout << fixed << setprecision(20);
    while (cin >> n >> m) run();
    return 0;
}
