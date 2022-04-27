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
int n, m, k;

struct node {
    int x, y, z;
};

vector<node> vec;

template <class Type>
struct Dinic {
    static const int M = 1e3 + 10;
    static const int N = 1e3 + 10;
    struct Edge {
        int to, nxt;
        Type flow;
        Edge() {}
        Edge(int to, int nxt, Type flow) : to(to), nxt(nxt), flow(flow) {}
    } edge[M];
    int S, T;
    int head[N], tot;
    int dep[N];
    void init() {
        memset(head, -1, sizeof head);
        tot = 0;
    }
    void set(int S, int T) {
        this->S = S;
        this->T = T;
    }
    void addedge(int u, int v, Type w, Type rw = 0) {
        edge[tot] = Edge(v, head[u], w);
        head[u] = tot++;
        edge[tot] = Edge(u, head[v], rw);
        head[v] = tot++;
    }
    bool BFS() {
        memset(dep, -1, sizeof dep);
        queue<int> q;
        q.push(S);
        dep[S] = 1;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int i = head[u]; ~i; i = edge[i].nxt) {
                if (edge[i].flow && dep[edge[i].to] == -1) {
                    dep[edge[i].to] = dep[u] + 1;
                    q.push(edge[i].to);
                }
            }
        }
        return dep[T] >= 0;
    }
    Type DFS(int u, Type f) {
        if (u == T || f == 0)
            return f;
        Type w, used = 0;
        for (int i = head[u]; ~i; i = edge[i].nxt) {
            if (edge[i].flow && dep[edge[i].to] == dep[u] + 1) {
                w = DFS(edge[i].to, min(f - used, edge[i].flow));
                edge[i].flow -= w;
                edge[i ^ 1].flow += w;
                used += w;
                if (used == f)
                    return f;
            }
        }
        if (!used)
            dep[u] = -1;
        return used;
    }
    Type solve() {
        Type ans = 0;
        while (BFS()) {
            ans += DFS(S, INF);
        }
        return ans;
    }
};
Dinic<int> dinic;

int dis(int x, int y, int nx, int ny) {
    return abs(x - nx) + abs(y - ny);
}

bool ok(int ti) {
    vector<int> ln(1 << k);
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            int now = 0;
            int ix = 0;
            for (auto &it : vec) {
                if (dis(i, j, it.x, it.y) <= ti) {
                    now |= (1 << ix);
                }
                ++ix;
            }
            if (!now)
                return false;
            ++ln[now];
        }
    }
    int S = 1, T = 2;
    dinic.init();
    dinic.set(S, T);
    for (int i = 0; i < k; ++i) {
        dinic.addedge(S, T + i + 1, vec[i].z);
    }
    int tot = T + k;
    for (int i = 0; i < 1 << k; ++i)
        if (ln[i]) {
            int no = tot + i + 1;
            dinic.addedge(no, T, ln[i]);
            for (int j = 0; j < k; ++j)
                if ((i >> j) & 1) {
                    dinic.addedge(T + j + 1, no, ln[i]);
                }
        }
    return dinic.solve() == n * m;
}

void run() {
    rd(n, m, k);
    vec.clear();
    vec.resize(k);
    int tot = 0;
    for (auto &it : vec) rd(it.x, it.y, it.z), tot += it.z;
    if (tot < n * m)
        return pt(-1);
    int l = 0, r = n + m, res = r;
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
    return 0;
}
