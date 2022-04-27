#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 20
int n, a[N][N];

ll C(int n, int m) {
    ll res = 1;
    for (int i = 1; i <= n; ++i) res *= i;
    for (int i = 1; i <= m; ++i) res /= i;
    for (int i = 1; i <= n - m; ++i) res /= i;
    return res;
}

ll f(int x, int y) {
    return C(x + y, x);
}

int main() {
    while (scanf("%d", &n) != EOF) {
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                scanf("%d", a[i] + j);
            }
        }
        ll res = 0;
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                res += a[i][j] * f(i - 1, j - 1) * f(n - i, n - j);
            }
        }
        printf("%lld\n", res);
    }
    return 0;
}
