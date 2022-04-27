#include <bits/stdc++.h>
using namespace std;

#define N 220
#define ll long long
char s[N];
int pos[N];
ll f[N][N];
int n;
ll k;

int main() {
    while (scanf("%d%lld", &n, &k) != EOF) {
        scanf("%s", s + 1);
        memset(pos, -1, sizeof pos);
        f[0][0] = 1;
        for (int i = 1; i <= n; ++i) {
            int d = pos[s[i]];
            pos[s[i]] = i;
            f[i][0] = f[i][1] = 1;
            for (int j = 1; j <= n; ++j) {
                f[i][j] += f[i - 1][j];
                f[i][j + 1] = f[i - 1][j];
                if (d != -1 && j - i + d >= 0) {
                    f[i][j] -= f[d - 1][j - i + d];
                }
            }
        }
        ll res = 0;
        for (int i = 0; i <= n; ++i) {
            if (f[n][i] >= k) {
                res += k * i;
                k = 0;
                break;
            } else {
                res += f[n][i] * i;
                k -= f[n][i];
            }
        }
        if (k > 0) {
            puts("-1");
        } else {
            printf("%lld\n", res);
        }
    }
    return 0;
}
