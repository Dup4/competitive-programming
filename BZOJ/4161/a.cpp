#include <bits/stdc++.h>
using namespace std;
const int N = 4e3 + 10;
const int mod = 1e9 + 7;
template <class T>
void chmax(T &x, T y) {
    x = max(x, y);
}
template <class T>
void chmin(T &x, T y) {
    x = min(x, y);
}
int n, k;
int a[N], now[N];
int res[N], h[N];
void times(int *x, int *y) {
    static int tmp[N];
    memset(tmp, 0, sizeof(tmp));
    for (int i = 0; i <= k - 1; i++)
        for (int j = 0; j <= k - 1; j++) tmp[i + j] = (tmp[i + j] + 1ll * x[i] * y[j]) % mod;
    for (int i = 2 * k - 2; i >= k; i--) {
        for (int j = 1; j <= k; j++) tmp[i - j] = (tmp[i - j] + 1ll * tmp[i] * a[j]) % mod;
        tmp[i] = 0;
    }
    for (int i = 0; i <= k - 1; i++) x[i] = tmp[i];
}
int main() {
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= k; i++) {
        scanf("%d", a + i);
        if (a[i] < 0)
            a[i] += mod;
    }
    for (int i = 0; i <= k - 1; i++) {
        scanf("%d", h + i);
        if (h[i] < 0)
            h[i] += mod;
    }
    if (n <= k - 1) {
        printf("%d\n", h[n]);
        return 0;
    }
    n -= k - 1;
    res[0] = now[1] = 1;
    while (n != 0) {
        if (n & 1)
            times(res, now);
        n >>= 1;
        times(now, now);
    }
    for (int i = k; i <= 2 * k - 2; i++)
        for (int j = 1; j <= k; j++) h[i] = (h[i] + 1ll * h[i - j] * a[j]) % mod;
    int ans = 0;
    for (int i = 0; i <= k - 1; i++) ans = (ans + 1ll * h[k - 1 + i] * res[i]) % mod;
    printf("%d\n", ans);
    return 0;
}
