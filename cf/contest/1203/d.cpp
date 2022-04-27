#include <bits/stdc++.h>
using namespace std;
#define debug(...)           \
    {                        \
        printf("#  ");       \
        printf(__VA_ARGS__); \
        puts("");            \
    }
#define ll long long
const int N = 2e5 + 10;
const int mod = 1e9 + 7;
template <class T1, class T2>
inline void chadd(T1 &x, T2 y) {
    x += y;
    if (x >= mod)
        x -= mod;
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
int n, m;
char s[N], t[N];
int f[N][26], g[N][26], nx[26], h[N];
void run() {
    n = strlen(s + 1), m = strlen(t + 1);
    for (int i = 0; i < 26; ++i) nx[i] = n + 1;
    for (int i = n; i >= 0; --i) {
        for (int j = 0; j < 26; ++j) {
            f[i][j] = nx[j];
        }
        if (i)
            nx[s[i] - 'a'] = i;
    }
    for (int i = 0; i < 26; ++i) nx[i] = 0;
    for (int i = 1; i <= n + 1; ++i) {
        for (int j = 0; j < 26; ++j) {
            g[i][j] = nx[j];
        }
        if (i <= n + 1)
            nx[s[i] - 'a'] = i;
    }
    for (int i = m, now = n + 1; i >= 1; --i) {
        now = g[now][t[i] - 'a'];
        h[i] = now;
    }
    int res = max(0, h[1] - 1), now = 0;
    for (int i = 1; i <= m; ++i) {
        now = f[now][t[i] - 'a'];
        res = max(res, h[i + 1] - now - 1);
    }
    res = max(res, n - now);
    cout << res << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    while (cin >> (s + 1) >> (t + 1)) run();
    return 0;
}
