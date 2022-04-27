#include <bits/stdc++.h>
using namespace std;

#define N 100010
int n;
int a[10][N];

bool ok() {
    for (int j = 1; j <= n; ++j) {
        int x = a[1][j], y = a[2][j], z = a[3][j];
        int xx = (x - 1) / 3, yy = (y - 1) / 3, zz = (z - 1) / 3;
        if (xx != yy || xx != zz)
            return 0;
        if ((y > x && y > z) || (y < x && y < z))
            return 0;
        if (abs(xx + 1 - j) & 1)
            return 0;
    }
    return 1;
}

int main() {
    while (scanf("%d", &n) != EOF) {
        for (int i = 1; i <= 3; ++i) {
            for (int j = 1; j <= n; ++j) {
                scanf("%d", a[i] + j);
            }
        }
        puts(ok() ? "Yes" : "No");
    }
    return 0;
}
