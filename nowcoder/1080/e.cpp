#include <bits/stdc++.h>
using namespace std;
#define debug(...)           \
    {                        \
        printf("#  ");       \
        printf(__VA_ARGS__); \
        puts("");            \
    }
#define ll long long
#define endl "\n"
constexpr int N = 1e5 + 10;
constexpr int mod = 998244353;
template <class T1, class T2>
inline void chadd(T1 &x, T2 y) {
    x += y;
    if (x >= mod)
        x -= mod;
    else if (x < 0)
        x += mod;
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
inline void out(T s) {
    cout << s << "\n";
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
int n, a[N], S[N];
char s[N];
ll f[5], g[N];
void run() {
    cin >> (s + 1);
    S[0] = 0;
    for (int i = 1; i <= n; ++i) {
        a[i] = s[i] - '0';
        S[i] = S[i - 1] + a[i];
        S[i] %= 3;
    }
    memset(f, 0, sizeof f);
    memset(g, 0, sizeof g);
    g[0] = 1;
    if (a[1])
        f[0] = 1;
    for (int i = 1; i <= n; ++i) {
        g[i] = f[S[i]];
        if (!a[i])
            chadd(g[i], g[i - 1]);
        if (i < n and a[i + 1] != 0) {
            chadd(f[S[i]], g[i]);
        }
    }
    cout << g[n] << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout << fixed << setprecision(20);
    while (cin >> n) run();
    return 0;
}
