#include <bits/stdc++.h>
using namespace std;

#define N 1010
#define ll long long
int n, m;
ll L, R, a[N], b[N], c[N * N];

int main() {
    while (scanf("%d%d%lld%lld", &n, &m, &L, &R) != EOF) {
        for (int i = 1; i <= n; ++i) {
            scanf("%lld", a + i);
        }
        for (int i = 1; i <= m; ++i) {
            scanf("%lld", b + i);
        }
        c[0] = 0;
        for (int i = 1; i <= m; ++i) {
            ll sum = 0;
            for (int j = i; j <= m; ++j) {
                sum += b[j];
                c[++c[0]] = sum;
            }
        }
        sort(c + 1, c + 1 + c[0]);
        m = c[0];
        ll res = 0;
        for (int i = 1; i <= n; ++i) {
            ll sum = 0;
            for (int j = i; j <= n; ++j) {
                sum += a[j];
                int l = lower_bound(c + 1, c + 1 + m, (L / sum + (L % sum ? 1 : 0))) - c;
                int r = upper_bound(c + 1, c + 1 + m, (R / sum)) - c - 1;
                res += max(0, r - l + 1);
            }
        }
        printf("%lld\n", res);
    }
    return 0;
}
