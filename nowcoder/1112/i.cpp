#include <bits/stdc++.h>
#define debug(...)           \
    {                        \
        printf("#  ");       \
        printf(__VA_ARGS__); \
        puts("");            \
    }
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
inline void pt() {
    cout << endl;
}
template <class T, class... Ts>
void pt(const T &arg, const Ts &...args) {
    cout << arg << " ";
    pt(args...);
}
template <class T>
inline void pt(const T &s) {
    cout << s << "\n";
}
template <class T>
inline void pt(const vector<T> &vec) {
    for (auto &it : vec) cout << it << " ";
    cout << endl;
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
constexpr int N = 1e5 + 10;
int n, c[N], cnt[N][2], ans[N], res;
vector<vector<pII>> G;
int fa[N], sze[N], son[N], son_id[N], big[N];
void dfs(int u) {
    sze[u] = 1;
    son[u] = 0;
    for (auto &it : G[u]) {
        int v = it.fi;
        if (v == fa[u])
            continue;
        fa[v] = u;
        dfs(v);
        sze[u] += sze[v];
        if (!son[u] || sze[v] > sze[son[u]]) {
            son[u] = v;
            son_id[u] = it.se;
        }
    }
}
void add(int u, int f) {
    if (cnt[c[u]][0] && cnt[c[u]][1])
        --res;
    if (f) {
        --cnt[c[u]][0];
        ++cnt[c[u]][1];
    } else {
        ++cnt[c[u]][0];
        --cnt[c[u]][1];
    }
    if (cnt[c[u]][0] && cnt[c[u]][1])
        ++res;
}
void up(int u, int f) {
    add(u, f);
    for (auto &it : G[u]) {
        int v = it.fi;
        if (big[v] || v == fa[u])
            continue;
        up(v, f);
    }
}
void gao(int u, int id) {
    for (auto &it : G[u]) {
        int v = it.fi;
        if (v == fa[u] || v == son[u])
            continue;
        gao(v, it.se);
    }
    if (son[u]) {
        big[son[u]] = 1;
        gao(son[u], son_id[u]);
    }
    for (auto &it : G[u]) {
        int v = it.fi;
        if (v == fa[u] || v == son[u])
            continue;
        up(v, 1);
    }
    add(u, 1);
    ans[id] = res;
    if (son[u])
        big[son[u]] = 0;
    if (!big[u])
        up(u, 0);
}
void run() {
    memset(cnt[0], 0, sizeof(cnt[0]) * (n + 10));
    memset(cnt[1], 0, sizeof(cnt[1]) * (n + 10));
    memset(ans, 0, sizeof(ans[0]) * (n + 10));
    G.clear();
    G.resize(n + 1);
    res = 0;
    for (int i = 1; i <= n; ++i) {
        cin >> c[i];
        ++cnt[c[i]][0];
    }
    for (int i = 1, u, v; i < n; ++i) {
        cin >> u >> v;
        G[u].push_back(pII(v, i));
        G[v].push_back(pII(u, i));
    }
    dfs(1);
    gao(1, 0);
    for (int i = 1; i < n; ++i) pt(ans[i]);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout << fixed << setprecision(20);
    while (cin >> n) run();
    return 0;
}
