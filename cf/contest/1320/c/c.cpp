#include <bits/stdc++.h>
#define fi first
#define se second
#define SZ(x) int((x).size())
#define endl "\n"
using namespace std;
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
constexpr int N = 1e6 + 10;
constexpr ll INF = 1e18;
int n, m, p;
pII a[N], b[N];

struct SEG {
    struct node {
        ll Max, lazy;
        node() {
            Max = lazy = 0;
        }
        void up(ll x) {
            lazy += x;
            Max += x;
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
            t[id].Max = -INF;
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
        if (ql > qr)
            return -INF;
        if (l >= ql && r <= qr)
            return t[id].Max;
        int mid = (l + r) >> 1;
        down(id);
        ll res = -INF;
        if (ql <= mid)
            chmax(res, query(id << 1, l, mid, ql, qr));
        if (qr > mid)
            chmax(res, query(id << 1 | 1, mid + 1, r, ql, qr));
        return res;
    }
} seg;

struct E {
    int x, y, z;
    void scan() {
        rd(x, y, z);
    }
    bool operator<(const E &other) const {
        return x < other.x;
    }
} e[N];

void run() {
    for (int i = 1; i <= n; ++i) rd(a[i].fi, a[i].se);
    for (int i = 1; i <= m; ++i) rd(b[i].fi, b[i].se);
    sort(a + 1, a + 1 + n, [&](pII a, pII b) {
        if (a.se != b.se)
            return a.se < b.se;
        return a.fi > b.fi;
    });
    sort(b + 1, b + 1 + m, [&](pII a, pII b) {
        if (a.se != b.se)
            return a.se < b.se;
        return a.fi > b.fi;
    });
    int cnt = 1;
    for (int i = 2; i <= n; ++i) {
        if (a[i].fi > a[cnt].fi)
            a[++cnt] = a[i];
    }
    n = cnt;
    cnt = 1;
    for (int i = 2; i <= m; ++i) {
        if (b[i].fi > b[cnt].fi)
            b[++cnt] = b[i];
    }
    m = cnt;
    int _n = 1e6;
    seg.build(1, 1, _n);
    for (int i = 1; i <= m; ++i) {
        seg.update(1, 1, _n, b[i].fi, b[i].fi, INF - b[i].se);
    }
    for (int i = 1; i <= p; ++i) e[i].scan();
    sort(e + 1, e + 1 + p);
    int pos = 0;
    ll res = -a[1].se - b[1].se;
    for (int i = 1; i <= n; ++i) {
        while (pos < p && e[pos + 1].x < a[i].fi) {
            ++pos;
            seg.update(1, 1, _n, e[pos].y + 1, _n, e[pos].z);
        }
        chmax(res, -a[i].se + seg.t[1].Max);
    }
    pt(res);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout << fixed << setprecision(20);
    while (cin >> n >> m >> p) run();
    //	while (cin >> n) run();
    //    for (int kase = 1; kase <= _T; ++kase) {
    //        cout << "Case #" << kase << ":\n";
    //        run();
    //    }
    return 0;
}
