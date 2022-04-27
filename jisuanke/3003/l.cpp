#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 10;
int f[11][N], n, b;
inline int S(int b, int x) {
    int res = 0;
    while (x) {
        res += x % b;
        x /= b;
    }
    return res;
}

int main() {
    for (int i = 2; i <= 10; ++i) {
        for (int j = 1; j <= 1000000; ++j) {
            f[i][j] = f[i][j - 1] + S(i, j);
        }
    }
    int T;
    scanf("%d", &T);
    for (int kase = 1; kase <= T; ++kase) {
        printf("Case #%d: ", kase);
        scanf("%d%d", &n, &b);
        printf("%d\n", f[b][n]);
    }
    return 0;
}
