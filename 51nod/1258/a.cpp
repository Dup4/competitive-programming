#include <bits/stdc++.h>
using namespace std;

#define ll long long
const int N = 5e4 + 10;
const ll p = 1e9 + 7;
ll n, K;
ll qpow(ll base, ll n) {
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
    static const int SIZE = 5e4 + 10;
    ll f[SIZE], fac[SIZE], inv[SIZE], pre[SIZE], suf[SIZE];
    int n;
    void add(ll &x, ll y) {
        x += y;
        if (x >= p)
            x -= p;
    }
    void init(int _n) {
        n = _n;
        fac[0] = 1;
        for (int i = 1; i < SIZE; ++i) fac[i] = fac[i - 1] * i % p;
        inv[SIZE - 1] = qpow(fac[SIZE - 1], p - 2);
        for (int i = SIZE - 1; i >= 1; --i) inv[i - 1] = inv[i] * i % p;
        //设置f初值，可以根据需要修改
        f[0] = 0;
        for (int i = 1; i <= n; ++i) f[i] = (f[i - 1] + qpow(i, K)) % p;
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

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%lld%lld", &n, &K);
        lagrange.init(K + 1);
        printf("%lld\n", lagrange.cal(n));
    }
    return 0;
}
