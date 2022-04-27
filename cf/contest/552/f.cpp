#include <bits/stdc++.h>
using namespace std;

#define N 200010
#define pii pair<int, int>
#define fi first
#define se second
int n, m, k, a[N], f[N], sum[N];
pii s[N];

int main() {
    while (scanf("%d%d%d", &n, &m, &k) != EOF) {
        for (int i = 1; i <= n; ++i) {
            scanf("%d", a + i);
        }
        for (int i = 1; i <= m; ++i) {
            scanf("%d%d", &s[i].fi, &s[i].se);
        }
        sort(a + 1, a + 1 + n);
        n = k;
        sort(a + 1, a + 1 + k, [](int x, int y) {
            return x > y;
        });
        for (int i = 1; i <= n; ++i) {
            sum[i] = sum[i - 1] + a[i];
        }
        sort(s + 1, s + 1 + m, [](pii x, pii y) {
            if (x.fi == y.fi) {
                return x.se > y.se;
            } else {
                return x.fi < y.fi;
            }
        });
        int t = 1;
        for (int i = 2; i <= m; ++i) {
            if (s[i].fi > k) {
                break;
            }
            if (s[i].fi != s[i - 1].fi) {
                s[++t] = s[i];
            }
        }
        m = t;
        for (int i = 1; i <= n; ++i) {
            f[i] = f[i - 1] + a[i];
            for (int j = 1; j <= m; ++j) {
                if (s[j].fi > i) {
                    break;
                } else {
                    f[i] = min(f[i], f[i - s[j].fi] + sum[i - s[j].se] - sum[i - s[j].fi]);
                }
            }
        }
        printf("%d\n", f[n]);
    }
    return 0;
}
