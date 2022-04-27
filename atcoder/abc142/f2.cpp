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
    for (auto &it : vec) cout << it << endl;
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
int n, m;
vector<vector<int>> G;
int sta[N], vis[N], use[N], d_in[N], d_out[N];
bool Insta[N];
void check(vector<int> &vec) {
    for (auto &it : vec) d_in[it] = d_out[it] = 0, use[it] = 1;
    for (auto &u : vec) {
        for (auto &v : G[u]) {
            if (use[v])
                ++d_out[u], ++d_in[v];
        }
    }
    for (auto &u : vec)
        if (d_in[u] != 1 || d_out[u] != 1) {
            for (auto &it : vec) use[it] = 0;
            return;
        }
    out(vec.size());
    out(vec);
    exit(0);
}
void Tarjan(int u) {
    vis[u] = 1;
    sta[++*sta] = u;
    Insta[u] = true;
    for (auto &v : G[u]) {
        if (!Insta[v]) {
            Tarjan(v);
        } else {
            vector<int> vec;
            for (int i = *sta; i >= 1; --i) {
                vec.push_back(sta[i]);
                if (sta[i] == v)
                    break;
            }
            check(vec);
        }
    }
    (*sta)--;
    Insta[u] = false;
}

void run() {
    G.clear();
    G.resize(n + 1);
    for (int i = 1, u, v; i <= m; ++i) {
        cin >> u >> v;
        G[u].push_back(v);
    }
    memset(vis, 0, sizeof vis);
    memset(use, 0, sizeof use);
    for (int i = 1; i <= n; ++i) {
        if (!vis[i]) {
            *sta = 0;
            Tarjan(i);
        }
    }
    out(-1);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout << fixed << setprecision(20);
    while (cin >> n >> m) run();
    return 0;
}
