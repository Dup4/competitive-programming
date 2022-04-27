#include <bits/stdc++.h>
using namespace std;

#define ll long long

int main() {
    ll a, b, c;
    while (scanf("%lld%lld%lld", &a, &b, &c) != EOF) {
        ll res = c * 2;
        if (a == b) {
            res += a + b;
        } else {
            res += 2ll * min(a, b) + 1;
        }
        printf("%lld\n", res);
    }
    return 0;
}
