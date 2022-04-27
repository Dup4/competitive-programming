#include <bits/stdc++.h>
using namespace std;
const int N = 1e3 + 10;
int n, a[N][N];

int main() {
    while (scanf("%d", &n) != EOF) {
        int x = -1, y = -1;
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                scanf("%d", &a[i][j]);
                if (a[i][j] == -1) {
                    x = i, y = j;
                    a[i][j] = 0;
                }
            }
        }
        for (int i = 1; i <= n; ++i) {
            int Min = 1e9;
            for (int j = 1; j <= n; ++j) {
                if (x == i && y == j)
                    continue;
                Min = min(Min, a[i][j]);
            }
            for (int j = 1; j <= n; ++j) {
                a[i][j] -= Min;
            }
        }
        for (int j = 1; j <= n; ++j) {
            int Min = 1e9;
            for (int i = 1; i <= n; ++i) {
                if (x == i && y == j)
                    continue;
                Min = min(Min, a[i][j]);
            }
            for (int i = 1; i <= n; ++i) {
                a[i][j] -= Min;
            }
        }
        printf("%d\n", -a[x][y]);
    }
    return 0;
}
