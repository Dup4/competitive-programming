#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 2010
const ll p = 1e9 + 7;
int n, m;
int a[N], b[N];
ll f[N][N];
void add(ll &x, ll y) {
    x += y;
    if (x >= p) {
        x -= p;
    }
}

int main() {
    while (scanf("%d%d", &n, &m) != EOF) {
        for (int i = 1; i <= n; ++i) {
            scanf("%d", a + i);
        }
        for (int i = 1; i <= m; ++i) {
            scanf("%d", b + i);
        }
        memset(f, 0, sizeof f);
        //	for (int i = 1; i <= max(n, m); ++i) {
        //		f[i][0] = 1;
        //		f[0][i] = 1;
        //	}
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                add(f[i][j], f[i - 1][j]);
                add(f[i][j], f[i][j - 1]);
                add(f[i][j], p - f[i - 1][j - 1]);
                if (a[i] == b[j]) {
                    add(f[i][j], f[i - 1][j - 1] + 1);
                }
            }
        }
        printf("%lld\n", f[n][m] + 1);
    }
    return 0;
}
