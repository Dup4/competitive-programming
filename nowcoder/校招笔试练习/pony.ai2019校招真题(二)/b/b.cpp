#include <bits/stdc++.h>
using namespace std;
using db = double;
const int N = 2e6 + 10;
const db eps = 1e-16;
int sgn(db x) {
    if (fabs(x) < eps)
        return 0;
    return x > 0 ? 1 : -1;
}
int n, h, a[N];
int que[N];
db f[N];

int main() {
    scanf("%d%d", &n, &h);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", a + i);
    }
    int l = 1, r = 0;
    f[1] = (a[1] - h);
    que[++r] = 1;
    puts("0");
    for (int i = 2; i <= n; ++i) {
        db k = (a[i] - h) * 1.0 / i;
        int _l = l, _r = r, res = 0;
        while (_r - _l >= 0) {
            int mid = (_l + _r) >> 1;
            if (sgn(k - f[que[mid]]) <= 0) {
                res = mid;
                _l = mid + 1;
            } else {
                _r = mid - 1;
            }
        }
        if (res != 0)
            res = que[res];
        printf("%d\n", res);
        f[i] = k;
        while (l <= r && sgn(f[que[r]] - f[i]) <= 0) --r;
        que[++r] = i;
    }
    return 0;
}
