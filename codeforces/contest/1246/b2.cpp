#pragma GCC optimize("Ofast,unroll-loops,no-stack-protector,fast-math")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
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
inline void pt() {
    cout << endl;
}
template <class T, class... Ts>
void pt(const T &arg, const Ts &...args) {
    cout << arg << ' ';
    pt(args...);
}
template <template <typename...> class T, typename t, typename... A>
void pt(const T<t> &arg, const A &...args) {
    for (auto &v : arg) cout << v << ' ';
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
constexpr int N = 1e5 + 10;
constexpr ll M = 1e10 + 10;
mt19937 rnd(time(0));
inline ll mul(ll a, ll b, ll p) {
    return (a * b - (ll)(a / (long double)p * b + 1e-3) * p + p) % p;
}
inline ll qmod(ll base, ll n, ll p) {
    ll res = 1;
    base %= p;
    while (n) {
        if (n & 1) {
            res = mul(res, base, p);
        }
        base = mul(base, base, p);
        n >>= 1;
    }
    return res;
}
struct Mill {
    ll n, fac[220][2], bk[220];
    int tot;
    // fac[i][0] 第i个质因子 fac[i][1] 第i个质因子的幂次
    const int C = 2307;
    const int S = 6;
    inline bool check(ll a, ll n) {
        ll m = n - 1, x, y = 0;
        int j = 0;
        while (!(m & 1)) {
            m >>= 1;
            ++j;
        }
        x = qmod(a, m, n);
        for (int i = 1; i <= j; x = y, ++i) {
            y = mul(x, x, n);
            if (y == 1 && x != 1 && x != n - 1) {
                return 1;
            }
        }
        return y != 1;
    }
    inline bool miller_rabin(ll n) {
        if (n < 2) {
            return 0;
        } else if (n == 2) {
            return 1;

        } else if (!(n & 1)) {
            return 0;
        }
        for (int i = 0; i < S; ++i) {
            if (check(rnd() % (n - 1) + 1, n)) {
                return 0;
            }
        }
        return 1;
    }
    inline ll pollard_rho(ll n, int c) {
        ll i = 1, k = 2, x = rnd() % n, y = x, d;
        while (1) {
            ++i;
            x = (mul(x, x, n) + c) % n;
            d = gcd(y - x, n);
            if (d > 1 && d < n) {
                return d;
            }
            if (y == x) {
                return n;
            }
            if (i == k) {
                y = x;
                k <<= 1;
            }
        }
    }
    inline void findfac(ll n, int c) {
        if (n == 1) {
            return;
        }
        if (miller_rabin(n)) {
            bk[++*bk] = n;
            return;
        }
        ll m = n;
        while (m == n) {
            m = pollard_rho(n, c--);
        }
        findfac(m, c);
        findfac(n / m, c);
    }
    inline void gao(ll _n, vector<ll> &vec) {
        vec.clear();
        n = _n;
        *bk = 0;
        findfac(n, C);
        sort(bk + 1, bk + 1 + *bk);
        fac[1][0] = bk[1];
        fac[1][1] = 1;
        tot = 1;
        for (int i = 2; i <= *bk; ++i) {
            if (bk[i] == bk[i - 1]) {
                ++fac[tot][1];
            } else {
                ++tot;
                fac[tot][0] = bk[i];
                fac[tot][1] = 1;
            }
        }
        vec.push_back(1);
        for (int i = 1, sze = 0; i <= *bk; ++i) {
            if (i == 1 || bk[i - 1] % bk[i]) {
                sze = vec.size();
            } else {
                bk[i] *= bk[i - 1];
            }
            for (int j = 0; j < sze; ++j) {
                vec.push_back(bk[i] * vec[j]);
            }
            //	if (vec.back() > 100000) break;
        }
        sort(vec.begin(), vec.end());
    }
} mill;
int n, m, k, a[N];
ll f(int x, int k) {
    ll res = 1;
    for (int i = 1; i <= k; ++i) {
        res = res * x;
        if (res > M)
            return -1;
    }
    return res;
}
void run() {
    memset(a, 0, sizeof a);
    m = 1e5;
    for (int i = 1; i <= n; ++i) ++a[rd()];
    if (k > 2) {
        vector<ll> fac;
        ll res = 0;
        for (int i = 1;; ++i) {
            ll x = f(i, k);
            if (x == -1)
                break;
            fac.clear();
            mill.gao(x, fac);
            for (auto &it : fac) {
                ll p = it, q = x / p;
                if (p > q)
                    break;
                if (p < q) {
                    if (p <= m && q <= m)
                        res += 1ll * a[p] * a[q];
                } else if (p == q) {
                    if (p <= m) {
                        res += 1ll * a[p] * (a[p] - 1) / 2;
                    }
                    break;
                }
            }
        }
        pt(res);
    } else {
        vector<vector<int>> vec;
        vec.clear();
        vec.resize(m + 10);
        for (int i = 1; i <= m; ++i) {
            for (int j = i; j <= m; j += i) {
                vec[i].push_back(j);
            }
        }
        ll res = 0;
        vector<ll> fac;
        for (int i = 1; i <= m; ++i) {
            mill.gao(i, fac);
            int x = 1;
            for (int j = 1; j <= mill.tot; ++j) {
                x *= f(mill.fac[j][0], mill.fac[j][1] / 2);
            }
            dbg(x);
            for (auto &it : vec[x]) {
                ll y = 1ll * it * it;
                if (y % i == 0) {
                    ll z = y / i;
                    if (z < i) {
                        res += 1ll * a[z] * a[i];
                    } else if (z == i) {
                        res += 1ll * a[z] * (a[z] - 1) / 2;
                    }
                }
            }
        }
        pt(res);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout << fixed << setprecision(20);
    while (cin >> n >> k) run();
    return 0;
}
