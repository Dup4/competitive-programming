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
int n, m, q;
vector<pII> vec[2];
void gao(vector<pII> &vec) {
    sort(vec.begin(), vec.end(), [&](pII x, pII y) {
        if (x.fi != y.fi)
            return x.se > y.se;
        return x.fi < y.fi;
    });
    vector<pII> tmp;
    for (auto &it : vec) {
        if (tmp.empty())
            tmp.push_back(it);
        else {
            if (it.fi > tmp.end()[-1].se)
                tmp.push_back(it);
            else
                chadd(tmp.end()[-1].se, it.se);
        }
    }
    vec = tmp;
}
void run() {
    vec[0].clear();
    vec[1].clear();
    for (int i = 1, op, l, r; i <= q; ++i) {
        cin >> op >> l >> r;
        vec[op - 1].push_back(pII(l, r));
    }
    ll a = 0, b = 0;
    gao(vec[0]);
    gao(vec[1]);
    for (auto &it : vec[0]) a += it.se - it.fi + 1;
    for (auto &it : vec[1]) b += it.se - it.fi + 1;
    cout << a << " " << b << endl;
    ll res = 1ll * n * m;
    if (a == 0) {
        res -= b * (n - 1);
    } else if (b == 0) {
        res -= a * (m - 1);
    } else {
        res -= a * m + b * n - a * b;
        ++res;
    }
    pt(res);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout << fixed << setprecision(20);
    while (cin >> n >> m >> q) run();
    return 0;
}
