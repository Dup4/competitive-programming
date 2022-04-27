#include <bits/stdc++.h>
using namespace std;

#define ll long long
const ll mod = 20100403;

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

ll C(int n, int m) {
    ll a = 1, b = 1;
    for (int i = n; i > n - m; --i) a = a * i % mod;
    for (int i = 1; i <= m; ++i) b = b * i % mod;
    //	cout << a << " " << b << endl;
    return a * qpow(b, mod - 2) % mod;
}

int main() {
    ll n, m;
    cin >> n >> m;
    cout << (C(n + m, n) - C(n + m, n + 1) + mod) % mod << "\n";
    return 0;
}
