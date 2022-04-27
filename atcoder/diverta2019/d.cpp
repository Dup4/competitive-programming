#include <bits/stdc++.h>
using namespace std;

#define ll long long
ll n;

int main() {
    while (scanf("%lld", &n) != EOF) {
        ll res = 0;
        for (ll i = 1, j; i <= n; i = j + 1) {
            j = n / (n / i);
            ll x = n / i;
            if (n % x == 0) {
                ll m = n / x - 1;
                if (m >= i && m <= j) {
                    res += m;
                }
            }
        }
        printf("%lld\n", res);
    }
    return 0;
}
