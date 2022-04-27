#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define LL __int128
LL gcd(LL a, LL b) {
    return b ? gcd(b, a % b) : a;
}
LL exgcd(LL a, LL b, LL &x, LL &y) {
    if (!a && !b)
        return -1;
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    LL d = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return d;
}

const int N = 1e5 + 10;
LL c, MOD;
LL a[N], m[N];
int n;

void gao() {
    LL A = a[1], M = m[1], k, y;
    for (int i = 2; i <= n; ++i) {
        LL r = exgcd(M, m[i], k, y);
        c = a[i] - A;
        MOD = m[i] / r;
        // if (c % r) {
        //     puts("he was definitely lying");
        //     return;
        // }
        k = (c / r * k % MOD + MOD) % MOD;
        A += k * M;
        M = M * m[i] / r;
        A = (A + M) % M;
    }
    ll res = A;
    printf("%lld\n", res);
}

int main() {
    while (scanf("%d", &n) != EOF) {
        for (int i = 1; i <= n; ++i) {
            ll x, y;
            scanf("%lld%lld", &x, &y);
            m[i] = x;
            a[i] = y;
        }
        gao();
    }
    return 0;
}
