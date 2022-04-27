#include <bits/stdc++.h>
using namespace std;

#define N 200010
#define M 500010
#define D 20
int n, q;
int l[N], r[N];
int f[M][D];

int work(int x, int y) {
    int ans = 0;
    for (int i = D - 1; i >= 0; --i) {
        if (f[x][i] < y) {
            x = f[x][i];
            ans |= (1 << i);
        }
    }
    x = f[x][0];
    ++ans;
    if (x < y)
        ans = -1;
    return ans;
}

int main() {
    while (scanf("%d%d", &n, &q) != EOF) {
        for (int i = 1; i <= n; ++i) {
            scanf("%d%d", l + i, r + i);
            ++l[i], ++r[i];
        }
        memset(f, 0, sizeof f);
        for (int i = 1; i <= n; ++i) {
            f[l[i]][0] = max(f[l[i]][0], r[i]);
        }
        for (int i = 1; i < M; ++i) {
            f[i][0] = max(f[i][0], max(i, f[i - 1][0]));
            for (int j = 1; j < D; ++j) {
                f[i][j] = max(f[i][j], max(f[i][j - 1], f[i - 1][j]));
            }
        }

        for (int j = 1; j < D; ++j) {
            for (int i = 1; i < M; ++i) {
                f[i][j] = max(f[i][j], f[f[i][j - 1]][j - 1]);
            }
        }
        int x, y;
        while (q--) {
            scanf("%d%d", &x, &y);
            ++x, ++y;
            printf("%d\n", work(x, y));
        }
    }
    return 0;
}
