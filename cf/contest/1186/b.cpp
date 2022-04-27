#include <bits/stdc++.h>
using namespace std;

#define ll long long

ll solve(ll n, ll m) {
    ll base = (m + 1) / 2;
    if (n % 3 == 0) {
        return (n / 3) * base;
    } else if (n % 3 == 1) {
        return (n / 3) * base + (m + 1) / 3;
    } else if (n % 3 == 2) {
        return ((n + 1) / 3) * base;
    } else {
        assert(0);
    }
}

int main() {
    ll n, m;
    while (scanf("%lld%lld", &n, &m) != EOF) {
        printf("%lld\n", max(solve(n, m), solve(m, n)));
    }
    return 0;
}
