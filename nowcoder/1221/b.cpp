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
constexpr int N = 5e4 + 10;
int n, k, q;
char s[N][10];
struct Hash {
    constexpr static ll seed[2] = {233, 13331};
    constexpr static ll mod[2] = {998244353, 1000000007};
    static ll base[2][10];
    static void init() {
        base[0][0] = base[1][0] = 1;
        for (int i = 1; i < 10; ++i) {
            base[0][i] = base[0][i - 1] * seed[0] % mod[0];
            base[1][i] = base[1][i - 1] * seed[1] % mod[1];
        }
    }
    ll a[2][10];
    inline void gao(char *s) {
        a[0][0] = a[1][0] = 0;
        for (int i = 1; s[i]; ++i) {
            a[0][i] = (a[0][i - 1] * seed[0] % mod[0] + s[i]) % mod[0];
            a[1][i] = (a[1][i - 1] * seed[1] % mod[1] + s[i]) % mod[1];
        }
    }
    inline ll get(int l, int r) {
        return (a[0][r] - a[0][l - 1] * base[0][r - l + 1] % mod[0] + mod[0]) % mod[0] * mod[0] +
               (a[1][r] - a[1][l - 1] * base[1][r - l + 1] % mod[1] + mod[1]) % mod[1];
        //	return pLL((a[0][r] - a[0][l - 1] * base[0][r - l + 1] % mod[0] + mod[0]) % mod[0], (a[1][r] - a[1][l -
        // 1] * base[1][r - l + 1] % mod[1] + mod[1]) % mod[1]);
    }
} hs;
ll Hash::base[2][10] = {{0}, {0}};
map<ll, int> mp[6];
void add(int f) {
    for (int i = 1; i <= k; ++i) {
        for (int j = i; j <= k; ++j) {
            mp[j - i + 1][hs.get(i, j)] += f;
        }
    }
}
void run() {
    for (int i = 1; i <= 5; ++i) mp[i].clear();
    for (int i = 1; i <= n; ++i) {
        cin >> (s[i] + 1);
        hs.gao(s[i]);
        add(1);
    }
    q = rd();
    while (q--) {
        int x = rd(), len = rd();
        hs.gao(s[x]);
        add(-1);
        int res = 0;
        for (int i = 1; i + len - 1 <= k; ++i) {
            int j = i + len - 1;
            if (mp[len].count(hs.get(i, j)))
                res += mp[len][hs.get(i, j)];
        }
        add(1);
        pt(res * len);
    }
}

int main() {
    Hash::init();
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout << fixed << setprecision(20);
    while (cin >> n >> k) run();
    return 0;
}
