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
int n;
ll a[N];
struct L_B {
    ll d[65], p[65];
    int cnt;
    void init() {
        memset(d, 0, sizeof d);
        memset(p, 0, sizeof p);
        cnt = 0;
    }  // 1e18以内的数都适用.
    bool Insert(ll val) {
        for (int i = 60; i >= 0; i--) {
            if (val & (1ll << i)) {
                if (!d[i]) {
                    d[i] = val;
                    break;
                }
                val ^= d[i];
            }
        }
        return val > 0;
        // 可判断val是否存在于线性基当中.
    }
    ll query_max() {
        ll res = 0;
        for (int i = 60; i >= 0; i--) {
            if ((res ^ d[i]) > res)
                res ^= d[i];
        }
        return res;
    }
    ll query_min() {  // 应该预先判断能否是0的情况..QAQ
        for (int i = 0; i <= 60; i++) {
            if (d[i])
                return d[i];
        }
        return 0;
    }
    void rebuild() {  // 用于求第k小值.需要先进行独立预处理
        for (int i = 60; i >= 0; i--) {
            for (int j = i - 1; j >= 0; j--) {
                if (d[i] & (1ll << j))
                    d[i] ^= d[j];
            }
        }
        for (int i = 0; i <= 60; i++) {
            if (d[i])
                p[cnt++] = d[i];
        }
    }
    ll kthquery(ll k) {  // 注意判断原序列异或出0的情况, 此时应该将k -- 在进行后面的操作.
        ll res = 0;
        if (k >= (1ll << cnt))
            return -1;
        for (int i = 60; i >= 0; i--) {
            if (k & (1LL << i))
                res ^= p[i];
        }
        return res;
    }
    void Merge(const L_B &b) {  // 把b这个线性基插入到当前这个线性基中.
        for (int i = 60; i >= 0; i--)
            if (b.d[i])
                Insert(b.d[i]);
    }
} lb;
void run() {
    ll sum = 0;
    lb.init();
    for (int i = 1; i <= n; ++i) cin >> a[i], sum ^= a[i];
    for (int i = 60; i >= 0; --i) {
        if ((sum >> i) & 1) {
            for (int j = 1; j <= n; ++j) {
                if ((a[j] >> i) & 1)
                    a[j] ^= (1ll << i);
            }
        }
    }
    for (int i = 1; i <= n; ++i) lb.Insert(a[i]);
    ll res = lb.query_max();
    cout << res + (sum ^ res) << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout << fixed << setprecision(20);
    while (cin >> n) run();
    return 0;
}
