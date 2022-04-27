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
const int N = 1e2 + 10;
int n, m, d[N], del[N], e[N][2], dis[N], pre[N];
vector<vector<int>> G;

struct UFS {
    int fa[N];
    void init() {
        memset(fa, 0, sizeof fa);
    }
    int find(int x) {
        return fa[x] == 0 ? x : fa[x] = find(fa[x]);
    }
    void join(int x, int y) {
        int fx = find(x), fy = find(y);
        if (fx != fy) {
            fa[fx] = fy;
        }
    }
} ufs;

bool connect() {
    ufs.init();
    for (int u = 1; u <= n; ++u) {
        if (del[u] == 0) {
            for (auto &v : G[u]) {
                ufs.join(u, v);
            }
        }
    }
    int cnt = 0;
    for (int i = 1; i <= n; ++i) {
        if (del[i] == 0 && ufs.fa[i] == 0)
            ++cnt;
    }
    return cnt == 1;
}

bool okdu(int x, int y) {
    int cnt[10] = {0}, tot = 0;
    for (int i = 1; i <= n; ++i) {
        if (del[i] == 0)
            ++cnt[d[i]], ++tot;
    }
    if (tot != x * y)
        return false;
    if (x == 1) {
        return cnt[1] == 2 && cnt[2] == tot - 2;
    } else {
        return cnt[2] == 4 && cnt[3] == 2 * (x + y) - 8 && cnt[4] == x * y - 2 * (x + y) + 4;
    }
}

bool gao(int x, int y) {
    memset(d, 0, sizeof d);
    G.clear();
    G.resize(n + 1);
    for (int i = 1; i <= m; ++i) {
        int u = e[i][0], v = e[i][1];
        if (del[u] == 0 && del[v] == 0) {
            ++d[u];
            ++d[v];
            G[u].push_back(v);
            G[v].push_back(u);
        }
    }
    if (!okdu(x, y)) {
        return false;
    }
    if (!connect()) {
        return false;
    }
    if (x == 1) {
        for (int i = 1; i <= n; ++i) {
            if (del[i] == 0 && d[i] == 1) {
                del[i] = 1;
                return true;
            }
        }
    } else {
        vector<int> two;
        for (int i = 1; i <= n; ++i) {
            if (del[i] == 0 && d[i] == 2) {
                two.push_back(i);
            }
        }
        if (two.empty() || two.size() > 4)
            return false;
        queue<pII> que;
        memset(dis, 0x3f, sizeof dis);
        dis[two[0]] = 0;
        pre[two[0]] = -1;
        que.push(pII(two[0], 0));
        while (!que.empty()) {
            pII u = que.front();
            que.pop();
            for (auto &v : G[u.fi]) {
                if (dis[v] > dis[u.fi] + 1) {
                    dis[v] = dis[u.fi] + 1;
                    pre[v] = u.fi;
                    que.push(pII(v, dis[v]));
                }
            }
        }
        for (int i = 1, sze = two.size(); i < sze; ++i) {
            if (dis[two[i]] == x - 1) {
                int it = pre[two[i]];
                del[two[0]] = 1;
                del[two[i]] = 1;
                while (it != two[0]) {
                    if (d[it] != 3)
                        return false;
                    del[it] = 1;
                    it = pre[it];
                }
                for (auto &u : {two[0], two[i]}) {
                    for (auto &v : G[u]) {
                        if (del[v] == 0) {
                            if (y == 2 && d[v] != 2)
                                return false;
                            if (y > 2 && d[v] != 3)
                                return false;
                        }
                    }
                }
                return true;
            }
        }
    }
    return false;
}

bool ok(int x, int y) {
    memset(del, 0, sizeof del);
    int tot = x * y;
    while (1) {
        if (tot == 1)
            return true;
        if (x > y)
            swap(x, y);
        if (gao(x, y) == false)
            return false;
        tot -= x;
        --y;
    }
    return false;
}

void run() {
    cin >> n >> m;
    for (int i = 1; i <= m; ++i) {
        cin >> e[i][0] >> e[i][1];
    }
    for (int i = 1; i * i <= n; ++i) {
        if (n % i == 0) {
            if (ok(i, n / i)) {
                return pt("Shi");
            }
        }
    }
    pt("Fou");
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout << fixed << setprecision(20);
    int _T = rd();
    while (_T--) run();
    return 0;
}
