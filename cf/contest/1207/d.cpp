#include <bits/stdc++.h>
using namespace std;
#define debug(...)           \
    {                        \
        printf("#  ");       \
        printf(__VA_ARGS__); \
        puts("");            \
    }
#define ll long long
#define pii pair<int, int>
#define fi first
#define se second
const int N = 3e5 + 10;
const ll mod = 998244353;
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
int n;
pii a[N];
ll fac[N], res;
void run() {
    res = fac[n];
    for (int i = 1; i <= n; ++i) cin >> a[i].fi >> a[i].se;
    sort(a + 1, a + 1 + n, [](pii x, pii y) {
        return x.fi < y.fi;
    });
    vector<int> A, B, C;
    for (int i = 1; i <= n; ++i) {
        if (i == 1 || a[i].fi != a[i - 1].fi)
            A.push_back(i);
    }
    A.push_back(n + 1);
    sort(a + 1, a + 1 + n, [](pii x, pii y) {
        return x.se < y.se;
    });
    for (int i = 1; i <= n; ++i) {
        if (i == 1 || a[i].se != a[i - 1].se)
            B.push_back(i);
    }
    B.push_back(n + 1);
    ll As = 1, Bs = 1;
    for (int i = 1, sze = (int)A.size(); i < sze; ++i) As = As * fac[A[i] - A[i - 1]] % mod;
    for (int i = 1, sze = (int)B.size(); i < sze; ++i) Bs = Bs * fac[B[i] - B[i - 1]] % mod;
    res = res - As - Bs + mod * 2;
    res %= mod;
    sort(a + 1, a + 1 + n, [](pii x, pii y) {
        if (x.fi != y.fi)
            return x.fi < y.fi;
        return x.se < y.se;
    });
    bool F = 1;
    C.push_back(1);
    for (int i = 2; i <= n; ++i) {
        if (a[i].fi < a[i - 1].fi || a[i].se < a[i - 1].se) {
            F = 0;
            break;
        }
        if (a[i].fi != a[i - 1].fi || a[i].se != a[i - 1].se)
            C.push_back(i);
    }
    C.push_back(n + 1);
    if (F) {
        ll re = 1;
        for (int i = 1, sze = (int)C.size(); i < sze; ++i) re = re * fac[C[i] - C[i - 1]] % mod;
        res = (res + re) % mod;
    }
    res %= mod;
    res = (res + mod) % mod;
    cout << res << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout << fixed << setprecision(20);
    fac[0] = 1;
    for (int i = 1; i < N; ++i) fac[i] = fac[i - 1] * i % mod;
    while (cin >> n) run();
    return 0;
}
