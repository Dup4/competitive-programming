#include <bits/stdc++.h>
using namespace std;

#define ll long long

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        ll a, b, c;
        scanf("%lld%lld%lld", &a, &b, &c);
        printf("%lld\n", (a + b + c) / 2);
    }
    return 0;
}
