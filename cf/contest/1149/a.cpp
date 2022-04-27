#include <bits/stdc++.h>
using namespace std;

int cnt[3];

int main() {
    int n;
    while (scanf("%d", &n) != EOF) {
        cnt[0] = cnt[1] = 0;
        for (int i = 1, x; i <= n; ++i) {
            scanf("%d", &x);
            ++cnt[x];
        }
        if (cnt[1] == 0 || cnt[2] == 0) {
            for (int i = 1; i <= n; ++i) {
                int x = cnt[1] ? 1 : 2;
                printf("%d%c", x, " \n"[i == n]);
            }
        } else {
            --cnt[1];
            --cnt[2];
            printf("2 1");
            while (cnt[2]--) {
                printf(" 2");
            }
            while (cnt[1]--) {
                printf(" 1");
            }
            puts("");
        }
    }
    return 0;
}
