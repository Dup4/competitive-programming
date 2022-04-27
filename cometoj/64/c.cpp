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
constexpr int N = 1e5 + 10;
int n, k, fa[N], deep[N], md[N], far;
vector<vector<int>> G;
void get_far(int u) {
    queue<int> q;
    q.push(u);
    deep[u] = 1;
    fa[u] = -1;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        far = u;
        for (auto v : G[u])
            if (v != fa[u]) {
                fa[v] = u;
                deep[v] = deep[u] + 1;
                q.push(v);
            }
    }
}
int get_center(int u) {
    get_far(u);
    get_far(far);
    int shift = deep[far] / 2;
    if (deep[far] % 2 == 0)
        --shift;
    while (shift--) far = fa[far];
    return far;
}
void pre(int u) {
    md[u] = deep[u];
    for (auto &v : G[u])
        if (v != fa[u]) {
            fa[v] = u;
            deep[v] = deep[u] + 1;
            pre(v);
            md[u] = max(md[u], md[v]);
        }
}
int cnt, limit, rt;
void cal(int u) {
    if (md[u] - deep[u] >= limit)
        ++cnt;
    else
        return;
    for (auto &v : G[u])
        if (v != fa[u]) {
            cal(v);
        }
}
bool check(int x) {
    cnt = 0;
    limit = x;
    cal(rt);
    return cnt <= k;
}
void run() {
    G.clear();
    G.resize(n + 1);
    for (int i = 1, u, v; i < n; ++i) {
        cin >> u >> v;
        G[u].push_back(v);
        G[v].push_back(u);
    }
    rt = get_center(1);
    deep[rt] = 0;
    fa[rt] = rt;
    pre(rt);
    int l = 0, r = n, res = n;
    while (r - l >= 0) {
        int mid = (l + r) >> 1;
        if (check(mid)) {
            res = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    cout << res << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout << fixed << setprecision(20);
    while (cin >> n >> k) run();
    return 0;
}
