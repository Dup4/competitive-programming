#include <bits/stdc++.h>
using namespace std;
#define debug(...)           \
    {                        \
        printf("#  ");       \
        printf(__VA_ARGS__); \
        puts("");            \
    }
#define ll long long
const int N = 1e5 + 10;
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
int T, n, a[N];
void out(string s) {
    cout << s << "\n";
}
void run() {
    cin >> n;
    for (int i = 1; i <= 10000; ++i) a[i] = 0;
    for (int i = 1; i <= 4 * n; ++i) {
        ++a[rd()];
    }
    int l = 1, r = 10000;
    int area = -1;
    while (l < r) {
        while (!a[l]) ++l;
        while (!a[r]) --r;
        if (a[l] & 1)
            return out("NO");
        if (a[l] != a[r])
            return out("NO");
        if (area == -1)
            area = l * r;
        else if (l * r != area)
            return out("NO");
        ++l, --r;
    }
    out("YES");
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin >> T;
    while (T--) run();
    return 0;
}
