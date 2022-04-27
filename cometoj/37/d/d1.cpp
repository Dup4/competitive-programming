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
constexpr int mod = 998244353;
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
constexpr int N = 2e3 + 10;
int n, cnt[N][N], S[N][N], bit[N], ans[N];
vector<vector<int>> G;
void dfs(int u, int fa, int deep, int *a) {
    ++a[deep];
    for (auto &v : G[u])
        if (v != fa) {
            dfs(v, u, deep + 1, a);
        }
}

void clear(int u) {
    memset(cnt[u], 0, sizeof cnt[u]);
}
void get(int u) {
    S[u][0] = cnt[u][0];
    for (int i = 1; i <= n; ++i) {
        S[u][i] = (S[u][i - 1] + cnt[u][i]) % mod;
    }
}

void run() {
    G.clear();
    G.resize(n + 1);
    for (int i = 1, u, v; i < n; ++i) {
        cin >> u >> v;
        G[u].push_back(v);
        G[v].push_back(u);
    }
    memset(ans, 0, sizeof ans);
    for (int u = 1; u <= n; ++u) {
        clear(u);
        dfs(u, u, 0, cnt[u]);
        get(u);
        for (auto &v : G[u]) {
            clear(v);
            dfs(v, u, 1, cnt[v]);
            get(v);
        }
        for (int i = 2; i <= n; i += 2) {
            int tmp = bit[S[u][i / 2 - 1]];
            int tot = (bit[cnt[u][i / 2]] - 1 + mod) % mod;
            for (auto &v : G[u]) {
                chadd(tot, mod - bit[cnt[v][i / 2]] + 1);
            }
            chadd(ans[i], 1ll * tmp * tot % mod);
        }
    }
    for (int u = 1; u <= n; ++u) {
        for (auto &v : G[u])
            if (u < v) {
                clear(u);
                clear(v);
                dfs(u, v, 0, cnt[u]);
                dfs(v, u, 0, cnt[v]);
                get(u);
                get(v);
                for (int i = 1; i <= n; i += 2) {
                    int tmp = 1ll * (bit[cnt[u][i / 2]] - 1) * (bit[cnt[v][i / 2]] - 1) % mod;
                    if (i / 2) {
                        tmp = 1ll * tmp * bit[S[u][i / 2 - 1] + S[v][i / 2 - 1]] % mod;
                    }
                    chadd(ans[i], tmp);
                }
            }
    }
    for (int i = 1; i < n; ++i) pt(ans[i]);
}

int main() {
    bit[0] = 1;
    for (int i = 1; i < N; ++i) bit[i] = (bit[i - 1] << 1) % mod;
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout << fixed << setprecision(20);
    while (cin >> n) run();
    return 0;
}
