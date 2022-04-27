#include <bits/stdc++.h>
using namespace std;

#define N 200010
int n, q, S;
int a[N], id[N];
int f[N];

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        S = min(n - 1, 200);
        for (int i = 1; i <= n; ++i) scanf("%d", a + i), id[a[i]] = i;
        memset(f, 0, sizeof f);
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= S; ++j) {
                if (a[i] > 1 && (a[i] - 1) % j == 0) {
                    if (id[a[i] - j] > i) {
                        ++f[j];
                    }
                }
            }
        }
        scanf("%d", &q);
        int op, x, y, k;
        while (q--) {
            scanf("%d", &op);
            if (op == 1) {
                scanf("%d%d", &x, &y);
                if (x == y)
                    continue;
                if (x > y)
                    swap(x, y);
                for (int i = 1; i <= S; ++i) {
                    if ((a[x] - 1) % i == 0) {
                        int pre = a[x] - i;
                        if (pre >= 1 && id[pre] <= y && id[pre] > x) {
                            --f[i];
                        }
                        int nx = a[x] + i;
                        if (nx <= n && id[nx] <= y && id[nx] > x) {
                            ++f[i];
                        }
                    }
                }
                for (int i = 1; i <= S; ++i) {
                    if ((a[y] - 1) % i == 0) {
                        int pre = a[y] - i;
                        if (pre >= 1 && id[pre] > x && id[pre] < y) {
                            ++f[i];
                        }
                        int nx = a[y] + i;
                        if (nx <= n && id[nx] > x && id[nx] < y) {
                            --f[i];
                        }
                    }
                }
                swap(id[a[x]], id[a[y]]);
                swap(a[x], a[y]);
            } else {
                scanf("%d", &k);
                if (k <= S) {
                    printf("%d\n", f[k] + 1);
                } else {
                    int res = 1;
                    int it = 1;
                    while (it + k <= n) {
                        if (id[it + k] < id[it])
                            ++res;
                        it += k;
                    }
                    printf("%d\n", res);
                }
            }
        }
    }
    return 0;
}
