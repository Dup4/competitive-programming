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
int n, m, a[N], b[N], d[N];
ll f[N];
vector<vector<int>> G;
void gao() {
    memset(f, 0, sizeof(f[0]) * (n + 10));
    queue<int> que;
    for (int i = 1; i <= n; ++i)
        if (!d[i])
            que.push(i);
    ll res = 0;
    while (!que.empty()) {
        int u = que.front();
        que.pop();
        chadd(res, 1ll * a[u] * f[u] % mod);
        chadd(f[u], b[u]);
        for (auto &v : G[u]) {
            chadd(f[v], f[u]);
            if (--d[v] == 0)
                que.push(v);
        }
    }
    pt(res);
}
void run() {
    G.clear();
    G.resize(n + 1);
    memset(d, 0, sizeof(d[0]) * (n + 1));
    for (int i = 1; i <= n; ++i) cin >> a[i] >> b[i];
    for (int i = 1, u, v; i <= m; ++i) {
        cin >> u >> v;
        G[v].push_back(u);
        ++d[u];
    }
    gao();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout << fixed << setprecision(20);
    while (cin >> n >> m) run();
    return 0;
}
