#include <bits/stdc++.h>
#define fi first
#define se second
#define SZ(x) int((x).size())
#define endl "\n"
using namespace std;
using db = double;
using ll = unsigned long long;
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
// head
ll n, m, bit[70], one = 1;

inline ll lowbit(ll x) {
    return x & -x;
}

int Log2(ll x) {
    while (__builtin_popcountll(x) > 1) {
        x ^= lowbit(x);
    }
    return __builtin_ffsll(x) - 1;
}

ll gao(ll n, ll base, ll k) {
    if (k == 1) {
        return base + (one << Log2(n));
    }
    ll L = (one << Log2(n)) - 1;
    ll R = (n - L - 1);
    --k;
    if (k <= L)
        return gao(L, base, k);
    else
        return gao(R, base + (one << Log2(n)), k -= L);
}

void run() {
    rd(n, m);
    pt(gao(n, 0, m));
}

int main() {
    //	bit[0] = 1;
    //	for (int i = 1; i < 64; ++i)
    //		bit[i] = bit[i - 1] << 1;
    //	cout << bit[63] << endl;
    //	cout << (one << 63) << endl;
    //	cout << Log2(10) << endl;
    //	cout << Log2(72057594037927936) << endl;
    //	cout << Log2(one << 63) << endl;
    //	cout << Log2((one << 63) + 1) << endl;
    //	cout << Log2((one << 63) - 1) << endl;
    //	return 0;
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout << fixed << setprecision(20);
    int _T = nextInt();
    while (_T--) run();
    //	while (cin >> n) run();
    //    for (int kase = 1; kase <= _T; ++kase) {
    //        cout << "Case #" << kase << ":\n";
    //        run();
    //    }
    return 0;
}
