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
int n, a[40], b[40];
ll l, r;
ll dp[110][2][2][2][2][2];
ll dfs(int pos, int flag1, int flag2, int limit, int one1, int one2) {
    if (pos == -1 && limit == 0 && one1 == 1 && one2 == 1) {
        return 1ll;
    } else if (pos == -1) {
        return 0ll;
    }
    ll &res = dp[pos][flag1][flag2][limit][one1][one2];
    if (res != -1)
        return res;
    res = 0;
    if (limit)
        return 0ll;
    int l1 = flag1 ? a[pos] : 1;
    int l2 = flag2 ? b[pos] : 1;
    for (int i = 0; i <= l1; ++i) {
        for (int j = 0; j <= l2; ++j) {
            res += dfs(pos - 1, flag1 && (i == a[pos]), flag2 && (j == b[pos]), limit | (i & j), one1 | i, one2 | j);
        }
    }
    return res;
}
inline ll f(ll A, ll B) {
    if (A <= 0 || B <= 0)
        return 0;
    memset(dp, -1, sizeof dp);
    memset(a, 0, sizeof a);
    memset(b, 0, sizeof b);
    for (int i = 31; i >= 0; --i) {
        a[i] = (A >> i) & 1;
        b[i] = (B >> i) & 1;
    }
    return dfs(31, 1, 1, 0, 0, 0);
}
void run() {
    cin >> l >> r;
    ll other = 0;
    if (l == 0) {
        other = r + r + 1;
    }
    pt(f(r, r) - f(l - 1, r) - f(r, l - 1) + f(l - 1, l - 1) + other);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout << fixed << setprecision(20);
    int _T = rd();
    while (_T--) run();
    return 0;
}
