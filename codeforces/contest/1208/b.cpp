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
constexpr int mod = 1e9 + 7;
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
int n, a[N], f[N], g[N];
map<int, int> mp;
void run() {
    for (int i = 1; i <= n; ++i) cin >> a[i];
    memset(f, 0, sizeof f);
    memset(g, 0, sizeof g);
    f[n + 1] = 1;
    mp.clear();
    for (int i = n; i >= 1; --i) {
        if (mp.find(a[i]) != mp.end())
            break;
        f[i] = 1;
        mp[a[i]] = i;
    }
    if (f[1] == 1)
        return out(0);
    mp.clear();
    for (int i = n; i >= 1; --i) {
        if (mp.find(a[i]) == mp.end()) {
            g[i] = 0;
            mp[a[i]] = i;
        } else
            g[i] = mp[a[i]];
    }
    int res = n + 1;
    int Max = 0;
    mp.clear();
    for (int i = 1; i <= n; ++i) {
        for (int j = i; j <= n + 1; ++j) {
            if (j > Max && f[j] == 1) {
                res = min(res, j - i);
                break;
            }
        }
        Max = max(Max, g[i]);
        if (mp.find(a[i]) != mp.end())
            break;
        mp[a[i]] = i;
    }
    cout << res << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout << fixed << setprecision(20);
    while (cin >> n) run();
    return 0;
}
