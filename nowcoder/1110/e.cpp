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
constexpr int N = 5e3 + 10;
int n, a[N];
pII f[N];
int g[N], h[N];
bool operator<(const pII &x, const pII &y) {
    if (x.fi != y.fi)
        return x.fi < y.fi;
    return x.se < y.se;
}
struct SEG {
    pII t[N << 2];
    void build(int id, int l, int r) {
        t[id] = pII(0, 0);
        if (l == r)
            return;
        int mid = (l + r) >> 1;
        build(id << 1, l, mid);
        build(id << 1 | 1, mid + 1, r);
    }
    void update(int id, int l, int r, int pos, pII v) {
        if (l == r) {
            t[id] = max(t[id], v);
            return;
        }
        int mid = (l + r) >> 1;
        if (pos <= mid)
            update(id << 1, l, mid, pos, v);
        else
            update(id << 1 | 1, mid + 1, r, pos, v);
        t[id] = max(t[id << 1], t[id << 1 | 1]);
    }
    pII query(int id, int l, int r, int ql, int qr) {
        if (ql > qr)
            return pII(0, 0);
        if (l >= ql && r <= qr)
            return t[id];
        int mid = (l + r) >> 1;
        pII res = pII(0, 0);
        if (ql <= mid)
            res = max(res, query(id << 1, l, mid, ql, qr));
        if (qr > mid)
            res = max(res, query(id << 1 | 1, mid + 1, r, ql, qr));
        return res;
    }
} seg;
void run() {
    seg.build(1, 1, n);
    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int i = 1; i <= n; ++i) {
        f[i] = pII(0, 0);
        f[i] = max(seg.query(1, 1, n, 1, a[i] - 1), f[i]);
        ++f[i].fi;
        seg.update(1, 1, n, a[i], pII(f[i].fi, i));
    }
    memset(h, 0, sizeof h);
    memset(g, 0, sizeof g);
    int base = 0;
    for (int i = 1; i <= n; ++i) {
        int res = base;
        for (int j = i + 1; j <= n; ++j) {
            h[j] = f[j].fi - 1;
            if (g[a[j] - 1] + 1 > h[j])
                ++h[j];
            if (f[j].se != i)
                h[j] = max(h[j], h[f[j].se] + 1);
            res ^= h[j] * h[j];
        }
        cout << res << " \n"[i == n];
        h[i] = f[i].fi;
        g[a[i]] = max(g[a[i]], h[i]);
        for (int j = a[i] + 1; j <= n; ++j) g[j] = max(g[j], g[j - 1]);
        base ^= h[i] * h[i];
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout << fixed << setprecision(20);
    while (cin >> n) run();
    return 0;
}
