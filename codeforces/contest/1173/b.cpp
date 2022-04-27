#include <bits/stdc++.h>
using namespace std;

#define N 1100
int n, m;

int main() {
    while (scanf("%d", &n) != EOF) {
        m = n / 2 + 1;
        printf("%d\n", m);
        int i = 1, j = 1;
        while (n--) {
            printf("%d %d\n", i, j);
            ++j;
            if (i == 1 && j == m) {
                i = m, j = 1;
            }
        }
    }
    return 0;
}
