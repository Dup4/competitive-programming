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
constexpr int N = 3e3 + 10;
int n, fa[N], sze[N];
ll res;
vector<vector<int>> G;
vector<pII> vec;
vector<ll> S;
void pre(int u) {
    sze[u] = 1;
    for (auto &v : G[u])
        if (v != fa[u]) {
            fa[v] = u;
            pre(v);
            sze[u] += sze[v];
        }
}
ll f(ll l, ll r) {
    return r * (r + 1) / 2 - l * (l - 1) / 2;
}
ll calc(ll x, ll y, ll deep) {
    ll res = 0;
    if (x > y)
        swap(x, y);
    if (y - x >= deep) {
        res += f(x, x + deep - 1) * y;
    } else {
        deep -= (y - x);
        res += f(x, y - 1) * y;
        x = y;
        int pos = (y - 1) * 2 + 1;
        int nx = pos + deep - 1;
        res += S[nx];
        res -= S[pos - 1];
    }
    return res;
}
void dfs(int u, int x, int deep) {
    chmax(res, calc(x, sze[u], deep));
    for (auto &v : G[u])
        if (v != fa[u]) {
            dfs(v, x, deep + 1);
        }
}
void run() {
    vec.clear();
    vec.push_back(pII(0, 0));
    S.clear();
    S.push_back(0);
    for (int i = 1; i < N; ++i) {
        vec.push_back(pII(i, i));
        S.push_back(S.back() + 1ll * vec.back().fi * vec.back().se);
        vec.push_back(pII(i, i + 1));
        S.push_back(S.back() + 1ll * vec.back().fi * vec.back().se);
    }
    res = 0;
    G.clear();
    G.resize(n + 1);
    for (int i = 1, u, v; i < n; ++i) {
        cin >> u >> v;
        G[u].push_back(v);
        G[v].push_back(u);
    }
    for (int u = 1; u <= n; ++u) {
        pre(u);
        for (auto &v : G[u]) {
            dfs(v, n - sze[v], 1);
        }
    }
    pt(res);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout << fixed << setprecision(20);
    while (cin >> n) run();
    return 0;
}
