#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 10;
int n, f[50], a[N], b[N];
void gao() {
    for (int i = 3; f[i] < N; ++i) {
        if (a[f[i - 1]] && a[f[i]]) {
            printf("%d %d\n", a[f[i - 1]], a[f[i]]);
            return;
        }
    }
    puts("impossible");
}
bool ok() {
    int pre = -1;
    for (int i = 1; i <= n; ++i) {
        if (b[i] == 1) {
            if (pre == -1)
                pre = i;
            else {
                printf("%d %d\n", pre, i);
                return 1;
            }
        }
    }
    return 0;
}

int main() {
    f[0] = 0;
    f[1] = 1, f[2] = 1;
    for (int i = 3; i <= 45; ++i) f[i] = f[i - 1] + f[i - 2];
    while (scanf("%d", &n) != EOF) {
        memset(a, 0, sizeof a);
        for (int i = 1; i <= n; ++i) scanf("%d", b + i), a[b[i]] = i;
        if (!ok())
            gao();
    }
    return 0;
}
