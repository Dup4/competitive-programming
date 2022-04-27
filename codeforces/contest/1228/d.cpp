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
constexpr int N = 3e5 + 10;
int n, m, ans[N], d[N];
mt19937 rnd(time(0));
ull f[N], g[N];
map<ull, vector<int>> mp;
void run() {
    for (int i = 1; i <= n; ++i) f[i] = rnd();
    memset(d, 0, sizeof d);
    memset(g, 0, sizeof g);
    mp.clear();
    for (int i = 1, u, v; i <= m; ++i) {
        cin >> u >> v;
        ++d[u];
        ++d[v];
        g[u] ^= f[v];
        g[v] ^= f[u];
    }
    for (int i = 1; i <= n; ++i) {
        if (!d[i])
            return out(-1);
        mp[g[i]].push_back(i);
        if (mp.size() > 3)
            return out(-1);
    }
    if (mp.size() != 3)
        return out(-1);
    int cnt = 0;
    for (auto &it : mp) {
        ++cnt;
        for (auto &u : it.second) {
            ans[u] = cnt;
        }
    }
    for (int i = 1; i <= n; ++i) cout << ans[i] << " \n"[i == n];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout << fixed << setprecision(20);
    while (cin >> n >> m) run();
    return 0;
}
