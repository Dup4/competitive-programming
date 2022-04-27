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
constexpr int N = 1e5 + 10;

ll query(ll x) {
    pt('?', x);
    cout.flush();
    rd(x);
    return x;
}

void ok(ll x) {
    pt('!', x);
    cout.flush();
}

int pri[N], check[N];
void sieve() {
    memset(check, 0, sizeof check);
    *pri = 0;
    for (int i = 2; i < N; ++i) {
        if (!check[i]) {
            pri[++*pri] = i;
        }
        for (int j = 1; j <= *pri; ++j) {
            if (1ll * i * pri[j] >= N)
                break;
            check[i * pri[j]] = 1;
            if (i % pri[j] == 0)
                break;
        }
    }
}

vector<ll> A, B;

void get(int l, int r, vector<ll> &vec) {
    int cnt = 0;
    __int128 limit = 1e18, now = 1;
    vec.clear();
    for (int i = l; i <= r; ++i) {
        if (!check[i]) {
            ++cnt;
            if (now * i <= limit)
                now *= i;
            else {
                vec.push_back(now);
                now = 1;
            }
        }
    }
    vec.push_back(now);
}

vector<pII> getfac(ll x) {
    vector<pII> fac;
    for (int i = 2; 1ll * i * i <= x; ++i) {
        if (x % i == 0) {
            pII it = pII(i, 0);
            while (x % i == 0) {
                ++it.se;
                x /= i;
            }
            fac.push_back(it);
        }
    }
    if (x != 1)
        fac.push_back(pII(x, 1));
    return fac;
}

ll getPow(ll x) {
    ll y = x;
    while (y <= 1e9) {
        y *= x;
    }
    return y;
}

ll getCnt(ll x, ll y) {
    ll res = 0;
    while (x % y == 0) {
        x /= y;
        ++res;
    }
    return res;
}

void run() {
    ll _A = 1;
    vector<ll> vec;
    for (auto &it : A) {
        ll now = query(it);
        _A *= now;
        vector<pII> fac(getfac(now));
        for (auto &it : fac) vec.push_back(it.fi);
    }
    if (_A == 1)
        return ok(8);
    if (_A == 2 || _A == 3) {
        ll p = getPow(_A);
        ll now = query(p);
        if (now == _A)
            return ok(9);
    }
    ll res = 1;
    _A = 1;
    for (auto &it : vec) {
        ll _it = getPow(it);
        ll now = query(_it);
        _A *= now;
        res *= (getCnt(now, it) + 1);
    }
    ll _res = res * 2;
    ll __res = res + 7;
    return ok(max(_res, __res));
}

int main() {
    sieve();
    get(2, 700, A);
    //	get(2, 507, A);
    //	get(509, 1000, B);
    //	get(1, 700, A);
    //	pt(SZ(A));
    //	pt(SZ(A));
    //	pt(SZ(B));
    //	return 0;
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
