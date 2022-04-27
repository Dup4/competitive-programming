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
int n, m, d[N], del[N], e[N][2], g[N][N], dis[N], pre[N];
vector<vector<int>> G;

void addG() {
    memset(d, 0, sizeof d);
    memset(g, 0, sizeof g);
    G.clear();
    G.resize(n + 1);
    for (int j = 1, u, v; j <= m; ++j) {
        u = e[j][0], v = e[j][1];
        if (del[u] == 0 && del[v] == 0) {
            g[u][v] = g[v][u] = 1;
            ++d[u];
            ++d[v];
            G[u].push_back(v);
            G[v].push_back(u);
        }
    }
}

bool gao(int x, vector<int> &vec) {
    addG();
    vector<int> two;
    for (int i = 1; i <= n; ++i) {
        if (del[i] == 0 && d[i] == 2) {
            two.push_back(i);
        }
    }
    if (two.empty() || two.size() != 4)
        return false;
    queue<int> que;
    memset(dis, 0x3f, sizeof dis);
    dis[two[0]] = 0;
    pre[two[0]] = -1;
    que.push(two[0]);
    while (!que.empty()) {
        int u = que.front();
        que.pop();
        for (auto &v : G[u]) {
            if (dis[v] > dis[u] + 1) {
                dis[v] = dis[u] + 1;
                pre[v] = u;
                que.push(v);
            }
        }
    }
    for (int i = 1, sze = two.size(); i < sze; ++i) {
        if (dis[two[i]] == x - 1) {
            vec.clear();
            vec.push_back(two[i]);
            int it = pre[two[i]];
            while (it != two[0]) {
                vec.push_back(it);
                it = pre[it];
            }
            vec.push_back(two[0]);
            return true;
        }
    }
    return false;
}

bool ok(int x, int y) {
    if (x > y)
        swap(x, y);
    memset(del, 0, sizeof del);
    if (x == 1) {
        for (int i = 1; i < y; ++i) {
            addG();
            vector<int> vec;
            for (int i = 1; i <= n; ++i) {
                if (del[i] == 0 && d[i] == 1) {
                    vec.push_back(i);
                }
                if (del[i] == 0 && del[i] > 2)
                    return false;
            }
            if (vec.size() == 2) {
                del[vec[0]] = 1;
            } else {
                return false;
            }
        }
        return true;
    }
    vector<int> vec;
    if (gao(x, vec) == false)
        return false;
    for (int i = 1; i <= y; ++i) {
        addG();
        vector<int> tmp;
        int sze = vec.size();
        for (int j = 0; j < sze; ++j) del[vec[j]] = 1;
        for (int j = 0; j < sze; ++j) {
            if (j && g[vec[j - 1]][vec[j]] == 0)
                return false;
            if (i < y) {
                if (j && j < sze - 1 && d[vec[j]] != 3)
                    return false;
                if ((j == 0 || j == sze - 1) && d[vec[j]] != 2)
                    return false;
                for (auto &v : G[vec[j]])
                    if (del[v] == 0)
                        tmp.push_back(v);
            }
        }
        if (i < y && tmp.size() != vec.size())
            return false;
        vec = tmp;
    }
    return true;
}

void run() {
    cin >> n >> m;
    for (int i = 1; i <= m; ++i) {
        cin >> e[i][0] >> e[i][1];
    }
    for (int i = 1; i <= n; ++i) {
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
