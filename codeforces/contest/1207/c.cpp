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
char s[N];
ll a, b;
void run() {
    cin >> n >> a >> b;
    cin >> (s + 1);
    ll res = 0;
    res = 1ll * n * a + 1ll * (n + 1) * b;
    int l = -1, r = -1;
    for (int i = 1; i <= n; ++i)
        if (s[i] == '1') {
            res += a + a;
            l = i;
            break;
        }
    for (int i = n; i >= 1; --i)
        if (s[i] == '1') {
            r = i;
            break;
        }
    for (int i = 1; i <= n; ++i) {
        if (s[i] == '1') {
            if (i > 1 && s[i - 1] == '1') {
                res += b;
            } else {
                res += b * 2;
            }
        }
    }
    for (int i = l, j; i <= r;) {
        if (s[i] == '0') {
            for (j = i; j <= r; ++j) {
                if (s[j] == '1')
                    break;
            }
            --j;
            int len = j - i;
            if (len >= 1) {
                res += min(a * 2, b * len);
            }
            i = j + 1;
        } else
            ++i;
    }
    cout << res << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout << fixed << setprecision(20);
    int _T;
    cin >> _T;
    while (_T--) run();
    return 0;
}
