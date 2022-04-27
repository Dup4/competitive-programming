#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    while (scanf("%d%d", &n, &m) != EOF) {
        int cnt[2] = {0, 0};
        for (int i = 1, x; i <= n; ++i) {
            scanf("%d", &x);
            ++cnt[x % 2];
        }
        int res = 0;
        for (int i = 1, x; i <= m; ++i) {
            scanf("%d", &x);
            x %= 2;
            if (cnt[x ^ 1]) {
                ++res;
                --cnt[x ^ 1];
            }
        }
        printf("%d\n", res);
    }
    return 0;
}
