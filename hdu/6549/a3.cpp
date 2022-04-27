#include <bits/stdc++.h>
using namespace std;

#define N 100010
int n, l, k;
char s[N];
int fa[N];
int f[N][15];

void Min(int &x, int y) {
    if (x > y)
        x = y;
}

int main() {
    scanf("%d%d%d", &n, &l, &k);
    k = min(n, k);
    scanf("%s", s);
    int tot = 0;
    fa[0] = tot;
    for (int i = 1; i < n; ++i) {
        if (s[i] == s[i - 1]) {
            fa[i] = fa[i - 1];
        } else {
            fa[i] = tot++;
        }
    }
    memset(f, 0x3f, sizeof f);
    f[0][0] = 1;
    f[0][1] = 0;
    for (int i = 1; i < n; ++i) {
        for (int j = 1; j <= k; ++j) {
            int pos = max(i - l, 0);
            f[i][j] = min(f[pos][j - 1] + 1, f[pos][j] + 1);
            if (fa[i] == fa[pos + 1]) {
                f[i][j] = min(f[i][j], f[pos][j - 1]);
                int pos2 = max(pos - 1, 0);
                if (s[i] == s[pos2]) {
                    f[i][j] = min(f[i][j], f[pos][j]);
                }
            }
        }
    }
    printf("%d\n", f[n - 1][k]);
    return 0;
}
