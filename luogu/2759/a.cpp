#include <bits/stdc++.h>
using namespace std;

#define ll long long
ll n;

ll get(ll x) {
    return floor(1.0 * x * log(x) / log(10));
}

int main() {
    while (scanf("%lld", &n) != EOF) {
        --n;
        ll l = 1, r = 1e15, res = -1;
        while (r - l >= 0) {
            ll mid = (l + r) >> 1;
            if (get(mid) >= n) {
                r = mid - 1;
                res = mid;
            } else {
                l = mid + 1;
            }
        }
        printf("%lld\n", res);
    }
    return 0;
}
