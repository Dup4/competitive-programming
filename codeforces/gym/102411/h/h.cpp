#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 10;
int n, q, Max, a[N], sum[N], ans[N], vis[N];

int getans(int limit) {
    if (vis[limit])
        return ans[limit];
    vis[limit] = 1;
    if (Max > limit) {
        return ans[limit] = -1;
    }
    if (limit <= 1000) {
        int res = 1, pre = 0;
        for (int i = 1; i <= n; ++i) {
            if (a[i] + pre <= limit) {
                pre += a[i];
            } else {
                pre = a[i];
                ++res;
            }
        }
        return ans[limit] = res;
    } else {
        int res = 0, pos = 0;
        while (pos < n) {
            ++res;
            int nx = upper_bound(sum + 1, sum + 1 + n, limit + sum[pos]) - sum - 1;
            pos = nx;
        }
        return ans[limit] = res;
    }
}

int main() {
    while (scanf("%d", &n) != EOF) {
        memset(vis, 0, sizeof vis);
        sum[0] = 0;
        for (int i = 1; i <= n; ++i) {
            scanf("%d", a + i);
            Max = max(Max, a[i]);
            sum[i] = sum[i - 1] + a[i];
        }
        scanf("%d", &q);
        while (q--) {
            int need;
            scanf("%d", &need);
            int res = getans(need);
            if (res == -1)
                puts("Impossible");
            else
                printf("%d\n", res);
        }
    }
    return 0;
}
