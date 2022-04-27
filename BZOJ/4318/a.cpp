#include <bits/stdc++.h>
using namespace std;

typedef double db;
const int N = 1e5 + 10;
int n;
db p[N], f[N], f2[N], ans;

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) scanf("%lf", p + i);
    memset(f, 0, sizeof f);
    memset(f2, 0, sizeof f2);
    ans = 0;
    for (int i = 1; i <= n; ++i) {
        ans += (3 * f2[i - 1] + 3 * f[i - 1] + 1) * p[i];
        f2[i] = (f2[i - 1] + 2 * f[i - 1] + 1) * p[i];
        f[i] = (f[i - 1] + 1) * p[i];
    }
    printf("%.1f\n", ans);
    return 0;
}
