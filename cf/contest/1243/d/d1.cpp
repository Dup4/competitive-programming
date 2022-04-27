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
constexpr int N = 1e5 + 10;
int n, m, tot;
vector<vector<int>> G;
struct UFS {
    int fa[N << 2];
    void init() {
        memset(fa, 0, sizeof fa);
    }
    int find(int x) {
        return fa[x] == 0 ? x : fa[x] = find(fa[x]);
    }
    void merge(int x, int y) {
        int fx = find(x), fy = find(y);
        if (fx != fy) {
            fa[fx] = fy;
        }
    }
    bool same(int x, int y) {
        return find(x) == find(y);
    }
} ufs;

struct SEG {
    int t[N << 2];
    void build(int id, int l, int r) {
        if (l == r) {
            t[id] = l;
            return;
        }
        t[id] = ++tot;
        int mid = (l + r) >> 1;
        build(id << 1, l, mid);
        build(id << 1 | 1, mid + 1, r);
    }
    void add(int id, int l, int r, int ql, int qr, int x) {
        if (ql > qr)
            return;
        if (l >= ql && r <= qr) {
            ufs.merge(t[id], x);
            if (l == r)
                return;
            else if (ufs.same(t[id], t[id << 1]) && ufs.same(t[id], t[id << 1 | 1]))
                return;
        }
        int mid = (l + r) >> 1;
        if (ql <= mid)
            add(id << 1, l, mid, ql, qr, x);
        if (qr > mid)
            add(id << 1 | 1, mid + 1, r, ql, qr, x);
    }
} seg;

void run() {
    tot = n;
    ufs.init();
    seg.build(1, 1, n);
    G.clear();
    G.resize(n + 1);
    for (int i = 1, u, v; i <= m; ++i) {
        cin >> u >> v;
        G[u].push_back(v);
        G[v].push_back(u);
    }
    for (int u = 1; u <= n; ++u) {
        int pre = 0;
        sort(G[u].begin(), G[u].end());
        for (auto &v : G[u]) {
            seg.add(1, 1, n, pre + 1, v - 1, u);
            pre = v;
        }
        seg.add(1, 1, n, pre + 1, n, u);
    }
    set<int> se;
    for (int i = 1; i <= n; ++i) se.insert(ufs.find(i));
    pt(se.size() - 1);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout << fixed << setprecision(20);
    while (cin >> n >> m) run();
    return 0;
}
