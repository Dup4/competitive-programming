#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 1e3 + 10;
const ll mod = 1e9 + 7;
ll f[N];
ll gcd(ll a, ll b) {
    return b ? gcd(b, a % b) : a;
}
ll qpow(ll base, ll n) {
    ll res = 1;
    while (n) {
        if (n & 1)
            res = res * base % mod;
        base = base * base % mod;
        n >>= 1;
    }
    return res;
}

int d(int x) {
    int res = 0;
    for (int i = 1; i <= x; ++i) res += (x % i == 0);
    return res;
}

int main() {
    int n = 1000;
    int k = 2;
    for (int i = 1; i <= n; ++i) {
        f[i] = qpow(i, k) * d(qpow(i, k)) % mod;
    }
    cout << f[2] << endl;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= i; ++j)
            if (gcd(i, j) == 1 && i * j <= n)
                assert(f[i] * f[j] % mod == f[i * j]);
    return 0;
}
