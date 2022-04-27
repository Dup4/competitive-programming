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
inline void pt() {
    cout << endl;
}
template <class T, class... Ts>
void pt(const T &arg, const Ts &...args) {
    cout << arg << ' ';
    pt(args...);
}
template <template <typename...> class T, typename t, typename... A>
void pt(const T<t> &arg, const A &...args) {
    for (auto &v : arg) cout << v << ' ';
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
constexpr int N = 1e3 + 10, OFFSET = 500, INF = 0x3f3f3f3f;
int n, a[N], f[N];
char s[N];
struct SEG {
    struct node {
        int Max, lazy;
        node() {
            Max = -INF;
            lazy = 0;
        }
        void up(int x) {
            Max += x;
            lazy += x;
        }
        node operator+(const node &other) const {
            node res = node();
            res.Max = max(Max, other.Max);
            return res;
        }
    } t[N << 2];
    void build(int id, int l, int r) {
        t[id] = node();
        if (l == r) {
            t[id].Max = f[l];
            return;
        }
        int mid = (l + r) >> 1;
        build(id << 1, l, mid);
        build(id << 1 | 1, mid + 1, r);
        t[id] = t[id << 1] + t[id << 1 | 1];
    }
    void down(int id) {
        int &lazy = t[id].lazy;
        if (!lazy)
            return;
        t[id << 1].up(lazy);
        t[id << 1 | 1].up(lazy);
        lazy = 0;
    }
    void update(int id, int l, int r, int ql, int qr, int v) {
        if (ql > qr)
            return;
        if (l >= ql && r <= qr) {
            t[id].up(v);
            return;
        }
        int mid = (l + r) >> 1;
        down(id);
        if (ql <= mid)
            update(id << 1, l, mid, ql, qr, v);
        if (qr > mid)
            update(id << 1 | 1, mid + 1, r, ql, qr, v);
        t[id] = t[id << 1] + t[id << 1 | 1];
    }
    int query(int id, int l, int r, int ql, int qr) {
        if (ql > qr)
            return 0;
        if (l >= ql && r <= qr)
            return t[id].Max;
        int mid = (l + r) >> 1;
        down(id);
        int res = -INF;
        if (ql <= mid)
            chmax(res, query(id << 1, l, mid, ql, qr));
        if (qr > mid)
            chmax(res, query(id << 1 | 1, mid + 1, r, ql, qr));
        return res;
    }
} seg;
int calc() {
    memset(f, 0, sizeof f);
    for (int i = 1 + OFFSET; i <= n + OFFSET; ++i) f[i] = f[i - 1] + a[i];
    if (f[n + OFFSET] != 0)
        return 0;
    seg.build(1, 1, n + OFFSET);
    int res = 0, l = 1 + OFFSET;
    for (int i = n + OFFSET; i >= 1 + OFFSET; --i) {
        --l;
        seg.update(1, 1, n + OFFSET, l, i - 1, a[i]);
        if (seg.query(1, 1, n + OFFSET, l, i - 1) <= 0) {
            ++res;
        }
    }
    return res;
}
void run() {
    cin >> (s + 1);
    for (int i = 1; i <= n; ++i) {
        if (s[i] == '(')
            a[i + OFFSET] = -1;
        else
            a[i + OFFSET] = 1;
    }
    int num = calc(), x = 1, y = 1;
    for (int i = 1; i <= n; ++i) {
        for (int j = i + 1; j <= n; ++j) {
            swap(a[i + OFFSET], a[j + OFFSET]);
            int now = calc();
            if (now > num) {
                num = now;
                x = i, y = j;
            }
            swap(a[i + OFFSET], a[j + OFFSET]);
        }
    }
    pt(num);
    pt(x, y);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout << fixed << setprecision(20);
    while (cin >> n) run();
    return 0;
}
