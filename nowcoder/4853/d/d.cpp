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
ll a, b, c, k;

ll exgcd(ll a, ll b, ll &x, ll &y) {
    if (a == 0 && b == 0)
        return -1;
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    ll d = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return d;
}

ll ceil(ll a, ll b) {
    return (a + b - 1) / b;
}

bool gao(ll a, ll b, ll &x, ll &y) {
    ll g = __gcd(a, b);
    if (k % g)
        return false;
    //	dbg(k, g);
    exgcd(a, b, x, y);
    x *= k / g;
    y *= k / g;
    //	dbg(x, y);
    if (x >= 0 && y >= 0)
        return true;
    if (x < 0) {
        ll t = y / a;
        //		dbg(y, a, t);
        if (t * b >= -x) {
            x += t * b;
            y -= t * a;
            return true;
        }
    }
    if (y < 0) {
        ll t = x / b;
        if (t * a >= -y) {
            x -= t * b;
            y += t * a;
            return true;
        }
    }
    return false;
}

void run() {
    if (k % a == 0)
        return pt(k / a, 0, 0);
    if (k % b == 0)
        return pt(0, k / b, 0);
    if (k % c == 0)
        return pt(0, 0, k / c);
    if (k % (a + b) == 0)
        return pt(k / (a + b), k / (a + b), 0);
    if (k % (a + c) == 0)
        return pt(k / (a + c), 0, k / (a + c));
    if (k % (b + c) == 0)
        return pt(0, k / (b + c), k / (b + c));
    if (k % (a + b + c) == 0)
        return pt(k / (a + b + c), k / (a + b + c), k / (a + b + c));
    ll x, y;
    if (gao(a, b, x, y)) {
        return pt(x, y, 0);
    }
    if (gao(a, c, x, y)) {
        return pt(x, 0, y);
    }
    if (gao(b, c, x, y)) {
        return pt(0, x, y);
    }
    if (gao(a + b, c, x, y)) {
        return pt(x, x, y);
    }
    if (gao(a + c, b, x, y)) {
        return pt(x, y, x);
    }
    if (gao(b + c, a, x, y)) {
        return pt(y, x, x);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout << fixed << setprecision(20);
    while (cin >> a >> b >> c >> k) run();
    //	while (cin >> n) run();
    //    for (int kase = 1; kase <= _T; ++kase) {
    //        cout << "Case #" << kase << ":\n";
    //        run();
    //    }
    return 0;
}
