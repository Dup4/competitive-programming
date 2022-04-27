#include <bits/stdc++.h>
using namespace std;
int a[20][20], b[20][20], c[20][20];

int main() {
    for (int i = 1; i <= 5; ++i)
        for (int j = 1; j <= 10; ++j) scanf("%d", a[i] + j);
    for (int i = 1; i <= 5; ++i)
        for (int j = 1; j <= 10; ++j) scanf("%d", b[i] + j);
    int res = 10;
    for (int x = -10; x <= 10; ++x) {
        int F = 1;
        memset(c, 0, sizeof c);
        for (int i = 1; i <= 5; ++i) {
            for (int j = 1; j <= 10; ++j) {
                int ny = (j + x);
                if (ny <= 10 && ny >= 1) {
                    if (a[i][j]) {
                        if (b[i][ny] == 0)
                            F = 0;
                        else
                            c[i][ny] = 1;
                    }
                }
            }
        }
        for (int i = 1; i <= 5; ++i)
            for (int j = 1; j <= 10; ++j)
                if (b[i][j] && c[i][j] == 0)
                    if (j - x >= 1 && j - x <= 10)
                        F = 0;
        if (F)
            res = min(res, abs(x));
    }
    printf("%d\n", res);
    return 0;
}
