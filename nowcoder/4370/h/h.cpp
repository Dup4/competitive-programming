#include <bits/stdc++.h>
#define fi first
#define se second
#define SZ(x) int((x).size())
#define endl "\n"
using namespace std;
using db = double;
using ll = long long;
using ull = unsigned long long;
using pII = pair<int, int>;
using pLL = pair<ll, ll>;
constexpr int mod = 1e9 + 7;
template <class T1, class T2>
inline void chadd(T1 &x, T2 y, int Mod = mod) {
    x += y;
    while (x >= Mod) x -= Mod;
    while (x < 0) x += Mod;
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
inline int nextInt() {
    int x;
    cin >> x;
    return x;
}
void rd() {}
template <class T, class... Ts>
void rd(T &arg, Ts &...args) {
    cin >> arg;
    rd(args...);
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
inline ll qpow(ll base, ll n) {
    assert(n >= 0);
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
constexpr int N = 1e5 + 10;
int n, K, w[N];
ll limit;
vector<vector<int>> G;

pLL dfs(int u, int fa) {
    pLL res = pLL(0, w[u]);
    vector<pLL> vec;
    for (auto &v : G[u])
        if (v != fa) {
            vec.push_back(dfs(v, u));
        }
    sort(vec.begin(), vec.end(), [&](pLL x, pLL y) {
        return x.se < y.se;
    });
    for (auto &it : vec) {
        res.fi += it.fi;
        if (res.se + it.se <= limit) {
            res.se += it.se;
        } else {
            ++res.fi;
        }
    }
    return res;
}

bool ok(ll x) {
    limit = x;
    pLL res = dfs(1, 1);
    return (res.fi + 1 <= K);
}

void run() {
    rd(n, K);
    G.clear();
    G.resize(n + 1);
    for (int i = 1, u, v; i < n; ++i) {
        rd(u, v);
        G[u].push_back(v);
        G[v].push_back(u);
    }
    ll l = 0, r = 0;
    for (int i = 1; i <= n; ++i) {
        rd(w[i]);
        chmax(l, w[i]);
        r += w[i];
    }
    ll res = r;
    while (r - l >= 0) {
        ll mid = (l + r) >> 1;
        if (ok(mid)) {
            res = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    pt(res);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout << fixed << setprecision(20);
    int _T = nextInt();
    //	while (_T--) run();
    for (int kase = 1; kase <= _T; ++kase) {
        cout << "Case #" << kase << ": ";
        run();
    }
    //	while (cin >> n) run();
    return 0;
}
