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
constexpr int N = 1e3 + 100;
int n, K;
char s[110][110];
inline int id(int x, int y) {
    return (x - 1) * n + y;
}
bitset<N> b;

struct LB {
    vector<bitset<N>> b;
    void init() {
        b.clear();
        b.resize(N);
    }
    void insert(bitset<N> val) {
        for (int i = n * n; i >= 1; --i) {
            if (val[i]) {
                if (b[i].none()) {
                    b[i] = val;
                    break;
                }
                val ^= b[i];
            }
        }
    }
    int sze() {
        int res = 0;
        for (int i = 1; i <= n * n; ++i) {
            res += b[i].any();
            ;
        }
        return res;
    }
} lb;

void run() {
    n = 1 << K;
    lb.init();
    vector<pII> vec;
    for (int i = 1; i <= n; ++i) {
        cin >> (s[i] + 1);
        for (int j = 1; j <= n; ++j) {
            if (s[i][j] == '1')
                vec.push_back(pII(i, j));
        }
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            b.reset();
            for (auto &it : vec) {
                b[id((i + it.fi - 1) % n + 1, (j + it.se - 1) % n + 1)] = 1;
            }
            lb.insert(b);
        }
    }
    pt(qpow(2, lb.sze()));
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout << fixed << setprecision(20);
    while (cin >> K) run();
    return 0;
}
