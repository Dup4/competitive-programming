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
constexpr int N = 2e5 + 10;
constexpr int M = 2e5;
int n, p[N];
ll pre[N], suf[N];
void run() {
    memset(p, 0, sizeof p);
    for (int i = 1; i <= n; ++i) ++p[rd()];
    pre[0] = 1;
    for (int i = 1; i <= M; ++i) {
        pre[i] = pre[i - 1] * (p[i] + 1) % (mod - 1);
    }
    suf[M + 1] = 1;
    for (int i = M; i >= 1; --i) {
        suf[i] = suf[i + 1] * (p[i] + 1) % (mod - 1);
    }
    ll res = 1;
    for (int i = 1; i <= M; ++i) {
        ll t = 1;
        for (int j = 1; j <= p[i]; ++j) {
            t = t * i % mod;
            res = res * qpow(t, pre[i - 1] * suf[i + 1] % (mod - 1)) % mod;
        }
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
