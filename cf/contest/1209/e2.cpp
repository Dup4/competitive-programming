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
constexpr int N = 2e3 + 10;
constexpr int M = 4e3 + 200;
int n, m, a[N][20], b[20], f[M], g[M], bf[M];
vector<pII> vec;
void Sort() {
    vec.clear();
    for (int i = 1; i <= m; ++i) {
        int Max = a[i][1];
        for (int j = 2; j <= n; ++j) Max = max(Max, a[i][j]);
        vec.push_back(pII(Max, i));
    }
    sort(vec.begin(), vec.end());
    reverse(vec.begin(), vec.end());
}
inline void shift() {
    int t = b[n];
    for (int i = n; i >= 2; --i) b[i] = b[i - 1];
    b[1] = t;
}
void run() {
    cin >> n >> m;
    for (int j = 1; j <= n; ++j)
        for (int i = 1; i <= m; ++i) cin >> a[i][j];
    Sort();
    memset(f, 0, sizeof f);
    m = min(n, m);
    for (int i = 1; i <= m; ++i) {
        int id = vec[i - 1].se;
        for (int j = 1; j <= n; ++j) b[j] = a[id][j];
        memset(g, 0, sizeof g);
        for (int j = 1; j <= n; ++j) {
            shift();
            for (int mask = 0; mask < (1 << n); ++mask) {
                int sum = 0;
                for (int k = 0; k < n; ++k)
                    if ((mask >> k) & 1)
                        sum += b[k + 1];
                chmax(g[mask], sum);
            }
        }
        for (int mask = 0; mask < (1 << n); ++mask) bf[mask] = f[mask];
        for (int mask = 0; mask < (1 << n); ++mask) {
            int fmask = ((1 << n) - 1) ^ mask;
            for (int o = fmask; o > 0; o = (o - 1) & fmask) {
                f[mask ^ o] = max(f[mask ^ o], bf[mask] + g[o]);
            }
        }
        for (int mask = 0; mask < (1 << n); ++mask) f[mask] = max(f[mask], bf[mask]);
    }
    cout << f[(1 << n) - 1] << endl;
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
