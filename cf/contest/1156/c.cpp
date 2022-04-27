#include <bits/stdc++.h>
using namespace std;

#define N 200010
int n, z, a[N];
int used[N];

int main() {
    while (scanf("%d%d", &n, &z) != EOF) {
        for (int i = 1; i <= n; ++i) {
            scanf("%d", a + i);
        }
        sort(a + 1, a + 1 + n);
        int res = 0;
        memset(used, 0, sizeof used);
        for (int i = n, j = (n + 1) / 2; i >= 1 && j >= 1; --i)
            if (!used[i]) {
                while (j >= 1 && a[i] - a[j] < z) {
                    --j;
                }
                if (j == 0) {
                    break;
                }
                ++res;
                used[j] = 1;
                --j;
            }
        printf("%d\n", res);
    }
    return 0;
}
