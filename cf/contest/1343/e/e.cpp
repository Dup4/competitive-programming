#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define SZ(x) int((x).size())
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
constexpr int N = 2e5 + 10, INF = 1e9;
const ll INFLL = 1e18;
int n, m, a, b, c, MinAB;
ll p[N];

struct Graph {
    struct E {
        int to, nx, w;
    } e[N << 1];
    int h[N], cnt;
    void init(int n) {
        for (int i = 0; i <= n; ++i) h[i] = -1;
        cnt = -1;
    }
    void addedge(int u, int v, int w = 0) {
        e[++cnt] = {v, h[u], w};
        h[u] = cnt;
    }
} G;

struct Dijkstra {
    struct node {
        int u, w, a, b;
        node(int u = 0, int w = 0, int a = 0, int b = 0) : u(u), w(w), a(a), b(b) {}
        bool operator<(const node &other) const {
            return w > other.w;
        }
    };
    int dis[N];
    bool used[N];
    void gao(int s) {
        for (int i = 1; i <= n; ++i) {
            dis[i] = INF;
            used[i] = 0;
        }
        priority_queue<node> pq;
        dis[s] = 0;
        pq.push(node(s, dis[s]));
        while (!pq.empty()) {
            int u = pq.top().u;
            pq.pop();
            if (used[u])
                continue;
            used[u] = 1;
            for (int i = G.h[u]; ~i; i = G.e[i].nx) {
                int v = G.e[i].to;
                if (dis[v] > dis[u] + 1) {
                    dis[v] = dis[u] + 1;
                    pq.push(node(v, dis[v]));
                }
            }
        }
    }
} f, g, h;

ll get(int l, int r) {
    if (l > r)
        return 0;
    if (l > m || r > m)
        return INFLL;
    //	chmin(r, m);
    //	chmin(l, m);
    return p[r] - p[l - 1];
}

void run() {
    rd(n, m, a, b, c);
    for (int i = 1; i <= m; ++i) rd(p[i]);
    sort(p + 1, p + 1 + m);
    for (int i = 1; i <= m; ++i) p[i] += p[i - 1];
    G.init(n);
    for (int i = 1, u, v; i <= m; ++i) {
        rd(u, v);
        G.addedge(u, v);
        G.addedge(v, u);
    }
    f.gao(a);
    g.gao(b);
    h.gao(c);
    MinAB = f.dis[b];
    ll res = INFLL;
    for (int i = 1; i <= n; ++i) {
        int Min = f.dis[i] + g.dis[i];
        chmin(res, get(1, g.dis[i]) + get(Min + 1, Min + h.dis[i]) + get(1, Min));
        //		if (f.dis[i] + g.dis[i] == MinAB) {
        //		dbg(i, h.dis[i]);
        //			chmin(res, get(1, g.dis[i]) + get(MinAB + 1, MinAB + h.dis[i]));
        //		}
    }
    //	res += get(1, MinAB);
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
