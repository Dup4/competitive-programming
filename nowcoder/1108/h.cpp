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
template <class T>
inline void pt(T s) {
    cout << s << "\n";
}
template <class T>
inline void pt(vector<T> &vec) {
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
int n, q;
struct BIT {
    int a[N];
    inline void init() {
        memset(a, 0, sizeof a);
    }
    inline int lowbit(int x) {
        return x & -x;
    }
    void add(int x, int v) {
        for (int i = x; i < N; i += lowbit(i)) a[i] += v;
    }
    int query(int x) {
        int ret = 0;
        for (int i = x; i > 0; i -= lowbit(i)) ret += a[i];
        return ret;
    }
    int query(int l, int r) {
        if (l > r)
            return 0;
        return query(r) - query(l - 1);
    }
    void add(int l, int r, int v) {
        if (l > r)
            return;
        add(l, v);
        add(r + 1, -v);
    }
} bit[2];
map<pII, int> mp;
void run() {
    bit[0].init();
    bit[1].init();
    mp.clear();
    int op, l, r, m = 0;
    while (q--) {
        cin >> op >> l >> r;
        if (op == 1) {
            ++m;
            ++mp[pII(l, r)];
            bit[0].add(l, 1);
            bit[1].add(r, 1);
        } else {
            int res = m;
            res -= bit[1].query(1, r - 1);
            res -= bit[0].query(l + 1, n);
            for (int i = l + 1; i < r; ++i) {
                for (int j = i; j < r; ++j) {
                    if (mp.count(pII(i, j)))
                        res += mp[pII(i, j)];
                }
            }
            pt(res);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout << fixed << setprecision(20);
    while (cin >> n >> q) run();
    return 0;
}
