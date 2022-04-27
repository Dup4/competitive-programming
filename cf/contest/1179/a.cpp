#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 400010
#define pii pair<int, int>
#define fi first
#define se second
int n, q, a[N], b[N];
pii res[N];

int main() {
    while (scanf("%d%d", &n, &q) != EOF) {
        int Max = 0;
        for (int i = 1; i <= n; ++i) {
            scanf("%d", a + i);
            Max = max(Max, a[i]);
        }
        int cnt = 0;
        int l = 1, r = n;
        memset(res, -1, sizeof res);
        while (a[l] < Max) {
            ++cnt;
            int x = a[l], y = a[l + 1];
            res[cnt] = pii(x, y);
            if (x < y)
                swap(x, y);
            ++l;
            a[l] = x;
            a[++r] = y;
        }
        for (int i = 1; i <= n; ++i) {
            b[i] = a[l + i - 1];
        }
        ll po;
        while (q--) {
            scanf("%lld", &po);
            if (po <= cnt) {
                printf("%d %d\n", res[po].fi, res[po].se);
            } else {
                po -= cnt;
                po -= 1;
                po %= (n - 1);
                po += 1;
                printf("%d %d\n", b[1], b[po + 1]);
            }
        }
    }
    return 0;
}
