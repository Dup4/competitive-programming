#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1e5 + 10, mod = 1e9 + 7;
int n, a[N], pre[N];
ll f[N];
template <class T1, class T2>
void chadd(T1 &x, T2 y) {
    x += y;
    while (x >= mod) x -= mod;
    while (x < 0) x -= mod;
}

int main() {
    while (scanf("%d", &n) != EOF) {
        for (int i = 1; i <= n; ++i) scanf("%d", a + i);
        memset(f, 0, sizeof f);
        memset(pre, -1, sizeof pre);
        f[0] = 1;
        for (int i = 1; i <= n; ++i) {
            f[i] = (f[i - 1] << 1) % mod;
            if (pre[a[i]] != -1) {
                chadd(f[i], mod - f[pre[a[i]] - 1]);
            }
            pre[a[i]] = i;
        }
        printf("%lld\n", (f[n] - 1 + mod) % mod);
    }
    return 0;
}
