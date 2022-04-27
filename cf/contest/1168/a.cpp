#include <bits/stdc++.h>
using namespace std;

#define N 300010
int n, m;
int a[N], b[N];

bool check(int x) {
    if (m - a[1] <= x) {
        b[1] = 0;
    } else {
        b[1] = a[1];
    }
    for (int i = 2; i <= n; ++i) {
        if (a[i] < b[i - 1]) {
            if (b[i - 1] - a[i] <= x) {
                b[i] = b[i - 1];
            } else {
                return false;
            }
        } else {
            if (b[i - 1] + m - a[i] <= x) {
                b[i] = b[i - 1];
            } else {
                b[i] = a[i];
            }
        }
    }
    return true;
}

int main() {
    while (scanf("%d%d", &n, &m) != EOF) {
        for (int i = 1; i <= n; ++i) {
            scanf("%d", a + i);
        }
        int l = 0, r = m, res = -1;
        while (r - l >= 0) {
            int mid = (l + r) >> 1;
            if (check(mid)) {
                r = mid - 1;
                res = mid;
            } else {
                l = mid + 1;
            }
        }
        printf("%d\n", res);
    }
    return 0;
}
