#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 1100
const ll p = 9999991;
int n, m;
ll f[N];

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
    static const int SIZE = 1100;
    ll f[SIZE], fac[SIZE], inv[SIZE], pre[SIZE], suf[SIZE];
    int n;
    void add(ll &x, ll y) {
        x += y;
        if (x >= p)
            x -= p;
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

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &m);
        for (int i = 0; i <= n; ++i) scanf("%lld", f + i);
        lagrange.init(n, f);
        f[n + 1] = lagrange.cal(n + 1);
        for (int i = 1; i <= n + 1; ++i) f[i] = (f[i] + f[i - 1]) % p;
        lagrange.init(n + 1, f);
        int l, r;
        while (m--) {
            scanf("%d%d", &l, &r);
            printf("%lld\n", (lagrange.cal(r) - lagrange.cal(l - 1) + p) % p);
        }
    }
    return 0;
}
