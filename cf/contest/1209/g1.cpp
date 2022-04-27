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
int n, q, a[N], b[N], l[N], r[N];
vector<pII> vec, ovec;
void run() {
    memset(b, 0, sizeof b);
    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int i = 1; i <= n; ++i) {
        if (!b[a[i]])
            l[a[i]] = i;
        r[a[i]] = i;
        ++b[a[i]];
    }
    vec.clear();
    for (int i = 1; i <= 200000; ++i)
        if (b[i])
            vec.push_back(pII(l[i], r[i]));
    sort(vec.begin(), vec.end(), [&](pII x, pII y) {
        return x.fi < y.fi;
    });
    ovec.clear();
    ovec.push_back(vec[0]);
    for (int i = 1, sze = vec.size(); i < sze; ++i) {
        if (vec[i].fi < ovec.end()[-1].se) {
            ovec.end()[-1].se = max(ovec.end()[-1].se, vec[i].se);
        } else {
            ovec.push_back(vec[i]);
        }
    }
    int res = 0;
    for (auto &it : ovec) {
        int Max = 0;
        for (int i = it.fi; i <= it.se; ++i) {
            Max = max(Max, b[a[i]]);
        }
        res += Max;
    }
    cout << n - res << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout << fixed << setprecision(20);
    while (cin >> n >> q) run();
    return 0;
}
