#include <bits/stdc++.h>
#define fi first
#define se second
#define SZ(x) ((int)x.size())
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
constexpr int N = 1e6 + 10;
int n, a[N];

struct frac {
    ll x, y;
    frac() {}
    frac(ll x, ll y) : x(x), y(y) {}
    frac operator+(const frac &u) {
        return frac(x + u.x, y + u.y);
    }
    bool operator<(const frac &other) const {
        return x * other.y < y * other.x;
    }
    bool operator>(const frac &other) const {
        return x * other.y > y * other.x;
    }
    bool operator!=(const frac &other) const {
        return x * other.y != y * other.x;
    }
    bool operator<=(const frac &other) const {
        return x * other.y <= y * other.x;
    }
    bool operator>=(const frac &other) const {
        return x * other.y >= y * other.x;
    }
    bool operator==(const frac &other) const {
        return x * other.y == y * other.x;
    }
};

void run() {
    vector<frac> f[2];
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        f[0].push_back(frac(a[i], 1));
    }
    while (SZ(f[0]) > 1) {
        int ok = 0;
        f[1].clear();
        reverse(f[0].begin(), f[0].end());
        f[1].push_back(f[0].back());
        f[0].pop_back();
        while (SZ(f[0]) >= 1) {
            if (f[0].back() < f[1].back())
                f[1].back() = f[1].back() + f[0].back(), ok = 1;
            else
                f[1].push_back(f[0].back());
            f[0].pop_back();
        }
        swap(f[0], f[1]);
        if (!ok)
            break;
    }
    for (auto &it : f[0]) {
        for (int i = 1; i <= it.y; ++i) cout << it.x * 1.0 / it.y << endl;
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