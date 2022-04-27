#include <bits/stdc++.h>
using namespace std;

#define N 2000010
int n, a[N], b[N], m;

int main() {
    while (scanf("%d%d%d", &n, &a[1], &m) != EOF) {
        for (int i = 2; i <= n; ++i) {
            a[i] = (a[i - 1] + 7 * i % m) % m;
        }
        for (int i = 1; i <= n; ++i) {
            for (int j = i; j <= n; j += i) {
                b[j] += a[i];
            }
        }
        int res = 0;
        for (int i = 1; i <= n; ++i) {
            res ^= b[i];
        }
        printf("%d\n", res);
    }
    return 0;
}
