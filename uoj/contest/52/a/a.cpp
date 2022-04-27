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
constexpr int mod = 998244353;
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
constexpr int N = 2e3 + 10;
int n, m, _m, pre[150], f[N * N];
char s[N], ss[N * N];

struct node {
    char ch;
    int son[2];
    node() {
        son[0] = son[1] = 0;
    }
} t[N * N];

void dfs(int u) {
    if (!u)
        return;
    dfs(t[u].son[0]);
    ss[++_m] = t[u].ch;
    dfs(t[u].son[1]);
}

void run() {
    rd(n);
    cin >> (s + 1);
    int m = 1;
    t[1].ch = s[1];
    vector<int> vec[2];
    vec[1].push_back(1);
    for (int i = 2; s[i]; ++i) {
        int p = i & 1;
        vec[p].clear();
        for (auto &it : vec[p ^ 1]) {
            ++m;
            t[m].ch = s[i];
            t[it].son[0] = m;
            vec[p].push_back(m);
            ++m;
            t[m].ch = s[i];
            t[it].son[1] = m;
            vec[p].push_back(m);
        }
    }
    _m = 0;
    dfs(1);
    f[0] = 1;
    memset(pre, -1, sizeof pre);
    for (int i = 1; i <= _m; ++i) {
        f[i] = 1ll * f[i - 1] * 2 % mod;
        int ch = ss[i];
        if (pre[ch] != -1) {
            f[i] = (f[i] + mod - f[pre[ch] - 1]) % mod;
        }
        pre[ch] = i;
    }
    pt((mod + f[_m] - 1) % mod);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout << fixed << setprecision(20);
    //	int _T = nextInt();
    //	while (_T--) run();
    //    for (int kase = 1; kase <= _T; ++kase) {
    //        cout << "Case #" << kase << ": ";
    //        run();
    //    }
    //	while (cin >> n) run();
    run();
    return 0;
}
