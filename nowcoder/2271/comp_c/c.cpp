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
constexpr int N = 1e5 + 10;
struct BIT {
    int a[N];
    void init() {
        memset(a, 0, sizeof a);
    }
    void update(int x, int v) {
        for (; x < N; x += x & -x) a[x] += v;
    }
    int query(int x) {
        int res = 0;
        for (; x > 0; x -= x & -x) res += a[x];
        return res;
    }
    int query(int l, int r) {
        if (l > r)
            return 0;
        return query(r) - query(l - 1);
    }
} bit;

struct Hash {
    vector<int> a;
    void init() {
        a.clear();
    }
    void add(int x) {
        a.push_back(x);
    }
    void gao() {
        sort(a.begin(), a.end());
        a.erase(unique(a.begin(), a.end()), a.end());
    }
    int get(int x) {
        return lower_bound(a.begin(), a.end(), x) - a.begin() + 1;
    }
} hx, hy;

int n, D, L, x[N], y[N];
struct E {
    int x[2], y[2];
    E() {}
    E(int x0, int x1, int y0, int y1) {
        hx.add(x0);
        hx.add(x1);
        hy.add(y0);
        hy.add(y1);
        x[0] = x0;
        x[1] = x1;
        y[0] = y0;
        y[1] = y1;
    }
};

struct W {
    int op, x, y;
    W() {}
    W(int op, int x, int y) : op(op), x(x), y(y) {}
};

void run() {
    ll res = 1ll * n * n;
    hx.init(), hy.init();
    bit.init();
    vector<E> vecE;
    vector<vector<W>> add, query;
    for (int i = 1, a, b; i <= n; ++i) {
        a = rd(), b = rd();
        x[i] = a + b;
        y[i] = a - b;
        hx.add(x[i]);
        hy.add(y[i]);
        if (x[i] - D + 1 > x[i] + D - 1 || y[i] - D + 1 > y[i] + D - 1) {
            --res;
            continue;
        }
        vecE.push_back(E(x[i] - D + 1, x[i] + D - 1, y[i] - D + 1, y[i] + D - 1));
    }
    hx.gao();
    hy.gao();
    int m = hx.a.size();
    add.resize(m + 10);
    query.resize(m + 10);
    for (int i = 1; i <= n; ++i) {
        add[hx.get(x[i])].push_back(W(0, hy.get(y[i]), 0));
    }
    for (auto &it : vecE) {
        for (int i = 0; i < 2; ++i) {
            it.x[i] = hx.get(it.x[i]);
            it.y[i] = hy.get(it.y[i]);
        }
        query[it.x[0] - 1].push_back(W(1, it.y[0], it.y[1]));
        query[it.x[1]].push_back(W(-1, it.y[0], it.y[1]));
    }
    for (int i = 1; i <= m; ++i) {
        for (auto &it : add[i]) {
            bit.update(it.x, 1);
        }
        for (auto &it : query[i]) {
            res += 1ll * it.op * bit.query(it.x, it.y);
        }
    }
    assert(res % 2 == 0);
    pt(res / 2);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout << fixed << setprecision(20);
    while (cin >> n >> D >> L) run();
    return 0;
}
