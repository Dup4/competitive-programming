#include <bits/stdc++.h>
using namespace std;

int n, m;

int main() {
    int T;
    scanf("%d", &T);
    for (int kase = 1; kase <= T; ++kase) {
        printf("Case #%d: ", kase);
        scanf("%d%d", &n, &m);
        if (n == 1) {
            printf("1.000000");
        } else {
            printf("0.500000");
        }
        printf(" ");
        if (m == 1) {
            printf("1.000000");
        } else {
            printf("%.6f", (m + 1) * 1.0 / (2 * m));
        }
        puts("");
    }
    return 0;
}
