#include <bits/stdc++.h>
#define fi first
#define se second
#define endl "\n"
#define SZ(x) ((int)x.size())
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
int n, m, q, vis[1 << 22], cnt[30], G[30];
void run() {
    memset(vis, 0, sizeof vis);
    int ori = 0;
    for (int i = 1, x; i <= n; ++i) {
        G[i] = 0;
        cin >> x;
        if (x)
            ori |= (1 << i);
    }
    for (int i = 1, u, v; i <= m; ++i) {
        cin >> u >> v;
        G[v] |= (1 << u);
    }
    vector<int> maskVec;
    int st = 0;
    while (1) {
        int pre = ori;
        if (vis[pre]) {
            st = vis[pre] - 1;
            break;
        }
        maskVec.push_back(pre);
        vis[pre] = maskVec.size();
        int now = 0;
        for (int i = 1; i <= n; ++i) {
            if (__builtin_popcount(G[i] & pre) & 1) {
                now |= (1 << i);
            }
        }
        ori = now;
    }
    int sze = maskVec.size();
    vector<vector<int>> pre, loop;
    pre.resize(n + 1), loop.resize(n + 1);
    int looplen = maskVec.size() - st;
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j < st; ++j) {
            if ((maskVec[j] >> i) & 1) {
                pre[i].push_back(j);
            }
        }
        for (int j = st; j < sze; ++j) {
            if ((maskVec[j] >> i) & 1) {
                loop[i].push_back(j - st + 1);
            }
        }
    }
    for (int _q = 1; _q <= q; ++_q) {
        int x;
        ll k;
        cin >> x >> k;
        if (k <= SZ(pre[x])) {
            pt(pre[x][k - 1]);
        } else {
            k -= SZ(pre[x]);
            ll res = st - 1;
            if (SZ(loop[x]) == 0) {
                pt(-1);
                continue;
            }
            res += 1ll * looplen * ((k + SZ(loop[x]) - 1) / SZ(loop[x]) - 1);
            k = (k - 1) % SZ(loop[x]) + 1;
            if (k > 0)
                res += loop[x][k - 1];
            pt(res);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout << fixed << setprecision(20);
    while (cin >> n >> m >> q) run();
    return 0;
}
