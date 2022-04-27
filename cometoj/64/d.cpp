#include <bits/stdc++.h>
using namespace std;
#define debug(...)           \
    {                        \
        printf("#  ");       \
        printf(__VA_ARGS__); \
        puts("");            \
    }
#define fi first
#define se second
#define endl "\n"
using ll = long long;
using ull = unsigned long long;
using pII = pair<int, int>;
using pLL = pair<ll, ll>;
using VI = vector<int>;
using VL = vector<ll>;
constexpr int mod = 1e9 + 7;
template <class T1, class T2>
inline void chadd(T1 &x, T2 y) {
    x += y;
    if (x >= mod)
        x -= mod;
    else if (x < 0)
        x += mod;
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
template <class T>
inline void out(T s) {
    cout << s << "\n";
}
template <class T>
inline void out(vector<T> &vec) {
    for (auto &it : vec) cout << it << " ";
    cout << endl;
}
inline ll gcd(ll a, ll b) {
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
constexpr int N = 1e6 + 10;
int n, m, q, rt, a[N], fa[N], deep[N];
ull unit = 19260817, Base[N], Ha[N];
vector<vector<int>> G;
unordered_map<ull, int> mp;
void pre(int u) {
    mp[Ha[u]] = u;
    for (int i = 0, sze = (int)G[u].size(); i < sze; ++i) {
        int v = G[u][i];
        deep[v] = deep[u] + 1;
        Ha[v] = Ha[u] * unit + i + 1;
        pre(v);
    }
}

struct BIT {
    ull a[N];
    void init() {
        memset(a, 0, sizeof a);
    }
    void update(int x, ull v) {
        for (; x < N; x += x & -x) a[x] += v;
    }
    ull query(int x) {
        ull res = 0;
        for (; x > 0; x -= x & -x) res += a[x];
    }
    ull query(int l, int r) {
        if (l < r)
            return 0;
        return query(r) - query(l - 1);
    }
} bit;

void run() {
    G.clear();
    G.resize(n + 1);
    mp.clear();
    bit.init();
    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int i = 1; i <= n; ++i) {
        cin >> fa[i];
        if (fa[i])
            G[fa[i]].push_back(i);
        else
            rt = i;
    }
    Ha[rt] = 0;
    deep[rt] = 0;
    pre(rt);
}

int main() {
    Base[0] = 1;
    for (int i = 1; i < N; ++i) Base[i] = Base[i - 1] * unit;
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout << fixed << setprecision(20);
    while (cin >> n >> m >> q) run();
    return 0;
}
