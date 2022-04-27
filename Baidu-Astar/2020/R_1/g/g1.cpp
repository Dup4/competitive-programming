#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define SZ(x) ((int)(x).size())
#define mkp make_pair
#define all(x) (x).begin(), (x).end()
#define endl "\n"
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
constexpr int N = 1e3 + 10, INF = 0x3f3f3f3f;
int n, m, k, a[N][N];

struct node {
    int x, y, z;
};

vector<node> vec;

namespace aby {
#define rep(i, j, k) for (int i = (int)(j); i <= (int)(k); i++)
#define per(i, j, k) for (int i = (int)(j); i >= (int)(k); i--)
const int N = 100005;
int head[N], np[N], p[N], flow[N], tot;
int n, S, T;
void init(int node) {
    n = node;
    S = n + 1;
    T = S + 1;
    rep(i, 1, T) head[i] = 0;
    rep(i, 1, tot) np[i] = p[i] = flow[i] = 0;
    tot = 1;
}
void add(int a, int b, int w) {
    ++tot;
    p[tot] = b;
    np[tot] = head[a];
    head[a] = tot;
    flow[tot] = w;
    ++tot;
    p[tot] = a;
    np[tot] = head[b];
    head[b] = tot;
    flow[tot] = 0;
}
int q[N], dis[N];
int bfs() {
    rep(i, 1, T) dis[i] = -1;
    dis[S] = 0;
    q[q[0] = 1] = S;
    rep(i, 1, q[0]) {
        int x = q[i];
        for (int u = head[x]; u; u = np[u])
            if (flow[u])
                if (dis[p[u]] == -1) {
                    dis[p[u]] = dis[x] + 1;
                    q[++q[0]] = p[u];
                }
    }
    return dis[T];
}
int dinic(int x, int fl) {
    if (x == T)
        return fl;
    if (!fl)
        return 0;
    int res = 0;
    for (int u = head[x]; u; u = np[u])
        if (flow[u])
            if (dis[p[u]] == dis[x] + 1) {
                int tmp = dinic(p[u], min(fl, flow[u]));
                fl -= tmp;
                res += tmp;
                flow[u] -= tmp;
                flow[u ^ 1] += tmp;
            }
    if (!res)
        dis[x] = -1;
    return res;
}
int getMaxFlow() {
    int res = 0;
    while (bfs() != -1) res += dinic(S, 1e9);
    return res;
}
};  // namespace aby

int dis(int x, int y, int nx, int ny) {
    return abs(x - nx) + abs(y - ny);
}

bool ok(int ti) {
    aby::init(k + (1 << k));
    vector<int> ln(1 << k);
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            int now = 0;
            for (auto &it : vec) {
                now <<= 1;
                if (dis(i, j, it.x, it.y) <= ti) {
                    now |= 1;
                }
            }
            //		if (!now) return false;
            ++ln[now];
        }
    }
    for (int i = 0; i < SZ(vec); ++i) {
        aby::add(aby::S, i + 1, vec[i].z);
    }
    for (int i = 0; i < SZ(ln); ++i) {
        aby::add(SZ(vec) + i + 1, aby::T, ln[i]);
        for (int j = 0; j < k; ++j)
            if ((i >> j) & 1) {
                aby::add(j + 1, SZ(vec) + i + 1, INF);
            }
    }
    return aby::getMaxFlow() == n * m;
}

void run() {
    rd(n, m, k);
    vec.clear();
    vec.resize(k);
    int tot = 0;
    for (auto &it : vec) rd(it.x, it.y, it.z), tot += it.z;
    if (tot < n * m)
        return pt(-1);
    int l = 0, r = n + m, res = r + 1;
    while (r - l >= 0) {
        int mid = (l + r) >> 1;
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
    while (_T--) run();
    //    for (int kase = 1; kase <= _T; ++kase) {
    //        cout << "Case #" << kase << ": ";
    //        run();
    //    }
    //	while (cin >> n) run();
    //	run();
    return 0;
}
