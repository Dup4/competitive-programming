#include <bits/stdc++.h>
using namespace std;

int main() {
    srand(time(NULL));
    int n = 100000, m = 100000;
    printf("%d %d\n", n, m);
    for (int i = 1; i <= n; ++i) {
        printf("%d%c", 1000000, " \n"[i == n]);
    }
    for (int i = 1; i <= m; ++i) {
        int op = rand() % 3 + 1;
        if (op == 3) {
            printf("%d %d\n", op, rand() % n + 1);
        } else {
            int l = rand() % n + 1, r = rand() % n + 1;
            if (l > r) {
                swap(l, r);
            }
            printf("%d %d %d\n", op, l, r);
        }
    }
    return 0;
}
