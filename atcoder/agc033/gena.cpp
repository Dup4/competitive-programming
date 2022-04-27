#include <bits/stdc++.h>
using namespace std;

int main() {
    int n = 1000, m = 1000;
    printf("%d %d\n", n, m);
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (i == 500 && j == 500) {
                printf("#");
            } else {
                printf(".");
            }
            if (j == m) {
                puts("");
            }
        }
    }
    return 0;
}
