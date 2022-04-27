#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define N 300010
#define varName(x) #x
#define DEBUG(...)           \
    {                        \
        printf("# ");        \
        printf(__VA_ARGS__); \
        puts("");            \
    }
int n, x;
ll a[N], f[N][3];

int main() {
    while (scanf("%d%d", &n, &x) != EOF) {
        for (int i = 1; i <= n; ++i) {
            scanf("%lld", a + i);
        }
        memset(f, 0, sizeof f);
        ll res = 0;
        for (int i = 1; i <= n; ++i) {
            f[i][0] = max(f[i - 1][0], 0ll) + a[i];
            f[i][1] = max(f[i - 1][0], max(f[i - 1][1], 0ll)) + a[i] * x;
            f[i][2] = max(f[i - 1][1], f[i - 1][2]) + a[i];
            cout << varName(f[i][0]) << " " << f[i][0] << endl;
            for (int j = 0; j < 3; ++j) {
                res = max(res, f[i][j]);
            }
        }
        printf("%lld\n", res);
    }
    return 0;
}
