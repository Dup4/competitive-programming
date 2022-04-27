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
constexpr int N = 4e5 + 10;
int n, a[N];
ll f[1 << 21], b[30], cnt[30][30];
void run() {
    for (int i = 1; i <= n; ++i) cin >> a[i], --a[i];
    // cnt[i][j]　表示将所有i都移动到j的后面的代价
    memset(cnt, 0, sizeof cnt);
    memset(b, 0, sizeof b);
    memset(f, 0x3f, sizeof f);
    for (int i = n; i >= 1; --i) {
        for (int j = 0; j < 20; ++j) cnt[a[i]][j] += b[j];
        ++b[a[i]];
    }
    f[0] = 0;
    for (int i = 0; i < 1 << 20; ++i) {
        for (int j = 0; j < 20; ++j) {
            if (((i >> j) & 1) == 0) {
                ll w = 0;
                for (int k = 0; k < 20; ++k) {
                    if ((i >> k) & 1)
                        w += cnt[j][k];
                }
                f[i | (1 << j)] = min(f[i | (1 << j)], f[i] + w);
            }
        }
    }
    out(f[(1 << 20) - 1]);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout << fixed << setprecision(20);
    while (cin >> n) run();
    return 0;
}
