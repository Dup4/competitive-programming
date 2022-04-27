#include <bits/stdc++.h>
using namespace std;

#define N 100010
int n, a[N], b[N];

bool ok(int *a) {
    if (a[2] + a[n] <= a[1])
        return 0;
    if (a[1] + a[n - 1] <= a[n])
        return 0;
    for (int i = 2; i < n; ++i) {
        if (a[i - 1] + a[i + 1] <= a[i]) {
            return 0;
        }
    }
    return 1;
}

int main() {
    while (scanf("%d", &n) != EOF) {
        for (int i = 1; i <= n; ++i) scanf("%d", a + i);
        sort(a + 1, a + 1 + n, [](int x, int y) {
            return x > y;
        });
        int mid = (n + 1) / 2;
        b[mid] = a[1];
        int i = mid - 1, j = mid + 1, k = 2;
        while (k <= n) {
            if (k % 2 == 0) {
                b[i] = a[k];
                --i;
            } else {
                b[j] = a[k];
                ++j;
            }
            ++k;
        }
        if (ok(b)) {
            puts("YES");
            for (int i = 1; i <= n; ++i) printf("%d%c", a[i], " \n"[i == n]);
        } else {
            puts("NO");
        }
    }
    return 0;
}
