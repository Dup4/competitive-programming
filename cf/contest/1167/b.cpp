#include <bits/stdc++.h>
using namespace std;

int a[5], b[] = {4, 8, 15, 16, 23, 42};

int main() {
    printf("? 1 2\n");
    fflush(stdout);
    scanf("%d", a);
    printf("? 2 3\n");
    fflush(stdout);
    scanf("%d", a + 1);
    printf("? 4 5\n");
    fflush(stdout);
    scanf("%d", a + 2);
    printf("? 5 6\n");
    fflush(stdout);
    scanf("%d", a + 3);
    do {
        if (b[0] * b[1] == a[0] && b[1] * b[2] == a[1] && b[3] * b[4] == a[2] && b[4] * b[5] == a[3]) {
            printf("!");
            fflush(stdout);
            for (int i = 0; i < 6; ++i) {
                printf(" %d", b[i]);
                fflush(stdout);
            }
            puts("");
            fflush(stdout);
            break;
        }
    } while (next_permutation(b, b + 6));
    return 0;
}
