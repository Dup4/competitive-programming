#include <bits/stdc++.h>
using namespace std;

#define N 100010
int n, a[2][N];
int l[2], r[2];

bool cro(int x, int l, int r) {
    return x >= l && x <= r;
}

int main() {
    while (scanf("%d", &n) != EOF) {
        l[0] = l[1] = n + 1;
        r[0] = r[1] = -1;
        for (int i = 0; i < 2; ++i) {
            for (int j = 1; j <= n; ++j) {
                scanf("%d", a[i] + j);
                if (a[i][j] == 1) {
                    if (l[i] == n + 1) {
                        l[i] = j;
                    }
                    r[i] = j;
                }
            }
        }
        int L = int res = 0;
        for (int i = 0; i < 2; ++i) {
            for (int j = l[i]; j <= r[i]; ++j) {
                if (a[i][j] == 0) {
                    ++res;
                }
            }
        }
        if (l[0] != n + 1 && l[1] != n + 1) {
            if (!(cro(l[0], l[1], r[1]) || cro(r[0], l[1], r[1]) || cro(l[1], l[0], r[0]) || cro(r[1], l[0], r[0]))) {
                res += max(0, min(abs(l[0] - r[1]), abs(r[0] - l[1])));
            }
        }
        printf("%d\n", res);
    }
    return 0;
}
