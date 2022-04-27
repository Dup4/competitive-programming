#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 5e6 + 10;
const ll p = 1e9 + 7;
int n, t;
ll l, r, f[N];

ll qmod(ll base, ll n) {
    ll res = 1;
    while (n) {
        if (n & 1) {
            res = res * base % p;
        }
        base = base * base % p;
        n >>= 1;
    }
    return res;
}

//拉格朗日差值
struct Lagrange {
    static const int SIZE = 5e6 + 10;
    ll f[SIZE], fac[SIZE], inv[SIZE], pre[SIZE], suf[SIZE];
    int n;
    void add(ll &x, ll y) {
        x += y;
        while (x >= p) x -= p;
        while (x < 0) x += p;
    }
    void init(int _n, ll *_f) {
        n = _n;
        fac[0] = 1;
        for (int i = 1; i < SIZE; ++i) fac[i] = fac[i - 1] * i % p;
        inv[SIZE - 1] = qmod(fac[SIZE - 1], p - 2);
        for (int i = SIZE - 1; i >= 1; --i) inv[i - 1] = inv[i] * i % p;
        //设置f初值，可以根据需要修改
        for (int i = 0; i <= n; ++i) f[i] = _f[i];
    }
    ll cal(ll x) {
        if (x <= n)
            return f[x];
        pre[0] = x % p;
        for (int i = 1; i <= n; ++i) pre[i] = pre[i - 1] * ((x - i) % p) % p;
        suf[n] = (x - n) % p;
        for (int i = n - 1; i >= 0; --i) suf[i] = suf[i + 1] * ((x - i) % p) % p;
        ll res = 0;
        for (int i = 0; i <= n; ++i) {
            ll tmp = f[i] * inv[n - i] % p * inv[i] % p;
            if (i)
                tmp = tmp * pre[i - 1] % p;
            if (i < n)
                tmp = tmp * suf[i + 1] % p;
            if ((n - i) & 1)
                tmp = p - tmp;
            add(res, tmp);
        }
        return res;
    }
} lagrange;

ll g(ll x) {
    return (x % p * (qmod(x % p, t) - 1 + p) % p) % p * qmod(x - 1, p - 2) % p;
}

ll cnt(ll x, int y) {
    ll res = 0;
    if (x >= y)
        ++res;
    res += (x - y) / 4;
    return res;
}

int main() {
    while (scanf("%d%lld%lld", &t, &l, &r) != EOF) {
        f[0] = 0;
        int limit = 1e6;
        for (int i = 1; i <= limit; ++i) {
            int mod = i % 4;
            f[i] = 0;
            if (mod == 0) {
                f[i] = g(i);
            } else if (mod == 1) {
                f[i] = g(i - 1);
            } else if (mod == 2) {
                f[i] = g(i);
            } else if (mod == 3) {
                f[i] = g(i - 1);
            }
            f[i] = (f[i] + f[i - 1]) % p;
        }
        lagrange.init(limit, f);
        ll res = 0;
        res += (cnt(r, 3) - cnt(l - 1, 3) + p) % p * (t / 2) % p;
        res += (cnt(r, 1) - cnt(l - 1, 1) + p) % p * t % p;
        res += (cnt(r, 2) - cnt(l - 1, 2) + p) % p;
        res %= p;
        if (r % 2 == 0)
            ++r;
        printf("%lld\n", (res + (lagrange.cal(r) - lagrange.cal(l - 1) + p) % p * qmod(2, p - 2) % p) % p);
    }
    return 0;
}
