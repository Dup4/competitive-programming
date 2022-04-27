#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define dbg(x...)                             \
    do {                                      \
        cout << "\033[32;1m" << #x << " -> "; \
        err(x);                               \
    } while (0)
void err() {
    cout << "\033[39;0m" << endl;
}
template <class T, class... Ts>
void err(const T& arg, const Ts&... args) {
    cout << arg << " ";
    err(args...);
}
const int N = 2e5 + 10, INF = 0x3f3f3f3f;
int n;
ll x, y, a[N], f[N];
mt19937 rd(time(0));
ll gcd(ll a, ll b) {
    return b ? gcd(b, a % b) : a;
}
// ll mul(ll a, ll b, ll p) {
//	return (a * b - (ll)(a / (long double)p * b + 1e-3) * p + p) % p;
// }
ll mul(ll a, ll b, ll p) {
    return (__int128)a * b % p;
}
ll qpow(ll base, ll n, ll p) {
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
    ll n, fac[22000][2], bk[22000];
    int tot;
    const int C = 2307;
    const int S = 8;
    bool check(ll a, ll n) {
        ll m = n - 1, x, y = 0;
        int j = 0;
        while (!(m & 1)) {
            m >>= 1;
            ++j;
        }
        x = qpow(a, m, n);
        for (int i = 1; i <= j; x = y, ++i) {
            y = mul(x, x, n);
            if (y == 1 && x != 1 && x != n - 1) {
                return 1;
            }
        }
        return y != 1;
    }
    bool miller_rabin(ll n) {
        if (n < 2) {
            return 0;
        } else if (n == 2) {
            return 1;
        } else if (!(n & 1)) {
            return 0;
        }
        for (int i = 0; i < S; ++i) {
            if (check(rd() % (n - 1) + 1, n)) {
                return 0;
            }
        }
        return 1;
    }
    ll pollard_rho(ll n, int c) {
        ll i = 1, k = 2, x = rd() % n, y = x, d;
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
    void findfac(ll n, int c) {
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
    void gao(ll _n) {
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
    }
} mill;

int main() {
    int _T;
    cin >> _T;
    while (_T--) {
        scanf("%d%lld%lld", &n, &x, &y);
        for (int i = 1; i <= n; ++i) scanf("%lld", a + i);
        mill.gao(x);
        int tot = mill.tot;
        for (int i = 1; i <= tot; ++i) f[i] = 0;
        ll res = 8e18;
        for (int i = 1; i <= tot; ++i) {
            //			dbg(mill.fac[i][0], mill.fac[i][1]);
            ll now = 1;
            for (int j = 1; now <= y / mill.fac[i][0]; ++j) {
                now *= mill.fac[i][0];
                f[i] += (y / now);
                for (int o = 1; o <= n; ++o) {
                    f[i] -= (a[o] / now);
                }
            }
            res = min(1ll * res, f[i] / mill.fac[i][1]);
        }
        printf("%lld\n", res);
    }
    return 0;
}
