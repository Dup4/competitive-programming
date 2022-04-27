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
constexpr int N = 1e5 + 10, M = 20;
char s[N];
int n;
struct ExKMP {
    int Next[N];
    void get_Next(char *s) {
        int lens = strlen(s + 1), p = 1, pos;
        Next[1] = lens;
        while (p + 1 <= lens && s[p] == s[p + 1]) ++p;
        Next[pos = 2] = p - 1;
        for (int i = 3; i <= lens; ++i) {
            int len = Next[i - pos + 1];
            if (len + i < p + 1)
                Next[i] = len;
            else {
                int j = max(p - i + 1, 0);
                while (i + j <= lens && s[j + 1] == s[i + j]) ++j;
                p = i + (Next[pos = i] = j) - 1;
            }
        }
    }
} exkmp;

struct RMQ {
    int Max[N][M];
    int mm[N];
    void init(int n, int *b) {
        mm[0] = -1;
        for (int i = 1; i <= n; ++i) {
            mm[i] = ((i & (i - 1)) == 0) ? mm[i - 1] + 1 : mm[i - 1];
            Max[i][0] = b[i];
        }
        for (int j = 1; j <= mm[n]; ++j) {
            for (int i = 1; i + (1 << j) - 1 <= n; ++i) {
                Max[i][j] = max(Max[i][j - 1], Max[i + (1 << (j - 1))][j - 1]);
            }
        }
    }
    int queryMax(int x, int y) {
        int k = mm[y - x + 1];
        return max(Max[x][k], Max[y - (1 << k) + 1][k]);
    }
} rmq;

void run() {
    n = strlen(s + 1);
    exkmp.get_Next(s);
    rmq.init(n, exkmp.Next);
    int res = 0;
    for (int i = 1; i <= n; ++i) {
        int l = i + 1, r = n - i - i + 1;
        if (exkmp.Next[n - i + 1] >= i && l <= r && rmq.queryMax(l, r) >= i)
            res = i;
    }
    s[res + 1] = 0;
    pt(s + 1);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout << fixed << setprecision(20);
    while (cin >> (s + 1)) run();
    return 0;
}
