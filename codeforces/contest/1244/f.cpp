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
constexpr int N = 4e5 + 10;
int n, k, vis[N];
char s[N];
bool ok() {
    for (int i = 2; s[i]; ++i)
        if (s[i - 1] == s[i])
            return false;
    return true;
}
bool ok2() {
    for (int i = 2; s[i]; ++i)
        if (s[i - 1] != s[i])
            return false;
    return true;
}
void gao(int l, int r) {
    if (l == r) {
        s[l] = s[l - 1];
        return;
    }
    char chl = s[l - 1], chr = s[r + 1];
    for (int i = 1; i <= k && l <= r; ++i) {
        s[l] = chl;
        s[r] = chr;
        ++l;
        --r;
    }
    if (l <= r && (k & 1)) {
        for (int i = l; i <= r; ++i) {
            s[i] = (s[i] == 'W' ? 'B' : 'W');
        }
    }
}
void run() {
    cin >> (s + 1);
    for (int i = n + 1; i <= 2 * n; ++i) s[i] = s[i - n];
    if (ok()) {
        if (k & 1) {
            for (int i = 1; i <= n; ++i) s[i] = (s[i] == 'W' ? 'B' : 'W');
        }
        s[n + 1] = 0;
        return pt(s + 1);
    }
    if (ok2()) {
        s[n + 1] = 0;
        return pt(s + 1);
    }
    memset(vis, 0, sizeof vis);
    for (int i = 2; i <= n * 2; ++i) {
        if (s[i - 1] == s[i]) {
            vis[i - 1] = vis[i] = 1;
        }
    }
    if (s[1] == s[n]) {
        vis[1] = vis[n] = vis[n + 1] = vis[n * 2] = 1;
    }
    int pos = 0;
    for (int i = 1; i <= n; ++i) {
        if (vis[i]) {
            pos = i;
            break;
        }
    }
    for (int i = pos + 1, l = -1, r = -1; i <= n + pos; ++i) {
        if (vis[i] == 0) {
            if (l == -1)
                l = i;
            r = i;
        } else {
            if (l != -1)
                gao(l, r);
            l = r = -1;
        }
    }
    for (int i = n + 1; i <= n + pos - 1; ++i) cout << s[i];
    for (int i = pos; i <= n; ++i) cout << s[i];
    pt();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout << fixed << setprecision(20);
    while (cin >> n >> k) run();
    return 0;
}
