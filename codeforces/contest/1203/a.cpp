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
bool ok1(int pos) {
    for (int i = pos + 1; i <= n; ++i)
        if (a[i] != a[i - 1] + 1)
            return 0;
    if (pos != 1 && a[1] != a[n] + 1)
        return 0;
    for (int i = 2; i < pos; ++i)
        if (a[i] != a[i - 1] + 1)
            return 0;
    return 1;
}
bool ok2(int pos) {
    for (int i = pos - 1; i >= 1; --i) {
        if (a[i] != a[i + 1] + 1) {
            return 0;
        }
    }
    if (pos != n && a[n] != a[1] + 1)
        return 0;
    for (int i = n - 1; i > pos; --i) {
        if (a[i] != a[i + 1] + 1) {
            return 0;
        }
    }
    return 1;
}

void run() {
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }
    if (n <= 2) {
        cout << "YES\n";
        return;
    }
    int pos = -1;
    for (int i = 1; i <= n; ++i)
        if (a[i] == 1) {
            pos = i;
            break;
        }
    if (ok1(pos) || ok2(pos))
        cout << "YES\n";
    else
        cout << "NO\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin >> T;
    while (T--) run();
    return 0;
}
