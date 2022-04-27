#include <bits/stdc++.h>
using namespace std;

int main() {
    int T;
    scanf("%d", &T);
    for (int kase = 1; kase <= T; ++kase) {
        printf("Case %d: ", kase);
        int n, x, res = 0;
        scanf("%d", &n);
        for (int i = 1; i <= n; ++i) {
            scanf("%d", &x);
            res ^= max(0, x - 2);
        }
        printf("%d\n", res);
    }
    return 0;
}
