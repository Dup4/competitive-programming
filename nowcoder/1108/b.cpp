#include <bits/stdc++.h>
using namespace std;
#define debug(...)           \
    {                        \
        printf("#  ");       \
        printf(__VA_ARGS__); \
        puts("");            \
    }
#define fi first
#define se second
#define endl "\n"
using ll = long long;
using ull = unsigned long long;
using pII = pair<int, int>;
using pLL = pair<ll, ll>;
using VI = vector<int>;
using VL = vector<ll>;
constexpr ll mod = 1e9 + 7;
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
template <class T>
inline void pt(T s) {
    cout << s << "\n";
}
template <class T>
inline void pt(vector<T> &vec) {
    for (auto &it : vec) cout << it << " ";
    cout << endl;
}
inline ll gcd(ll a, ll b) {
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
constexpr int N = 2e3 + 10;
int n, m;
ll f[N][N][4];  // 1, 2, 1009, 2018
void run() {
    f[1][1][3] = 1;
    for (int i = 2; i <= m; ++i) {
        chadd(f[1][i][0], f[1][i - 1][0] + f[1][i - 1][1] + f[1][i - 1][2] + f[1][i - 1][3]);
        chadd(f[1][i][1], f[1][i - 1][1] + f[1][i - 1][3]);
        chadd(f[1][i][2], f[1][i - 1][2] + f[1][i - 1][3]);
        chadd(f[1][i][3], f[1][i - 1][3]);
    }
    for (int i = 2; i <= n; ++i) {
        chadd(f[i][1][0], f[i - 1][1][0] + f[i - 1][1][1] + f[i - 1][1][2] + f[i - 1][1][3]);
        chadd(f[i][1][1], f[i - 1][1][1] + f[i - 1][1][3]);
        chadd(f[i][1][2], f[i - 1][1][2] + f[i - 1][1][3]);
        chadd(f[i][1][3], f[i - 1][1][3]);
    }
    for (int i = 2; i <= n; ++i) {
        for (int j = 2; j <= m; ++j) {
        }
    }
    ll res = 0;
    chadd(res, f[n][m])
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout << fixed << setprecision(20);
    while (cin >> n >> m) run();
    return 0;
}
