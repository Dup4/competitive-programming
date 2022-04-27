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
inline void out(T s) {
    cout << s << "\n";
}
template <class T>
inline void out(vector<T> &vec) {
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
ll x, n, bit[110];
inline ll ceil(ll x, ll y) {
    return (x + y - 1) / y;
}
void run() {
    vector<int> fac;
    for (ll i = 2; i * i <= x; ++i) {
        if (x % i == 0)
            fac.push_back(i);
        while (x % i == 0) x /= i;
    }
    if (x != 1)
        fac.push_back(x);
    ll res = 1;
    for (auto &it : fac) {
        if (it > n)
            continue;
        int k = 1;
        bit[1] = it;
        for (int i = 2;; ++i) {
            if (bit[i - 1] > ceil(n, it)) {
                k = i - 1;
                break;
            }
            bit[i] = bit[i - 1] * it;
        }
        ll tot = 0;
        for (int i = k; i >= 1; --i) {
            ll p = n / bit[i];
            p -= tot;
            res = res * qpow(bit[i] % mod, p % (mod - 1)) % mod;
            tot += p;
        }
    }
    out(res);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout << fixed << setprecision(20);
    while (cin >> x >> n) run();
    return 0;
}
