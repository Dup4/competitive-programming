#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 100010
int n;
ll k, a[N];

int main() {
    while (scanf("%d%lld", &n, &k) != EOF) {
        for (int i = 1; i <= n; ++i) {
            scanf("%lld", a + i);
            a[i] += a[i - 1];
        }
        ll res = 0;
        for (int i = 1, j = 1; i <= n; ++i) {
            while (j <= n && a[j] - a[i - 1] < k) {
                ++j;
            }
            if (j == n + 1) {
                break;
            }
            res += n - j + 1;
        }
        printf("%lld\n", res);
    }
    return 0;
}
