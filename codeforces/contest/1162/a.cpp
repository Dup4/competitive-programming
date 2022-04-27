#include <bits/stdc++.h>
using namespace std;

#define N 110
int n, h, m;
int a[N];

int main() {
    while (scanf("%d%d%d", &n, &h, &m) != EOF) {
        for (int i = 1; i <= n; ++i) {
            a[i] = h;
        }
        for (int i = 1, l, r, x; i <= m; ++i) {
            scanf("%d%d%d", &l, &r, &x);
            for (int j = l; j <= r; ++j) {
                a[j] = min(a[j], x);
            }
        }
        int res = 0;
        for (int i = 1; i <= n; ++i) {
            res += a[i] * a[i];
        }
        printf("%d\n", res);
    }
    return 0;
}
