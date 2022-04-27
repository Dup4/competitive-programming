#include <bits/stdc++.h>
using namespace std;

#define db double
#define ll long long
ll n, m, x, y;

int main() {
    while (scanf("%lld%lld%lld%lld", &n, &m, &x, &y) != EOF) {
        db res = 1ll * n * m * 1.0 / 2;
        bool F = 0;
        if (n % 2 == 0 && m % 2 == 0 && x == n / 2 && y == m / 2) {
            F = 1;
        }
        printf("%.15f %d\n", res, F);
    }
    return 0;
}
