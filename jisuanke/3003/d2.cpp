#include <bits/stdc++.h>
using namespace std;

int cnt[20], f[20], ans, n, x, y, s, k;

int exp(int a, int b) {
    int q = 1;
    while (b--) q *= a;
    return q;
}

void dfs(int t, int p) {
    if (t > y) {
        if (k - s == x) {
            for (int i = 1; i <= y; ++i) printf("%d ", f[i]);
            printf("\n");
        }
        return;
    }
    for (int i = p; k * exp(i, y - t + 1) - s - i * (y - t + 1) <= x; ++i) {
        f[t] = i;
        k *= i;
        s += i;
        dfs(t + 1, i);
        k /= i;
        s -= i;
    }
}

int main() {
    int T;
    cnt[0] = 1;
    for (int i = 1; i <= 15; ++i) cnt[i] = cnt[i - 1] * 2;
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        ans = 0;
        for (y = 2; cnt[y] - 2 * y <= n - y; ++y) {
            x = n - y;
            s = 0;
            k = 1;
            dfs(1, 2);
        }
        printf("%d\n", ans);
    }
    return 0;
}
.  //
