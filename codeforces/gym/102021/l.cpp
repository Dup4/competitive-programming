#include <bits/stdc++.h>

using namespace std;

const int N = 110;

int main() {
    int n, m;
    int a[N][N], b[N][N];
    scanf("%d%d", &n, &m);
    for (int i = 0; i <= n + 1; ++i)
        for (int j = 0; j <= m + 1; ++j) {
            scanf("%d", &a[i][j]);
            b[i][j] = 0;
        }
    int flag = 0;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            if (a[i - 1][j - 1] > 1 || a[i - 1][j - 1] < 0) {
                flag = 1;
                break;
            } else if (a[i - 1][j - 1] == 1) {
                b[i][j] = 1;
                for (int x = -1; x < 2; ++x)
                    for (int y = -1; y < 2; ++y) a[i + x][j + y]--;
            } else
                b[i][j] = 0;
    for (int i = 0; i <= n + 1; ++i)
        for (int j = 0; j <= m + 1; ++j)
            if (a[i][j] != 0) {
                flag = 1;
                break;
            }
    if (flag == 1)
        puts("impossible");
    else {
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j)
                if (b[i][j] == 1)
                    printf("X");
                else
                    printf(".");
            printf("\n");
        }
    }
    return 0;
}
