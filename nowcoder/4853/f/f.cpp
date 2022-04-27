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
constexpr int N = 1e5 + 10;
int n, xa, ya, xb, yb, x[N], y[N];

ll gcd(ll a, ll b) {
    return b ? gcd(b, a % b) : a;
}

struct frac {
    ll x, y;
    void sim() {
        ll g = gcd(abs(x), abs(y));
        x /= g;
        y /= g;
        if (x * y < 0) {
            x = -abs(x);
            y = abs(y);
        } else {
            x = abs(x);
            y = abs(y);
        }
    }
    frac() {}
    frac(ll x, ll y) : x(x), y(y) {
        sim();
    }
    frac operator+(const frac &u) {
        ll p, q;
        p = x * u.y + y * u.x;
        q = u.y * y;
        ll d = gcd(p, q);
        p /= d;
        q /= d;
        return (frac){p, q};
    }
    frac operator-(const frac &u) {
        ll p, q;
        p = x * u.y - y * u.x;
        q = u.y * y;
        ll d = gcd(p, q);
        p /= d;
        q /= d;
        return (frac){p, q};
    }
    frac operator*(const frac &u) {
        ll p, q;
        p = u.x * x;
        q = u.y * y;
        ll d = gcd(p, q);
        p /= d;
        q /= d;
        return (frac){p, q};
    }
    frac operator/(const frac &u) {
        ll p, q;
        p = u.y * x;
        q = u.x * y;
        ll d = gcd(p, q);
        p /= d;
        q /= d;
        return (frac){p, q};
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
    void sqr() {
        *this = (*this) * (*this);
    }
    void print() {
        sim();
        if (x * y < 0)
            putchar('-');
        printf("%lld/%lld", abs(x), abs(y));
    }
};

void run() {
    rd(xa, ya, xb, yb);
    for (int i = 1; i <= n; ++i) {
        rd(x[i], y[i]);
    }
    ll res = 1ll * n * (n - 1) / 2;
    vector<frac> vec;
    frac K = frac(yb - ya, xb - xa);
    frac B = frac(ya, 1) - (frac(xa, 1) * K);
    for (int i = 1; i <= n; ++i) {
        vec.push_back(frac(y[i], 1) - (frac(x[i], 1) * K));
    }
    sort(vec.begin(), vec.end());
    for (int i = 1; i < n; ++i) {
        if (vec[i] == vec[i - 1] && vec[i] != B)
            --res;
    }
    pt(res);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout << fixed << setprecision(20);
    while (cin >> n) run();
    //    for (int kase = 1; kase <= _T; ++kase) {
    //        cout << "Case #" << kase << ":\n";
    //        run();
    //    }
    return 0;
}
