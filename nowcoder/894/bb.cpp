#include <bits/stdc++.h>
using namespace std;

#define N 1010
#define ll long long
int n, m;
ll L, R, a[N], b[N];

int main() {
    scanf("%d%d%lld%lld", &n, &m, &L, &R);
    for (int i = 1; i <= n; ++i) {
        scanf("%lld", a + i);
    }
    for (int i = 1; i <= m; ++i) {
        scanf("%lld", b + i);
    }
    b[m + 1] = 0;
    ll res = 0;
    for (int i = 1; i <= n; ++i) {
        ll sum = 0;
        for (int j = i; j <= n; ++j) {
            sum += a[j];
            int l = 1, r = 0;
            ll suml = b[1], sumr = 0;
            for (int k = 1; k <= m; ++k) {
                l = k;
                suml = b[k];
                r = k - 1;
                sumr = 0;
                while (l <= m && (sum < (L / (suml + b[l + 1]) + ((L % (suml + b[l + 1])) ? 1 : 0)))) {
                    ++l;
                    suml += b[l];
                }
                while (r < m && (sum <= (R / (sumr + b[r + 1])))) {
                    ++r;
                    sumr += b[r];
                }
                if (l <= r) {
                    res += r - l + 1;
                }
            }
        }
    }
    printf("%lld\n", res);
    return 0;
}
