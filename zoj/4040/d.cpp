#include <bits/stdc++.h>
using namespace std;
using ll = long long;
mt19937 rd(time(0));
inline ll gcd(ll a, ll b) {
    return b ? gcd(b, a % b) : a;
}
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
    const int S = 8;
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
            if (check(rd() % (n - 1) + 1, n)) {
                return 0;
            }
        }
        return 1;
    }
    inline ll pollard_rho(ll n, int c) {
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
        }
        sort(vec.begin(), vec.end());
    }
} mill;
ll n;
vector<ll> fac;

int main() {
    int _T;
    scanf("%d", &_T);
    while (_T--) {
        scanf("%lld", &n);
        mill.gao(n, fac);
        ll res = 0;
        for (ll &it : fac) {
            if (it <= res + 1) {
                res += it;
            } else
                break;
        }
        printf("%lld\n", res + 1);
    }
    return 0;
}
