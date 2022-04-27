#include <bits/stdc++.h>
using namespace std;
#define debug(...)           \
    {                        \
        printf("#  ");       \
        printf(__VA_ARGS__); \
        puts("");            \
    }
#define ll long long
const int N = 4e5 + 10;
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
int n;
ll a[N];
void run() {
    for (int i = 1; i <= n; ++i) cin >> a[i];
    ll G = a[1];
    for (int i = 2; i <= n; ++i) G = gcd(G, a[i]);
    int res = 0;
    for (ll i = 1; i * i <= G; ++i) {
        if (G % i == 0) {
            res += 2;
        }
        if (i * i == G)
            --res;
    }
    cout << res << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    while (cin >> n) run();
    return 0;
}
