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
constexpr int N = 1e2 + 10;
constexpr ll INFLL = 1e18;
int n, m;
ll a[N][N], f[N][N];

ll gao(ll x) {
    memset(f, 0, sizeof f);
    if (a[1][1] < x)
        return INFLL;
    //	f[1][1] = a[1][1] - x;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            ll tar = x + (i - 1) + (j - 1);
            f[i][j] = INFLL;
            if (a[i][j] >= tar) {
                if (i > 1)
                    chmin(f[i][j], a[i][j] - tar + f[i - 1][j]);
                if (j > 1)
                    chmin(f[i][j], a[i][j] - tar + f[i][j - 1]);
            }
            if (i == 1 && j == 1)
                f[i][j] = a[i][j] - tar;
        }
    }
    return f[n][m];
}

void run() {
    rd(n, m);
    ll Max = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            rd(a[i][j]);
            chmax(Max, a[i][j]);
        }
    }
    ll l = -1000, r = Max, res = r;
    //	- n - m + 2, res = r;
    while (r - l >= 0) {
        ll mid = (l + r) / 2;
        if (gao(mid - 1) > gao(mid + 1)) {
            l = mid + 1;
        } else {
            res = mid;
            r = mid - 1;
        }
        //	ll th = (r - l + 1) / 3;
        //	ll mid = (l + r) / 2;
        //	ll mid1 = l + th, mid2 = l + th * 2;
        //	if (gao(mid1) > gao(mid2)) {
        //		l = mid2 + 1;
        //	} else {
        //		r = mid1 - 1;
        //	}
    }
    //	pt(min(gao(l), gao(r)));
    pt(min({gao(l), gao(res), gao(r)}));
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout << fixed << setprecision(20);
    int _T = nextInt();
    while (_T--) run();
    //    for (int kase = 1; kase <= _T; ++kase) {
    //        cout << "Case #" << kase << ": ";
    //        run();
    //    }
    //	while (cin >> n) run();
    //	run();
    return 0;
}
