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
constexpr int N = 2e5 + 10;
int n;
ll s;
pII a[N];
bool check(ll x) {
    int l = 0, r = 0;
    ll remind = s;
    for (int i = 1; i <= n; ++i) {
        if (a[i].se < x) {
            remind -= a[i].fi;
            ++l;
        } else if (a[i].fi > x) {
            remind -= a[i].fi;
            ++r;
        }
    }
    if (l > n / 2 || r > n / 2)
        return false;
    for (int i = 1; i <= n; ++i) {
        if (a[i].fi <= x && a[i].se >= x) {
            if (l < n / 2) {
                ++l;
                remind -= a[i].fi;
            } else {
                remind -= x;
            }
        }
    }
    return remind >= 0;
}
void run() {
    cin >> n >> s;
    for (int i = 1; i <= n; ++i) a[i].fi = rd(), a[i].se = rd();
    sort(a + 1, a + 1 + n);
    ll l = a[n / 2 + 1].fi, r = 1e9, res = l;
    while (r - l >= 0) {
        ll mid = (l + r) >> 1;
        if (check(mid)) {
            res = mid;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    pt(res);
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
