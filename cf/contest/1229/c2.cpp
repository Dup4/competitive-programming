#include <bits/stdc++.h>
using namespace std;
#define debug(...)           \
    {                        \
        printf("#  ");       \
        printf(__VA_ARGS__); \
        puts("");            \
    }
#define fi first
#define se second
#define endl "\n"
using ll = long long;
using pII = pair<int, int>;
using pLL = pair<ll, ll>;
using VI = vector<int>;
using VL = vector<ll>;
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
template <class T>
inline void out(T s) {
    cout << s << "\n";
}
template <class T>
inline void out(vector<T> &vec) {
    for (auto &it : vec) cout << it << " ";
    cout << endl;
}
inline ll gcd(ll a, ll b) {
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
int n, m, q, d[N];
vector<vector<int>> G;
inline ll f(int x) {
    return 1ll * G[x].size() * (d[x] - G[x].size());
}
void run() {
    memset(d, 0, sizeof d);
    G.clear();
    G.resize(n + 1);
    for (int i = 1, u, v; i <= m; ++i) {
        cin >> u >> v;
        if (u > v)
            swap(u, v);
        G[u].push_back(v);
        ++d[u];
        ++d[v];
    }
    ll res = 0;
    for (int i = 1; i <= n; ++i) res += f(i);
    cin >> q;
    cout << res << endl;
    for (int i = 1, u; i <= q; ++i) {
        cin >> u;
        res -= f(u);
        for (auto &v : G[u]) {
            res -= f(v);
            G[v].push_back(u);
            res += f(v);
        }
        G[u].clear();
        cout << res << endl;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout << fixed << setprecision(20);
    while (cin >> n >> m) run();
    return 0;
}
