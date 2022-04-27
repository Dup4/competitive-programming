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
namespace Random {
double Next(double l, double r) {
    mt19937 mt(chrono::steady_clock::now().time_since_epoch().count());
    auto rd = bind(uniform_real_distribution<double>(l, r), mt);
    return rd();
}
long long Next(long long l, long long r) {
    mt19937 mt(chrono::steady_clock::now().time_since_epoch().count());
    auto rd = bind(uniform_int_distribution<long long>(l, r), mt);
    return rd();
}
}  // namespace Random

int main() {
    int n = 10000, q = 100000, limit = 1000;
    pt(n, q);
    string s[] = {"INSERT", "DELETE", "MAKE-SAME", "REVERSE", "GET-SUM", "MAX-SUM"};
    for (int i = 1; i <= n; ++i) cout << Random::Next(-1ll * limit, 1ll * limit) << " \n"[i == n];
    int m = n;
    for (int i = 1; i <= q; ++i) {
        int op = Random::Next(0ll, 5ll);
        if (m <= 1)
            op = 0;
        cout << s[op] << " ";
        if (op == 0) {
            int pos = Random::Next(0ll, 1ll * m);
            int tot = 1;
            int val = Random::Next(-1ll * limit, 1ll * limit);
            pt(pos, tot, val);
            ++m;
        } else if (op == 1) {
            int pos = Random::Next(1ll, 1ll * m);
            int tot = 1;
            pt(pos, tot);
            --m;
        } else if (op == 2) {
            int pos = Random::Next(1ll, 1ll * m);
            int tot = 1;
            int val = Random::Next(-1ll * limit, 1ll * limit);
            pt(pos, tot, val);
        } else if (op == 3) {
            int pos = Random::Next(1ll, 1ll * m);
            int tot = 1;
            pt(pos, tot);
        } else if (op == 4) {
            int pos = Random::Next(1ll, 1ll * m);
            int tot = 1;
            pt(pos, tot);
        } else {
            cout << endl;
        }
    }
    return 0;
}
