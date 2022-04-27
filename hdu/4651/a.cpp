#include <bits/stdc++.h>
using namespace std;
#define f(x) (((x) * (3 * (x)-1)) >> 1)
#define g(x) (((x) * (3 * (x) + 1)) >> 1)
const int N = 1e5 + 10;
const int mod = 1e9 + 7;
int n, ans[N];

int main() {
    n = 100000;
    for (int i = 1; i <= n; ++i) ans[i] = 0;
    ans[0] = 1;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; f(j) <= i; ++j) {
            if (j & 1) {
                ans[i] = (ans[i] + ans[i - f(j)]) % mod;
            } else {
                ans[i] = (ans[i] - ans[i - f(j)] + mod) % mod;
            }
        }
        for (int j = 1; g(j) <= i; ++j) {
            if (j & 1) {
                ans[i] = (ans[i] + ans[i - g(j)]) % mod;
            } else {
                ans[i] = (ans[i] - ans[i - g(j)] + mod) % mod;
            }
        }
    }
    int _T;
    scanf("%d", &_T);
    while (_T--) {
        scanf("%d", &n);
        printf("%d\n", ans[n]);
    }
    return 0;
}
