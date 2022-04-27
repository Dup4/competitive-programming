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
using ull = unsigned long long;
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
inline void pt(T s) {
    cout << s << "\n";
}
template <class T>
inline void pt(vector<T> &vec) {
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
int n, m, cnt[N], S[1010][1010];
ll f[N];
pII a[N];
ll gao2() {
    memset(cnt, 0, sizeof(cnt[0]) * (m + 10));
    for (int i = 1; i <= n; ++i) {
        if (a[i].fi < a[i].se) {
            ++cnt[0];
        } else
            ++cnt[min(a[i].fi, a[i].se)];
    }
    for (int i = 1; i <= m; ++i) cnt[i] += cnt[i - 1];
    ll res = 0;
    for (int i = 1; i <= n; ++i) {
        if (a[i].se > a[i].fi)
            res += n;
        else
            res += cnt[a[i].fi - 1];
    }
    return res;
}
ll gao3() {
    memset(cnt, 0, sizeof(cnt[0]) * (m + 10));
    memset(S, 0, sizeof S);
    for (int i = 1; i <= n; ++i) {
        if (a[i].fi >= a[i].se)
            ++cnt[a[i].se];
        else
            ++S[a[i].fi][a[i].se];
    }
    for (int i = 1; i <= m; ++i) {
        cnt[i] += cnt[i - 1];
    }
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= m; ++j) {
            S[i][j] += S[i - 1][j] + S[i][j - 1] - S[i - 1][j - 1];
        }
    }
    ll res = 0;
    for (int i = 1; i <= n; ++i) {
        if (a[i].fi >= a[i].se) {
            res += S[a[i].fi - 1][a[i].fi - 1];
        } else {
            res += cnt[a[i].fi - 1];
            res += S[a[i].fi - 1][m];
            res += S[m][a[i].se - 1] - S[a[i].fi - 1][a[i].se - 1];
        }
    }
    return res;
}
ll gao4() {
    memset(cnt, 0, sizeof(cnt[0]) * (m + 10));
    for (int i = 1; i <= n; ++i)
        if (a[i].fi < a[i].se)
            ++cnt[a[i].se];
    for (int i = 1; i <= m; ++i) cnt[i] += cnt[i - 1];
    ll res = 0;
    for (int i = 1; i <= n; ++i) {
        if (a[i].fi < a[i].se)
            res += cnt[a[i].fi - 1];
    }
    return res;
}
void run() {
    for (int i = 1; i <= n; ++i) cin >> a[i].fi >> a[i].se;
    f[1] = 1ll * n * n;
    f[2] = gao2();
    f[3] = gao3();
    f[4] = gao4();
    f[5] = 0;
    for (int i = 1; i <= 4; ++i) cout << f[i] - f[i + 1] << " \n"[i == 4];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout << fixed << setprecision(20);
    while (cin >> n >> m) run();
    return 0;
}
