#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll p = 998244353;
#define N 3010

ll qpow(ll x, ll n) {
    ll res = 1;
    while (n) {
        if (n & 1) {
            res = res * x % p;
        }
        x = x * x % p;
        n >>= 1;
    }
    return res;
}

void add(ll &x, ll y) {
    x += y;
    if (x >= p) {
        x -= y;
    }
}

int n;
ll f[N], a[N], b[N];
ll sf[N], sa[N], sb[N];

void Init() {
    b[0] = 1;
    for (int i = 1; i < N; ++i) {
        b[i] = b[i - 1] * i % p;
        sb[i] = (sb[i - 1] + b[i]) % p;
    }
    ll inv4 = qpow(4, p - 2);
    for (int i = 1; i < N; ++i) {
        a[i] = b[i] * i % p * (i - 1) % p * inv4 % p;
        sa[i] = (sa[i - 1] + a[i]) % p;
    }
    for (int i = 1; i < N; ++i) {
        f[i] = sa[i] * qpow(sb[i], p - 2) % p * qpow(i - 1, p - 2) % p;
        add(f[i], f[i - 1]);
        sf[i] = (sf[i - 1] + f[i]) % p;
    }
}

int main() {
    Init();
    while (scanf("%d", &n) != EOF) {
//        cout << a[n] << " " << sa[n] << " " << b[n] << " " << sb[n] << endl;
        printf("%lld\n", f[n]);
    }
    return 0;
}
