#include <bits/stdc++.h>
using namespace std;

#define N 100010
int n, a[N], b[N];

int main() {
    int _T;
    scanf("%d", &_T);
    while (_T--) {
        scanf("%d", &n);
        for (int i = 1; i <= n; ++i) {
            scanf("%d", a + i);
            b[i] = 0;
        }
        int res = 0, ori;
        for (int i = 2; i < n; ++i) {
            if (a[i] > a[i - 1] && a[i] > a[i + 1]) {
                b[i] = 1;
                ++res;
            }
        }
        ori = res;
        for (int i = 1; i <= n; ++i) {
            int tmp = ori;
            if (i == 1) {
                if (b[i + 1] == 1) {
                    --tmp;
                }
            } else if (i == n) {
                if (b[i - 1] == 1) {
                    --tmp;
                }
            } else {
                if (b[i - 1] == 1) {
                    if (a[i - 1] <= a[i + 1]) {
                        --tmp;
                    }
                } else {
                    if (a[i - 1] > a[i + 1] && (i - 2 >= 1 && a[i - 1] > a[i - 2])) {
                        ++tmp;
                    }
                }
                if (b[i + 1] == 1) {
                    if (a[i + 1] <= a[i - 1]) {
                        --tmp;
                    }
                } else {
                    if (a[i + 1] > a[i - 1] && (i + 2 <= n && a[i + 1] > a[i + 2])) {
                        ++tmp;
                    }
                }
            }
            res = min(res, tmp);
        }
        printf("%d\n", res);
    }
    return 0;
}
