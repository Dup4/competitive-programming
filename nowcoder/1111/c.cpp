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
using ull = unsigned long long;
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
inline void pt(T s) {
    cout << s << "\n";
}
template <class T>
inline void pt(vector<T> &vec) {
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
constexpr int INF = 0x3f3f3f3f;
int n, m, limit, vis[N], use[N], ok;
vector<vector<pII>> G;
void dfs(int u, int cnt, int fee) {
    if (fee + (n - cnt) > limit)
        return;
    if (cnt == n) {
        ok = 1;
        return;
    }
    for (auto &it : G[u]) {
        int v = it.fi, w = it.se;
        if (vis[v] || fee + w > limit)
            continue;
        vis[v] = 1;
        dfs(v, cnt + 1, fee + w);
        vis[v] = 0;
        if (ok)
            return;
    }
}
bool check(int _limit, int rt) {
    ok = 0;
    limit = _limit;
    vis[rt] = 1;
    dfs(rt, 1, 0);
    vis[rt] = 0;
    return ok;
}
void run() {
    G.clear();
    G.resize(n + 1);
    for (int i = 1, u, v, w; i <= m; ++i) {
        cin >> u >> v >> w;
        G[u].push_back(pII(v, w));
    }
    int lst = INF;
    for (int i = 1; i <= n; ++i) {
        int l = n - 1, r = lst, res = lst;
        while (r - l >= 0) {
            int mid = (l + r) >> 1;
            if (check(mid, i)) {
                res = mid;
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }
        lst = res;
        if (lst == n - 1)
            break;
    }
    if (lst == INF)
        lst = -1;
    pt(lst);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout << fixed << setprecision(20);
    while (cin >> n >> m) run();
    return 0;
}
