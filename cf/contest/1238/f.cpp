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
constexpr int N = 3e5 + 10;
int n, f[N], rt, res;
vector<vector<int>> G;
void dfs(int u, int fa) {
    int Max[2] = {0, 0};
    int sons = 0;
    for (auto &v : G[u]) {
        if (v == fa)
            continue;
        ++sons;
        dfs(v, u);
        if (f[v] > Max[0]) {
            swap(Max[0], Max[1]);
            Max[0] = f[v];
        } else if (f[v] > Max[1])
            Max[1] = f[v];
    }
    if (u != rt) {
        f[u] = Max[0] + 1 + max(0, sons - 1);
        chmax(res, Max[0] + Max[1] + 1 + max(0, sons - 1));
    } else {
        f[u] = Max[0] + Max[1] + 1 + max(0, sons - 2);
        chmax(res, f[u]);
    }
}
void run() {
    cin >> n;
    memset(f, 0, sizeof(f[0]) * (n + 10));
    G.clear();
    G.resize(n + 1);
    for (int i = 1, u, v; i < n; ++i) {
        cin >> u >> v;
        G[u].push_back(v);
        G[v].push_back(u);
    }
    rt = 1;
    res = 0;
    for (int i = 2; i <= n; ++i) {
        if (G[i].size() > 1) {
            rt = i;
            break;
        }
    }
    dfs(rt, rt);
    pt(res);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout << fixed << setprecision(20);
    int _T;
    cin >> _T;
    while (_T--) run();
    return 0;
}
