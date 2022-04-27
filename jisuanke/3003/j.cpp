#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10;
const int mod = 1e9 + 7;
int n, a[N], f[N], limit, tot, res;
inline void add(int &x, int y) {
    x += y;
    while (x >= mod) x -= mod;
    while (x < 0) x += mod;
}
inline int ceil(int x, int y) {
    return (x + y - 1) / y;
}
inline int floor(int x, int y) {
    return x / y;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        tot = 0;
        for (int i = 1; i <= n; ++i) scanf("%d", a + i), tot += a[i];
        sort(a + 1, a + 1 + n);
        limit = ceil(tot, 2);
        for (int i = 0; i <= limit; ++i) f[i] = 0;
        f[0] = 1;
        res = 0;
        for (int i = n; i >= 1; --i) {
            int x = a[i];
            int l = ceil(tot - 2 * x, 2), r = floor(tot - x, 2);
            for (int j = l; j <= r; ++j) add(res, f[j]);
            for (int j = limit; j >= x; --j) add(f[j], f[j - x]);
        }
        printf("%d\n", res);
    }
    return 0;
}
