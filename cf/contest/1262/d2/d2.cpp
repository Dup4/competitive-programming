#pragma GCC optimize("Ofast,unroll-loops,no-stack-protector,fast-math")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#include <bits/stdc++.h>
#define fi first
#define se second
#define endl "\n"
using namespace std;
using db = double;
using ll = long long;
using ull = unsigned long long;
using pII = pair<int, int>;
using pLL = pair<ll, ll>;
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
#define dbg(x...)                             \
    do {                                      \
        cout << "\033[32;1m" << #x << " -> "; \
        err(x);                               \
    } while (0)
void err() {
    cout << "\033[39;0m" << endl;
}
template <class T, class... Ts>
void err(const T &arg, const Ts &...args) {
    cout << arg << ' ';
    err(args...);
}
template <template <typename...> class T, typename t, typename... A>
void err(const T<t> &arg, const A &...args) {
    for (auto &v : arg) cout << v << ' ';
    err(args...);
}
void ptt() {
    cout << endl;
}
template <class T, class... Ts>
void ptt(const T &arg, const Ts &...args) {
    cout << ' ' << arg;
    ptt(args...);
}
template <class T, class... Ts>
void pt(const T &arg, const Ts &...args) {
    cout << arg;
    ptt(args...);
}
void pt() {}
template <template <typename...> class T, typename t, typename... A>
void pt(const T<t> &arg, const A &...args) {
    for (int i = 0, sze = arg.size(); i < sze; ++i) cout << arg[i] << " \n"[i == sze - 1];
    pt(args...);
}
ll gcd(ll a, ll b) {
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
// head
constexpr int N = 2e5 + 10;
int n, q, k, pos, a[N], ans[N];
pII b[N];

struct SEG {
    struct node {
        int sum;
        node() {
            sum = 0;
        }
        node operator+(const node &other) const {
            node res = node();
            res.sum = sum + other.sum;
            return res;
        }
    } t[N << 2];
    void init() {
        memset(t, 0, sizeof t);
    }
    void update(int id, int l, int r, int pos) {
        if (l == r) {
            t[id].sum = 1;
            return;
        }
        int mid = (l + r) >> 1;
        if (pos <= mid)
            update(id << 1, l, mid, pos);
        else
            update(id << 1 | 1, mid + 1, r, pos);
        t[id] = t[id << 1] + t[id << 1 | 1];
    }
    int query(int id, int l, int r, int k) {
        if (l == r)
            return l;
        int mid = (l + r) >> 1;
        if (t[id << 1].sum >= k)
            return query(id << 1, l, mid, k);
        else
            return query(id << 1 | 1, mid + 1, r, k - t[id << 1].sum);
    }
} seg;

void run() {
    vector<vector<pII>> qvec;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        b[i] = pII(a[i], i);
    }
    sort(b + 1, b + 1 + n, [&](pII x, pII y) {
        if (x.fi != y.fi)
            return x.fi > y.fi;
        return x.se < y.se;
    });
    cin >> q;
    qvec.clear();
    qvec.resize(n + 5);
    for (int i = 1; i <= q; ++i) {
        cin >> k >> pos;
        qvec[k].push_back(pII(pos, i));
    }
    seg.init();
    for (int i = 1; i <= n; ++i) {
        seg.update(1, 1, n, b[i].se);
        for (auto &it : qvec[i]) {
            ans[it.se] = seg.query(1, 1, n, it.fi);
        }
    }
    for (int i = 1; i <= q; ++i) pt(a[ans[i]]);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout << fixed << setprecision(20);
    while (cin >> n) run();
    return 0;
}
