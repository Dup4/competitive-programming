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
constexpr int N = 2e3 + 10, M = 5e6 + 10;
int n, x[N], y[N], c[N], k[N], ce;
struct E {
    int u, v;
    ll w;
    E() {}
    E(int u, int v, ll w) : u(u), v(v), w(w) {}
    bool operator<(const E &other) const {
        return w < other.w;
    }
} e[M];
inline int dis(int a, int b) {
    return abs(x[a] - x[b]) + abs(y[a] - y[b]);
}
int fa[N];
int find(int x) {
    return fa[x] == x ? x : fa[x] = find(fa[x]);
}
void Kruskal() {
    sort(e + 1, e + 1 + ce);
    ll tot = 0;
    vector<int> vec;
    vector<pII> vec2;
    for (int i = 1; i <= ce; ++i) {
        int u = e[i].u, v = e[i].v;
        ll w = e[i].w;
        int fu = find(u), fv = find(v);
        if (fu == fv)
            continue;
        tot += w;
        fa[fu] = fv;
        if (u == 0)
            vec.push_back(v);
        else
            vec2.push_back(pII(u, v));
    }
    pt(tot);
    pt(vec.size());
    pt(vec);
    pt(vec2.size());
    for (auto &it : vec2) pt(it.fi, it.se);
}
void run() {
    for (int i = 0; i <= n; ++i) fa[i] = i;
    for (int i = 1; i <= n; ++i) x[i] = rd(), y[i] = rd();
    for (int i = 1; i <= n; ++i) c[i] = rd();
    for (int i = 1; i <= n; ++i) k[i] = rd();
    ce = 0;
    for (int i = 1; i <= n; ++i) {
        e[++ce] = E(0, i, c[i]);
        for (int j = 1; j <= n; ++j) {
            e[++ce] = E(i, j, 1ll * dis(i, j) * (k[i] + k[j]));
        }
    }
    Kruskal();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout << fixed << setprecision(20);
    while (cin >> n) run();
    return 0;
}
