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
constexpr int N = 4e6 + 10;
int h, g, n, m, b[N];

void dfs(int rt) {
    int ls = rt << 1;
    int rs = rt << 1 | 1;
    if (!b[ls] && !b[rs]) {
        b[rt] = 0;
    } else {
        if (b[ls] > b[rs]) {
            b[rt] = b[ls];
            dfs(ls);
        } else {
            b[rt] = b[rs];
            dfs(rs);
        }
    }
}

int tmp;
void dfs1(int rt) {
    int ls = rt << 1;
    int rs = rt << 1 | 1;
    if (!b[ls] && !b[rs]) {
        tmp = rt;
    } else {
        if (b[ls] > b[rs]) {
            dfs1(ls);
        } else {
            dfs1(rs);
        }
    }
}

int get(int rt) {
    dfs1(rt);
    return tmp;
    //	try { dfs1(rt); } catch(int e) { return tmp; }
    //	assert(0);
}

void run() {
    rd(h, g);
    n = 1 << h, m = 1 << g;
    for (int i = 1; i < n; ++i) rd(b[i]);
    int could = n - m;
    vector<int> res;
    ll sum = 0;
    int rt = 1;
    for (int i = 1; i <= could; ++i) {
        //	res.push_back(rt);
        //	dfs(rt);
        //	continue;
        while (b[rt] && get(rt) < m) {
            int ls = rt << 1;
            int rs = rt << 1 | 1;
            if (b[ls] > b[rs]) {
                rt = rs;
            } else {
                rt = ls;
            }
        }
        // dbg(i, rt);
        assert(b[rt]);
        res.push_back(rt);
        dfs(rt);
    }
    for (int i = 1; i < m; ++i) sum += b[i];
    pt(sum);
    for (int i = 0; i < SZ(res); ++i) cout << res[i] << " \n"[i == SZ(res) - 1];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout << fixed << setprecision(20);
    int _T = nextInt();
    while (_T--) run();
    //	while (cin >> n) run();
    //    for (int kase = 1; kase <= _T; ++kase) {
    //        cout << "Case #" << kase << ":\n";
    //        run();
    //    }
    return 0;
}
