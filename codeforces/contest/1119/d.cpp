#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 100010
int n, q;
ll a[N], b[N], c[N];

int main() {
    while (scanf("%d", &n) != EOF) {
        for (int i = 1; i <= n; ++i) scanf("%lld", a + i);
        sort(a + 1, a + 1 + n);
        n = unique(a + 1, a + 1 + n) - a - 1;
        for (int i = 2; i <= n; ++i) b[i - 1] = a[i] - a[i - 1];
        sort(b + 1, b + n);
        for (int i = 1; i < n; ++i) c[i] = c[i - 1] + b[i];
        scanf("%d", &q);
        ll l, r;
        for (int i = 1; i <= q; ++i) {
            scanf("%lld%lld", &l, &r);
            ll res = r - l + 1;
            int pos = upper_bound(b + 1, b + n, res) - b;
            res += c[pos - 1] + 1ll * (r - l + 1) * (n - pos);
            printf("%lld%c", res, " \n"[i == q]);
        }
    }
    return 0;
}
