#include <bits/stdc++.h>
using namespace std;

#define N 100010
int n, a[N];

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        for (int i = 1; i <= n; ++i) scanf("%d", a + i);
        sort(a + 1, a + 1 + n);
        int res = 0;
        for (int i = 2; i < n; ++i) {
            res = max(res, min(a[i] - 1, i - 1));
        }
        printf("%d\n", res);
    }
    return 0;
}
