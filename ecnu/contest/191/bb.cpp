#include <bits/stdc++.h>
using namespace std;

#define N 200010
int n, a[N], b[N];
int main() {
    while (scanf("%d", &n) != EOF) {
        memset(a, 0, sizeof a);
        memset(b, 0, sizeof b);
        int res = 0, Max = 0;
        for (int i = 1, x; i <= n; ++i) scanf("%d", &x), a[x - 1] = 1, Max = x - 1;
        if (n == 1) {
            puts("1");
            continue;
        }
        for (int i = 1; i <= Max; ++i) {
            bool F = 1;
            int cnt = 0;
            for (int j = i; j <= Max; j += i) {
                if (a[j] == 0) {
                    F = 0;
                    break;
                }
                cnt += b[j];
            }
            if (cnt == Max / i)
                continue;
            if (F) {
                for (int j = i; j <= Max; j += i) {
                    b[j] = 1;
                }
                ++res;
            }
        }
        printf("%d\n", res);
    }
    return 0;
}
