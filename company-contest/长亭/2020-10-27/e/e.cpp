#include <bits/stdc++.h>
using namespace std;
using ll = long long;
ll n = 23333 * 10007;

ll eular(ll n) {
    ll ans = n;
    for (int i = 2; 1ll * i * i <= n; ++i) {
        if (n % i == 0) {
            ans -= ans / i;
            while (n % i == 0) n /= i;
        }
    }
    if (n > 1)
        ans -= ans / n;
    return ans;
}

ll exgcd(ll a, ll b, ll &x, ll &y) {
    if (a == 0 && b == 0)
        return -1;
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    ll d = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return d;
}

ll inv(ll a, ll n) {
    ll x, y;
    ll d = exgcd(a, n, x, y);
    if (d == 1)
        return (x % n + n) % n;
    return -1;
}

ll qpow(ll base, ll n, ll mod) {
    ll res = 1;
    while (n) {
        if (n & 1)
            res = res * base % mod;
        base = base * base % mod;
        n >>= 1;
    }
    return res;
}

int main() {
    ll phin = eular(n);
    ll e, c;
    cin >> e >> c;
    ll d = inv(e, phin);
    // cout << d << endl;
    cout << qpow(c, d, n) << endl;
    return 0;
}