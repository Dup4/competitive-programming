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
constexpr int N = 5e3 + 10;
int n, cnt[N];
int res;
struct Trie {
    struct node {
        map<short, int> son;
        int v, f;
        node() {
            son.clear();
            v = f = 0;
        }
    };
    vector<node> t;
    int rt, cnt = 0;
    int newnode() {
        ++cnt;
        t.push_back(node());
        return cnt;
    }
    void init() {
        t.clear();
        t.push_back(node());
        cnt = 0;
        rt = newnode();
    }
    int insert(int rt, int v, int num) {
        if (t[rt].son[v] == 0) {
            t[rt].son[v] = newnode();
        }
        t[t[rt].son[v]].v += num;
        return t[rt].son[v];
    }
    void dfs(int u) {
        chmin(res, t[u].f);
        for (auto &it : t[u].son) {
            int v = it.se;
            t[v].f = t[u].f;
            t[v].f -= t[v].v;
            t[v].f += n - t[v].v;
            dfs(v);
        }
    }
} trie;
void run() {
    vector<vector<int>> pri(N, vector<int>(N, 0));
    for (int i = 2; i < N; ++i) {
        pri[i] = pri[i - 1];
        int tmp = i;
        for (int j = 2; j * j <= tmp; ++j) {
            while (tmp % j == 0) {
                ++pri[i][j];
                tmp /= j;
            }
        }
        if (tmp != 1)
            ++pri[i][tmp];
    }
    for (int i = 1; i <= n; ++i) ++cnt[rd()];
    trie.init();
    res = 0;
    for (int i = 1; i < N; ++i) {
        if (cnt[i]) {
            res += accumulate(pri[i].begin(), pri[i].end(), 0ll) * cnt[i];
            int rt = trie.rt;
            for (int j = i; j >= 2; --j) {
                int tmp = pri[i][j];
                while (tmp--) {
                    rt = trie.insert(rt, j, cnt[i]);
                }
            }
        }
    }
    trie.t[trie.rt].f = res;
    trie.dfs(trie.rt);
    pt(res);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout << fixed << setprecision(20);
    while (cin >> n) run();
    return 0;
}
