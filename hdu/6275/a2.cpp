#include "bits/stdc++.h"

using namespace std;
typedef long long ll;

bool f(ll a, ll b, ll c, ll n) {
    if (!a) return (((n + 1) & (b / c)) & 1ll) > 0;
    if (a >= c || b >= c) {
        ll temp = (n & 1ll) ? (n + 1) / 2 * n : n / 2 * (n + 1);//先除后乘防止溢出
        return ((a / c * temp + (b / c) * (n + 1) + f(a % c, b % c, c, n)) & 1ll) > 0;
    } else {
        ll m = (a * n + b) / c;
        return (((n * m) ^ f(c, c - b - 1, a, m - 1)) & 1) > 0;
    }
}

int main() {
    int _;
    scanf("%d", &_);
    while (_--) {
        ll n;
        scanf("%lld", &n);
        ll ans = 0, to = min(30000000ll, n);
        for (ll i = 1; i < to; i++) {
            ans = ans ^ (n % i);
        }
        for (ll i = to, j; i <= n; i = j + 1) {
            j = n / (n / i);
            ll c = 1, ans1 = 0;
            for (int k = 1; k <= 50; k++) {
                ans1 += f(n / i, n % j, c, j - i) * c;
                c <<= 1;
            }
            ans ^= ans1;
        }
        printf("%lld\n", ans);
    }
    return 0;
}
