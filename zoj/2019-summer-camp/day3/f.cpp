#include <bits/stdc++.h>
using namespace std;

#define N 1100
#define db double
#define ll long long
const ll p = 1e9 + 7;
ll n;
void add(ll &x, ll y) {
    x += y;
    if (x >= p)
        x -= p;
}
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
ll f[N][N];

int main() {
    ll i = 4, j = 27;
    db _i = 4, _j = 27;
    ll res = 2;
    db _res = 2;
    for (int _ = 1; _ <= 10000000; ++_) {
        add(res, 1ll * 2 * i % p * qmod(j, p - 2) % p);
        _res += 2.0 * _i / _j;
        ++i;
        ++_i;
        j = j * 3 % p;
        _j = _j * 3;
        if (res == 500000006)
            cout << _ << endl;
    }
    cout << res << endl;
    cout << _res << endl;
    while (scanf("%lld", &n) != EOF) {
        memset(f, 0, sizeof f);
        ll res = 0;
        f[1][n] = 1;
        for (int i = 1; i <= 1000; ++i) {
            for (int j = 1; j <= n; ++j)
                if (f[i][j]) {
                    for (int k = 1; k <= j; ++k) {
                        add(f[i + 1][j / k], f[i][j] * qmod(j, p - 2) % p);
                    }
                }
        }
        for (int i = 1; i <= 1000; ++i) {
            add(res, 1ll * i * f[i][1] % p);
        }
        cout << res << endl;
    }
    return 0;
}
