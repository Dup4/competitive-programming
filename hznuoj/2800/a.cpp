#include <bits/stdc++.h>
using namespace std;
#define endl "\n"
#define fi first
#define se second
#define SZ(x) ((int)(x).size())
#define mkp make_pair
#define all(x) (x).begin(), (x).end()
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
constexpr int S = 300;
int n, q, a[N], _a[N], _w[N], f[N][20];
ll tot[N];
vector<vector<pII>> G;
pII modify[N];
int szModify;
// vector <pII> modify;

int fa[N], deep[N], dis[N], sze[N], son[N], top[N], in[N], fin[N], out[N];
void dfs(int u) {
    sze[u] = 1;
    son[u] = 0;
    for (auto &it : G[u]) {
        int v = it.fi, w = it.se;
        if (v == fa[u])
            continue;
        _w[v] = w;
        fa[v] = u;
        deep[v] = deep[u] + 1;
        dis[v] = dis[u] + w;
        dfs(v);
        sze[u] += sze[v];
        if (!son[u] || sze[v] > sze[son[u]])
            son[u] = v;
    }
}

void gettop(int u, int tp) {
    in[u] = ++*in;
    fin[*in] = u;
    top[u] = tp;
    if (son[u])
        gettop(son[u], tp);
    for (auto &it : G[u]) {
        int v = it.fi;
        if (v != son[u] && v != fa[u]) {
            gettop(v, v);
        }
    }
    out[u] = *in;
}

void init(int rt) {
    _w[rt] = 0;
    fa[rt] = rt;
    dis[rt] = 0;
    *in = 0;
    dfs(rt);
    gettop(rt, rt);
}

inline bool inSubTree(int u, int v) {
    return in[v] >= in[u] && in[v] <= out[u];
}

inline int finds(int u, int rt) {
    while (top[u] != top[rt]) {
        u = top[u];
        if (fa[u] == rt)
            return u;
        u = fa[u];
    }
    return fin[in[rt] + 1];
}

void dfs1(int u) {
    int *g = f[u];
    for (int i = 0; i < 10; ++i) {
        g[i] = ((a[u] >> i) & 1);
        g[i + 10] = ((a[u] >> (i + 10)) & 1);
    }
    tot[u] = 0;
    for (auto &it : G[u]) {
        int v = it.fi;
        if (v == fa[u])
            continue;
        dfs1(v);
        int *h = f[v];
        for (int i = 0; i < 10; ++i) {
            if ((_w[v] >> i) & 1) {
                tot[u] += (1 << i) * (sze[v] - h[i]);
            } else {
                tot[u] += (1 << i) * h[i];
            }
            if ((_w[v] >> (i + 10)) & 1) {
                tot[u] += (1ll << (i + 10)) * (sze[v] - h[i + 10]);
            } else {
                tot[u] += (1ll << (i + 10)) * h[i + 10];
            }
            g[i] += h[i];
            g[i + 10] += h[i + 10];
        }
    }
    //	for (int i = 0; i < 30; ++i) {
    //		g[i] += ((a[u] >> i) & 1);
    //	//	assert(((a[u] >> i) & 1) <= 1);
    //	}
}

inline void build() {
    for (int i = 1; i <= szModify; ++i) {
        a[modify[i].fi] = _a[modify[i].fi] = modify[i].se;
    }
    //	for (auto &it : modify) {
    //		a[it.fi] = _a[it.fi] = it.se;
    //	}
    //	modify.clear();
    szModify = 0;
    dfs1(1);
    int *all = f[1];
    for (int i = 2; i <= n; ++i) {
        for (int j = 0; j < 10; ++j) {
            int *now = f[i];
            int _tot = n - sze[i];
            if ((_w[i] >> j) & 1) {
                tot[i] += (1 << j) * (_tot - all[j] + now[j]);
            } else {
                tot[i] += (1 << j) * (all[j] - now[j]);
            }
            if ((_w[i] >> (j + 10)) & 1) {
                tot[i] += (1ll << (j + 10)) * (_tot - all[j + 10] + now[j + 10]);
            } else {
                tot[i] += (1ll << (j + 10)) * (all[j + 10] - now[j + 10]);
            }
        }
    }
}

void run() {
    rd(n);
    G.clear();
    G.resize(n + 1);
    for (int i = 1, u, v, w; i < n; ++i) {
        rd(u, v, w);
        //	assert(w < (1 << 30));
        G[u].push_back(pII(v, w));
        G[v].push_back(pII(u, w));
    }
    init(1);
    build();
    rd(q);
    for (int i = 1, op, x, y; i <= q; ++i) {
        rd(op, x);
        if (op == 1) {
            rd(y);
            modify[++szModify] = pII(x, y);
            //	assert(y < (1 << 30));
            //	modify.push_back(pII(x, y));
        } else {
            if (szModify > S)
                build();
            ll res = tot[x];
            for (int i = 1; i <= szModify; ++i) {
                pII it = modify[i];
                int v = it.fi, w = it.se;
                if (v == x)
                    continue;
                if (inSubTree(x, v)) {
                    int nx = finds(v, x);
                    res -= _w[nx] ^ _a[v];
                    _a[v] = w;
                    res += _w[nx] ^ _a[v];
                } else {
                    res -= _w[x] ^ _a[v];
                    _a[v] = w;
                    res += _w[x] ^ _a[v];
                }
            }
            for (int i = 1; i <= szModify; ++i) {
                _a[modify[i].fi] = a[modify[i].fi];
            }
            //	for (auto &it : modify) {
            //		_a[it.fi] = a[it.fi];
            //	}
            pt(res);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout << fixed << setprecision(20);
    int _T = 1;
    while (_T--) run();
    //    for (int kase = 1; kase <= _T; ++kase) {
    //        cout << "Case #" << kase << ": ";
    //        run();
    //    }
    //	while (cin >> n) run();
    //	run();
    return 0;
}
