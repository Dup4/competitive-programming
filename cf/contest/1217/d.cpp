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
    if (x >= mod)
        x -= mod;
    else if (x < 0)
        x += mod;
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
constexpr int N = 5e3 + 10;
int n, m, c[N], in[N], vis[N], used[N];
vector<vector<pII>> G;
bool loop() {
    queue<int> q;
    for (int i = 1; i <= n; ++i)
        if (!in[i])
            q.push(i);
    int cnt = 0;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        ++cnt;
        for (auto &it : G[u])
            if (--in[it.fi] == 0)
                q.push(it.fi);
    }
    return cnt < n;
}
void DFS(int u) {
    if (vis[u])
        return;
    vis[u] = 1;
    used[u] = 1;
    for (auto &it : G[u]) {
        int v = it.fi, id = it.se;
        if (used[v]) {
            c[id] = 2;
            continue;
        }
        DFS(v);
    }
    used[u] = 0;
}

void run() {
    G.clear();
    G.resize(n + 1);
    memset(in, 0, sizeof in);
    for (int i = 1, u, v; i <= m; ++i) {
        cin >> u >> v;
        G[u].push_back(pII(v, i));
        ++in[v];
    }
    if (!loop()) {
        out(1);
        for (int i = 1; i <= m; ++i) cout << 1 << " \n"[i == m];
    } else {
        memset(vis, 0, sizeof vis);
        memset(used, 0, sizeof used);
        out(2);
        for (int i = 1; i <= m; ++i) c[i] = 1;
        for (int i = 1; i <= n; ++i)
            if (!vis[i]) {
                DFS(i);
            }
        for (int i = 1; i <= m; ++i) cout << c[i] << " \n"[i == m];
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
