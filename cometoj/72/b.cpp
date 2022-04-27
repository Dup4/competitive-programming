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
constexpr int N = 4e2 + 10;
int n, m;
char s[N][N];
string t;
pII que[N * N * 10];
int l, r;
bool ok(int x, int y) {
    if (x < 1 || x > n || y < 1 || y > m)
        return false;
    return true;
}
void run() {
    l = N * N * 2, r = l - 1;
    for (int i = 1; i <= n; ++i) {
        cin >> (s[i] + 1);
        for (int j = 1; j <= m; ++j) {
            if (s[i][j] == '@') {
                que[++r] = pII(i, j);
                s[i][j] = '.';
            }
        }
    }
    cin >> t;
    for (auto &c : t) {
        int x = que[l].fi, y = que[l].se;
        if (c == 'W') {
            --x;
        } else if (c == 'A') {
            --y;
        } else if (c == 'S') {
            ++x;
        } else {
            ++y;
        }
        if (!ok(x, y)) {
            return pt("GG");
        }
        if (s[x][y] == 'o') {
            s[x][y] = '.';
            que[--l] = pII(x, y);
        } else {
            que[--l] = pII(x, y);
            --r;
        }
    }
    for (int i = l; i <= r; ++i) {
        s[que[i].fi][que[i].se] = 'X';
    }
    s[que[l].fi][que[l].se] = '@';
    for (int i = 1; i <= n; ++i) pt((s[i] + 1));
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout << fixed << setprecision(20);
    while (cin >> n >> m) run();
    return 0;
}
