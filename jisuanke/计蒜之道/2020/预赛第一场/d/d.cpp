
#include <bits/stdc++.h>
using namespace std;
#define endl "\n"
#define fi first
#define se second
#define SZ(x) ((int)(x).size())
#define mkp make_pair
#define all(x) (x).begin(), (x).end()
using db = double;
using ll = long long;
using ull = unsigned long long;
using pII = pair<int, int>;
using pLL = pair<ll, ll>;
constexpr int mod = 1e9 + 7;
template <class T1, class T2>
inline void chadd(T1 &x, T2 y, int Mod = mod) {
    x += y;
    while (x >= Mod) x -= Mod;
    while (x < 0) x += Mod;
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
inline int nextInt() {
    int x;
    cin >> x;
    return x;
}
void rd() {}
template <class T, class... Ts>
void rd(T &arg, Ts &...args) {
    cin >> arg;
    rd(args...);
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
inline ll qpow(ll base, ll n) {
    assert(n >= 0);
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
constexpr int N = 3e5 + 10;
constexpr ll INFLL = 0x3f3f3f3f3f3f3f3f;
int n, m;
ll b[N], w[N], f[N], Sb[N], Sw[N];

struct E {
    int t, l, r;
    ll c;
    E() {}
    void scan() {
        rd(t, l, r, c);
    }
    bool operator<(const E &other) const {
        return r < other.r;
    }
} e[N];

struct SEG {
    struct node {
        ll Max, lazy;
        node() {
            lazy = 0;
            Max = 0;
        }
        void up(ll x) {
            Max += x;
            lazy += x;
        }
        node operator+(const node &other) const {
            node res = node();
            res.Max = max(Max, other.Max);
            return res;
        }
    } t[N << 2];
    void down(int id) {
        ll &lazy = t[id].lazy;
        t[id << 1].up(lazy);
        t[id << 1 | 1].up(lazy);
        lazy = 0;
    }
    void build(int id, int l, int r) {
        t[id] = node();
        if (l == r) {
            return;
        }
        int mid = (l + r) >> 1;
        build(id << 1, l, mid);
        build(id << 1 | 1, mid + 1, r);
        t[id] = t[id << 1] + t[id << 1 | 1];
    }
    void update(int id, int l, int r, int ql, int qr, ll v) {
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
    ll query(int id, int l, int r, int ql, int qr) {
        if (l >= ql && r <= qr)
            return t[id].Max;
        int mid = (l + r) >> 1;
        down(id);
        ll res = -INFLL;
        if (ql <= mid)
            chmax(res, query(id << 1, l, mid, ql, qr));
        if (qr > mid)
            chmax(res, query(id << 1 | 1, mid + 1, r, ql, qr));
        return res;
    }
} seg[2];

void run() {
    rd(n, m);
    for (int i = 1; i <= n; ++i) rd(b[i]), Sb[i] = Sb[i - 1] + b[i];
    for (int i = 1; i <= n; ++i) rd(w[i]), Sw[i] = Sw[i - 1] + w[i];
    for (int i = 1; i <= m; ++i) e[i].scan();
    memset(f, 0, sizeof f);
    sort(e + 1, e + 1 + m);
    int pos = 1;
    seg[0].build(1, 1, n);
    seg[1].build(1, 1, n);
    for (int i = 1; i <= n; ++i) {
        f[i] = max(b[i], w[i]) + f[i - 1];
        seg[0].update(1, 1, n, 1, i, b[i]);
        seg[1].update(1, 1, n, 1, i, w[i]);
        while (pos <= m && e[pos].r == i) {
            int t = e[pos].t, l = e[pos].l, r = e[pos].r;
            ll c = e[pos].c;
            seg[t - 1].update(1, 1, n, 1, l, c);
            ++pos;
        }
        seg[0].update(1, 1, n, i, i, f[i - 1]);
        seg[1].update(1, 1, n, i, i, f[i - 1]);
        chmax(f[i], seg[0].query(1, 1, n, 1, i));
        chmax(f[i], seg[1].query(1, 1, n, 1, i));
    }
    pt(f[n]);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout << fixed << setprecision(20);
    int _T = 1;
    while (_T--) run();
    //    for (int kase = 1; kase <= _T; ++kase) {
    //        cout << "Case #" << kase << ": ";
    //        run();
    //    }
    //	while (cin >> n) run();
    //	run();
    return 0;
}
