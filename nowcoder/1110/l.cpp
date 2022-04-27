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
constexpr int N = 1e5 + 10;
int n, a[N];
ll inv6, S[3][N];
void run() {
    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int i = 0; i < 3; ++i) {
        S[i][0] = 0;
        for (int j = 1; j <= n; ++j) {
            S[i][j] = S[i][j - 1] + qpow(a[j], i + 1);
            S[i][j] %= mod;
        }
    }
    ll res = 0;
    for (int i = 1; i + 3 <= n; ++i) {
        ll t = 1ll * a[i] * inv6 % mod;
        chadd(res, t * 2 % mod * (S[2][n] - S[2][i] + mod) % mod);
        chadd(res, mod - t * 3 % mod * (S[0][n] - S[0][i] + mod) % mod * (S[1][n] - S[1][i] + mod) % mod);
        chadd(res, t * qpow((S[0][n] - S[0][i] + mod) % mod, 3) % mod);
    }
    pt(res);
}

int main() {
    inv6 = qpow(6, mod - 2);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout << fixed << setprecision(20);
    while (cin >> n) run();
    return 0;
}
