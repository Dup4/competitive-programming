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
int n, m, a[N], b[N], cnt[N], f[N];
void run() {
    memset(cnt, 0, sizeof cnt);
    memset(f, 0, sizeof f);
    for (int i = 1; i <= n; ++i) cin >> a[i], b[i] = a[i];
    sort(b + 1, b + 1 + n);
    m = unique(b + 1, b + 1 + n) - b - 1;
    for (int i = 1; i <= n; ++i) {
        a[i] = lower_bound(b + 1, b + 1 + m, a[i]) - b;
        ++cnt[a[i]];
    }
    int x = 0, y = 0, tot = 0, num = 0, Max = 0;
    for (int i = 1; i <= m; ++i) ++f[cnt[i]], chmax(Max, cnt[i]);
    for (int i = 1; i <= n; ++i) {
        tot += f[i] * i;
        num += f[i];
        int Tot = tot + (m - num) * i;
        int X = i, Y = Tot / X;
        if (Y >= X && X * Y > x * y) {
            x = X, y = Y;
        }
    }
    vector<int> po(m), vec;
    iota(po.begin(), po.end(), 1);
    sort(po.begin(), po.end(), [&](int x, int y) {
        return cnt[x] > cnt[y];
    });
    for (auto &it : po) {
        if (cnt[it] >= x)
            cnt[it] = x;
        for (int j = 1; j <= cnt[it]; ++j) vec.push_back(b[it]);
    }
    reverse(vec.begin(), vec.end());
    vector<vector<int>> G(x + 1, vector<int>(y + 1));
    for (int i = 1; i <= y - x + 1; ++i) {
        int a = 1, b = i;
        while (a <= x && b <= y) {
            G[a][b] = vec.back();
            vec.pop_back();
            ++a;
            ++b;
        }
    }
    for (int i = 2; i <= x; ++i) {
        int a = i, b = 1;
        while (a <= x && b <= y) {
            G[a][b] = vec.back();
            vec.pop_back();
            ++a, ++b;
        }
        a = 1, b = y - i + 2;
        while (a <= x && b <= y) {
            G[a][b] = vec.back();
            vec.pop_back();
            ++a, ++b;
        }
    }
    pt(x * y);
    pt(x, y);
    for (int i = 1; i <= x; ++i)
        for (int j = 1; j <= y; ++j) cout << G[i][j] << " \n"[j == y];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout << fixed << setprecision(20);
    while (cin >> n) run();
    return 0;
}
