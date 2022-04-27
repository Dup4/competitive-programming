#pragma GCC optimize("Ofast,unroll-loops,no-stack-protector,fast-math")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
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
inline void pt() {
    cout << endl;
}
template <class T, class... Ts>
void pt(const T &arg, const Ts &...args) {
    cout << arg << ' ';
    pt(args...);
}
template <template <typename...> class T, typename t, typename... A>
void pt(const T<t> &arg, const A &...args) {
    for (auto &v : arg) cout << v << ' ';
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
constexpr int N = 2e5 + 10;
int n, m;
struct Hash {
    vector<int> a;
    void init() {
        a.clear();
    }
    void add(int x) {
        a.push_back(x);
    }
    void gao() {
        sort(a.begin(), a.end());
        a.erase(unique(a.begin(), a.end()), a.end());
    }
    int get(int x) {
        return lower_bound(a.begin(), a.end(), x) - a.begin() + 1;
    }
} hs;
struct BIT {
    int a[N];
    void init() {
        memset(a, 0, sizeof a);
    }
    void up(int x) {
        for (; x < N; x += x & -x) a[x] += 1;
    }
    int query(int x) {
        int res = 0;
        for (; x > 0; x -= x & -x) res += a[x];
        return res;
    }
} bit;
int dis(ll x, ll y, ll z) {
    ll tmp = x * x + y * y + z * z;
    int mid = sqrt(tmp);
    for (int i = max(0, mid - 10); i <= mid + 10; ++i) {
        if (1ll * i * i >= tmp)
            return i;
    }
}
struct E {
    int op, x, y, z, k;
    E() {}
    void scan() {
        op = rd();
        if (op == 1) {
            x = rd(), y = rd(), z = rd();
            k = dis(x, y, z);
            hs.add(k);
        } else {
            k = rd();
        }
    }
} e[N];
void run() {
    hs.init();
    bit.init();
    for (int i = 1; i <= n; ++i) e[i].scan();
    hs.gao();
    m = hs.a.size();
    for (int i = 1; i <= n; ++i) {
        if (e[i].op == 1) {
            bit.up(hs.get(e[i].k));
        } else {
            if (e[i].k == 0) {
                pt(0);
                continue;
            }
            int l = 1, r = m, res = m + 1;
            while (r - l >= 0) {
                int mid = (l + r) >> 1;
                if (bit.query(mid) >= e[i].k) {
                    res = mid;
                    r = mid - 1;
                } else {
                    l = mid + 1;
                }
            }
            if (res == m + 1)
                res = -1;
            else
                res = hs.a[res - 1];
            pt(res);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout << fixed << setprecision(20);
    while (cin >> n) run();
    return 0;
}
