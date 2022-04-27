#include <bits/stdc++.h>
using namespace std;

#define ll long long
ll l, r, k;
ll f(ll x) {
    return x - x / (k + 1);
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%lld%lld%lld", &l, &r, &k);
        ++l, ++r;
        if (k & 1) {
            printf("%lld\n", r - l + 1);
        } else {
            printf("%lld\n", f(r) - f(l - 1));
        }
    }
    return 0;
}
