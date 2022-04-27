#include <bits/stdc++.h>
using namespace std;

#define N 250010
const int p = 1e9 + 7;
int n, x, A, B;
// f[S][T]表示前9位为S，后9位为T的所有超集的方案数
int f[610][610];
void add(int &x, int y) {
    x += y;
    if (x >= p)
        x -= p;
}

int main() {
    while (scanf("%d", &n) != EOF) {
        memset(f, 0, sizeof f);
        int res = 0;
        for (int i = 1; i <= n; ++i) {
            scanf("%d", &x);
            A = x / 512, B = x % 512;
            int t = 0;
            for (int j = A; j <= 512; j = (j + 1) | A) {
                add(t, f[j][B]);
            }
            add(res, t);
            add(t, 1);
            for (int j = B; j >= 0; j = (j - 1) & B) {
                add(f[A][j], t);
                if (!j)
                    break;
            }
        }
        printf("%d\n", res);
    }
    return 0;
}
