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
constexpr int N = 1e2 + 10;
int n, a[N][2], b[N];
struct Hash {
    constexpr static ll seed[2] = {233, 13331};
    constexpr static ll mod[2] = {998244353, 1000000007};
    static ll base[2][N];
    static void init() {
        base[0][0] = base[1][0] = 1;
        for (int i = 1; i < N; ++i) {
            base[0][i] = base[0][i - 1] * seed[0] % mod[0];
            base[1][i] = base[1][i - 1] * seed[1] % mod[1];
        }
    }
    ll a[2][N];
    void gao(int *b) {
        // a[0][0] = 0;
        a[1][0] = 0;
        for (int i = 1; i <= n; ++i) {
            //	a[0][i] = (a[0][i - 1] * seed[0] % mod[0] + b[i] + 1) % mod[0];
            a[1][i] = (a[1][i - 1] * seed[1] % mod[1] + b[i] + 1) % mod[1];
        }
    }
    ll get(int l, int r) {
        return a[1][n];
    }
} hs;
ll Hash::base[2][N] = {{0}, {0}};
map<ll, int> mp;

int gao(int one) {
    mp.clear();
    for (int i = 0; i < (1 << 15); ++i) {
        bool flag = 1;
        for (int j = 1; j <= n; ++j) {
            b[j] = __builtin_popcount(i ^ a[j][1]);
            if (b[j] > one)
                flag = 0;
        }
        if (flag) {
            hs.gao(b);
            mp[hs.get(1, n)] = i << 15;
        }
    }
    for (int i = 0; i < (1 << 15); ++i) {
        bool flag = 1;
        for (int j = 1; j <= n; ++j) {
            b[j] = one - __builtin_popcount(i ^ a[j][0]);
            if (b[j] < 0)
                flag = 0;
        }
        if (flag) {
            hs.gao(b);
            ll hv = hs.get(1, n);
            if (mp.count(hv))
                return mp[hv] + i;
        }
    }
    return -1;
}

void run() {
    for (int i = 1; i <= n; ++i) {
        cin >> a[i][0];
        a[i][1] = (a[i][0] >> 15);
        a[i][0] &= (1 << 15) - 1;
    }
    for (int i = 0; i <= 30; ++i) {
        int res = gao(i);
        if (res != -1) {
            return pt(res);
        }
    }
    pt(-1);
}

int main() {
    Hash::init();
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout << fixed << setprecision(20);
    while (cin >> n) run();
    return 0;
}
