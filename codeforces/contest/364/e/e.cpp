#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 2e3 + 5e2 + 10;
int n, m, K, a[N][N], b[N], cnt[N * N];

int main() {
    while (scanf("%d%d%d", &n, &m, &K) != EOF) {
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                scanf("%1d", a[i] + j);
            }
        }
        ll res = 0;
        for (int l = 1; l <= n; ++l) {
            memset(b, 0, sizeof b);
            for (int r = l; r <= n; ++r) {
                int tot = 0;
                cnt[0] = 1;
                for (int i = 1; i <= m; ++i) {
                    b[i] += a[r][i];
                    tot += b[i];
                    if (tot - K >= 0)
                        res += cnt[tot - K];
                    ++cnt[tot];
                }
                tot = 0;
                for (int i = 1; i <= m; ++i) {
                    tot += b[i];
                    --cnt[tot];
                }
            }
        }
        printf("%lld\n", res);
    }
    return 0;
}
