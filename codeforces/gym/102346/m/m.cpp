#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10;
int n, m, T, a[N];

int calc(int x) {
    int tot = x * T;
    int res = 1, sum = 0;
    for (int i = 1; i <= n; ++i) {
        if (a[i] > tot)
            return 1e9;
        if (a[i] + sum <= tot) {
            sum += a[i];
        } else {
            sum = a[i];
            ++res;
        }
    }
    return res;
}

int main() {
    scanf("%d%d%d", &n, &m, &T);
    for (int i = 1; i <= n; ++i) scanf("%d", a + i);
    int l = 1, r = 1e9 / T + 5, res = 1e9;
    while (r - l >= 0) {
        int mid = (l + r) >> 1;
        if (calc(mid) <= m) {
            r = mid - 1;
            res = mid;
        } else {
            l = mid + 1;
        }
    }
    printf("%d\n", res);
    return 0;
}
