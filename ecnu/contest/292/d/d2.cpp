#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define SZ(x) ((int)(x).size())
#define mkp make_pair
#define all(x) (x).begin(), (x).end()
#define endl "\n"
using db = double;
using ll = long long;
using ull = unsigned long long;
using pII = pair<int, int>;
using pLL = pair<ll, ll>;
constexpr int mod = 998244353;
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
int n, b[N];
char s[N];
ll a[N], bit[N];

struct Hash {
    int seed, mod;
    int base[N], a[N];
    void init(int _seed, int _mod) {
        seed = _seed;
        mod = _mod;
        base[0] = 1;
        for (int i = 1; i < N; ++i) {
            base[i] = 1ll * base[i - 1] * seed % mod;
        }
    }
    // 1-indexed
    inline void gao(char *s, int n) {
        a[0] = 0;
        for (int i = 1; i <= n; ++i) {
            a[i] = (1ll * a[i - 1] * seed % mod + s[i]) % mod;
        }
    }
    inline int get(int l, int r) {
        return (a[r] - 1ll * a[l] * base[r - l + 1] % mod + mod) % mod;
    }
    inline int gao(int x, int l) {
        if (l <= x)
            return a[l];
        else
            return (1ll * a[x] * base[l - x] % mod + a[l - x]) % mod;
    }
} hs[2];

int get(int a, int l) {
    if (l <= a)
        return (s[l] - '0');
    else
        return (s[l - a] - '0');
}

void run() {
    cin >> (s + 1);
    n = strlen(s + 1);
    a[0] = 0;
    bit[0] = 1;
    for (int i = 1; i <= n; ++i) {
        a[i] = (a[i - 1] * 10 % mod + (s[i] - '0')) % mod;
        bit[i] = (bit[i - 1] * 10 % mod);
        // dbg(i, a[i], bit[i]);
        b[i] = i;
    }
    //	hs[0].init(233, 998244353);
    hs[1].init(13331, 1000000007);
    //	hs[0].gao(s, n);
    hs[1].gao(s, n);
    //	dbg(hs[1].get(2, 1), hs[1].get(1, 1));
    int k, p, len;
    sort(b + 1, b + 1 + n, [&](int x, int y) {
        len = x + y, k = 0, p = 1;
        while (p > 0) {
            if (hs[1].gao(x, k + p) == hs[1].gao(y, k + p)) {
                k += p;
                p <<= 1;
            } else {
                p >>= 1;
            }
            while (k + p > len) p >>= 1;
        }
        if (k == len)
            return false;
        if (get(x, k + 1) < get(y, k + 1))
            return false;
        else
            return true;
    });
    ll res = 0;
    for (int i = 1; i <= n; ++i) {
        int it = b[i];
        //	dbg(i, b[i]);
        res = (res * bit[it] % mod + a[it]) % mod;
    }
    pt(res);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout << fixed << setprecision(20);
    run();
    //    for (int kase = 1; kase <= _T; ++kase) {
    //        cout << "Case #" << kase << ": ";
    //        run();
    //    }
    //	while (cin >> n) run();
    //	run();
    return 0;
}
