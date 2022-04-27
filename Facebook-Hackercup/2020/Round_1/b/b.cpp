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
constexpr int N = 1e6 + 10;
constexpr ll INFLL = 0x3f3f3f3f3f3f3f3f;
int n, m, k, s, h[N], vis[N];
ll P[N], Q[N], f[N][2], g[N];
pII pos[N];

inline ll dis(ll x, ll y) {
    return abs(x - y);
}

void getPos() {
    int l = 0, r = 1;
    g[0] = 0;
    for (int i = 1; i <= m; ++i) h[i] = 0, vis[i] = 0;
    for (int i = 1; i <= n; ++i) {
        while (l < m && Q[l + 1] < P[i]) ++l;
        while (r <= m && Q[r] < P[i]) ++r;
        pos[i] = pII(l, r);
        if (l)
            vis[l] = 1;
        if (r <= m)
            vis[r] = 1, h[r] = i;
    }
}

void input(ll *arr, int n) {
    for (int i = 1; i <= k; ++i) rd(arr[i]);
    ll A, B, C, D;
    rd(A, B, C, D);
    for (int i = k + 1; i <= n; ++i) {
        arr[i] = ((A * arr[i - 2] % D + B * arr[i - 1] % D + C) % D) + 1;
    }
}

void run() {
    rd(m, n, k, s);
    input(Q, m);
    input(P, n);
    sort(P + 1, P + 1 + n);
    sort(Q + 1, Q + 1 + m);
    getPos();
    int _n = 0;
    for (int i = 1; i <= n; ++i) {
        if (pos[i].se <= m && P[i] != Q[pos[i].se]) {
            P[++_n] = P[i], pos[_n] = pos[i];
        }
    }
    //	dbg(n, _n);
    n = _n;
    if (!n)
        return pt(0);
    int _m = 0;
    for (int i = 1; i <= m; ++i) {
        if (vis[i]) {
            Q[++_m] = Q[i];
            h[_m] = h[i];
        }
    }
    m = _m;
    getPos();
    for (int i = 1; i <= n; ++i) f[i][0] = f[i][1] = INFLL, g[i] = INFLL;
    //	for (int i = 1; i <= n; ++i) dbg(i, pos[i].fi, pos[i].se);
    if (pos[1].fi > 0)
        f[1][0] = dis(P[1], Q[pos[1].fi]);
    if (pos[1].se <= m)
        g[1] = f[1][1] = dis(P[1], Q[pos[1].se]);
    //	dbg(f[1][0], f[1][1]);
    for (int i = 2; i <= n; ++i) {
        if (pos[i].fi > 0) {
            ll fee = dis(P[i], Q[pos[i].fi]);
            if (pos[i].fi == pos[i - 1].fi) {
                int _p = h[pos[i].fi];
                chmin(f[i][0], max(fee, f[i - 1][0]));
                //	if (_p) chmin(f[i][0], max(f[_p][0], fee));
                //	if (_p) chmin(f[i][0], max(f[_p][1], min(g[_p], fee) + g[_p] + fee));
            } else if (pos[i].fi == pos[i - 1].se) {
                chmin(f[i][0], max(fee, f[i - 1][0]));
                chmin(f[i][0], max(f[i - 1][1], min(fee, g[i - 1]) + fee + g[i - 1]));
            } else {
                chmin(f[i][0], max(fee, min(f[i - 1][0], f[i - 1][1])));
            }
        }
        if (pos[i].se <= m) {
            ll fee = dis(P[i], Q[pos[i].se]);
            if (pos[i].se == pos[i - 1].se) {
                if (f[i - 1][1] < max(f[i - 1][0], fee)) {
                    chmin(f[i][1], f[i - 1][1]);
                    g[i] = g[i - 1];
                } else {
                    chmin(f[i][1], max(f[i - 1][0], fee));
                    g[i] = fee;
                }
            } else {
                chmin(f[i][1], max(fee, min(f[i - 1][0], f[i - 1][1])));
                g[i] = fee;
            }
        }
    }
    //	dbg(f[n][0], f[n][1]);
    pt(min(f[n][0], f[n][1]));
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
    //	run();
    return 0;
}
