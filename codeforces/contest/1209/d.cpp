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
int n, k, res, vis[N][2], x[N][2], use[N];
vector<vector<int>> G;
void DFS(int u) {
    if (vis[u][0])
        return;
    vis[u][0] = 1;
    for (auto &v : G[u])
        if (!vis[v][1]) {
            int a = x[v][0], b = x[v][1];
            if (!use[a] || !use[b])
                ++res;
            use[a] = use[b] = 1;
        }
    for (auto &v : G[u])
        if (!vis[v][1]) {
            vis[v][1] = 1;
            int a = x[v][0], b = x[v][1];
            if (!vis[a][0])
                DFS(a);
            if (!vis[b][0])
                DFS(b);
        }
}
void run() {
    G.clear();
    G.resize(n + 1);
    for (int i = 1; i <= k; ++i) {
        cin >> x[i][0] >> x[i][1];
        G[x[i][0]].push_back(i);
        G[x[i][1]].push_back(i);
    }
    memset(vis, 0, sizeof vis);
    memset(use, 0, sizeof use);
    res = 0;
    for (int i = 1; i <= n; ++i) {
        if (!vis[i][0])
            DFS(i);
    }
    cout << k - res << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout << fixed << setprecision(20);
    while (cin >> n >> k) run();
    return 0;
}
