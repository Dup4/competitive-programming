#include <bits/stdc++.h>
using namespace std;

#define N 100010
int n, m, f[N], b[20], num[N];
struct node {
    int sze, s;
    node() {}
    void scan() {
        scanf("%d", &sze);
        s = 0;
        for (int i = 1, x; i <= sze; ++i) {
            scanf("%d", &x);
            s |= (1 << (x - 1));
        }
    }
    bool operator<(const node &other) const {
        return sze < other.sze;
    }
} a[N];

int main() {
    for (int i = 0; i < (1 << 15) - 1; ++i) {
        num[i] = 0;
        int t = i;
        while (t) {
            num[i] += t % 2;
            t /= 2;
        }
    }
    while (scanf("%d%d", &n, &m) != EOF) {
        int sum = 0, res = 0;
        for (int i = 1; i <= n; ++i) scanf("%d", b + i), sum += b[i];
        sort(b + 1, b + 1 + n, [](int x, int y) {
            return x > y;
        });
        for (int i = 1; i <= m; ++i) a[i].scan();
        memset(f, 0, sizeof f);
        sort(a + 1, a + 1 + m);
        int D = (1 << n) - 1;
        for (int i = 1; i <= m; ++i) {
            int now = D ^ a[i].s;
            f[a[i].s] = max(f[a[i].s], b[a[i].sze]);
            for (int j = now; j > 0; j = (j - 1) & now) {
                f[j | a[i].s] = max(f[j | a[i].s], f[j] + b[num[j] + a[i].sze]);
            }
        }
        for (int i = 0; i < D; ++i) res = max(res, f[i]);
        printf("%d\n", sum - res);
    }
    return 0;
}
