#include <bits/stdc++.h>
using namespace std;
#define endl "\n"
#define fi first
#define se second
#define SZ(x) ((int)(x).size())
#define mkp make_pair
#define all(x) (x).begin(), (x).end()
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
ll x, y;

/*
0100
1000

1000
0010

0011
0011
0010

10000
00010

00111
00111
00010

01
01
01
*/
// 和为x 异或和为y

bool gao2() {
    ll a = 0, b = 0;
    for (int i = 59; i >= 0; --i) {
        int _x = (x >> i) & 1;
        int _y = (y >> i) & 1;
        if (_x == 0 && _y == 1)
            return false;
        if (_x == 1) {
            if (((a >> i) & 1))
                return false;
            if (a > b)
                b |= (1ll << i);
            else
                a |= (1ll << i);
        } else {
            a |= 1ll << (i - 1);
            b |= 1ll << (i - 1);
        }
    }
    pt(2);
    pt(a, b);
    return true;
}

void gao3() {
    ll a[3] = {0, 0, 0};
    int last = 0;
    for (int i = 0; i < 60; ++i) {
        int _x = (x >> i) & 1;
        int _y = (y >> i) & 1;
        if (_x == 1 && _y == 1) {
            a[0] |= 1ll << i;
        } else if (_x == 1 && _y == 0) {
            if (last == 0) {
                a[1] |= 1ll << (i - 1);
                a[2] |= 1ll << (i - 1);
            } else {
                last = 0;
                a[1] ^= 1ll << (i - 1);
                a[2] ^= 1ll << (i - 1);
            }
        } else if (_x == 0 && _y == 1) {
            last = 1;
            a[0] |= 1ll << i;
            a[1] |= 1ll << i;
            a[2] |= 1ll << i;
            if (i) {
                a[1] |= 1ll << (i - 1);
                a[2] |= 1ll << (i - 1);
            }
        }
        if (last) {
            a[1] |= 1ll << i;
            a[2] |= 1ll << i;
        }
    }
    //	dbg(a[0], a[1], a[2]);
    if (((a[0] + a[1]) ^ a[2]) == y) {
        pt(2);
        pt(a[0] + a[1], a[2]);
    } else if (((a[0] + a[2]) ^ a[1]) == y) {
        pt(2);
        pt(a[0] + a[2], a[1]);
    } else if (((a[1] + a[2]) ^ a[0]) == y) {
        pt(2);
        pt(a[1] + a[2], a[0]);
    } else {
        pt(3);
        pt(a[0], a[1], a[2]);
    }
}

void run() {
    rd(y, x);
    if (x < y || x % 2 != y % 2)
        return pt(-1);
    if (!x && !y)
        return pt(0);
    if (x == y) {
        pt(1);
        pt(x);
        return;
    }
    if (gao2())
        return;
    gao3();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout << fixed << setprecision(20);
    int _T = 1;
    // nextInt();
    while (_T--) run();
    //    for (int kase = 1; kase <= _T; ++kase) {
    //        cout << "Case #" << kase << ": ";
    //        run();
    //    }
    //    while (cin >> n) run();
    //    run();
    return 0;
}
