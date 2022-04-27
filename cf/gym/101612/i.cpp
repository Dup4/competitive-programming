#include <bits/stdc++.h>
using namespace std;

#define N 2000010
#define M 1010
#define pii pair<int, int>
#define fi first
#define se second
int n, x[M], y[M];
int a[N], b[N];

void File() {
    freopen("intel.in", "r", stdin);
    freopen("intel.out", "w", stdout);
}

void init() {
    memset(a, 0, sizeof a);
    memset(b, 0, sizeof b);
}
int main() {
    File();
    while (scanf("%d", &n) != EOF) {
        init();
        for (int i = 1; i <= n; ++i) {
            scanf("%d%d", x + i, y + i);
            x[i] += 1000001;
            y[i] += 1000001;
        }
        x[n + 1] = x[1], y[n + 1] = y[1];
        for (int i = 2; i <= n + 1; ++i) {
            if (x[i] == x[i - 1]) {
                int l = y[i], r = y[i - 1];
                if (l > r)
                    swap(l, r);
                ++l;
                ++a[l];
                --a[r + 1];
            } else {
                int l = x[i], r = x[i - 1];
                if (l > r)
                    swap(l, r);
                ++l;
                ++b[l];
                --b[r + 1];
            }
        }
        int res = 0;
        for (int i = 1; i <= 2000001; ++i) {
            a[i] += a[i - 1];
            b[i] += b[i - 1];
            if (a[i] > 2) {
                res += a[i] - 2;
            }
            if (b[i] > 2) {
                res += b[i] - 2;
            }
        }
        printf("%d\n", res);
    }
    return 0;
}
