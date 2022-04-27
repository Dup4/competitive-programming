#include <bits/stdc++.h>

using namespace std;

int f[100000 + 10];

int main() {
    int n, x, y;
    x = y = 0;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &f[i]);
        if (f[i] == 1)
            ++x;
        else
            ++y;
    }
    f[0] = f[n];
    for (int i = 1; i <= n; ++i) {
        int a = x, b = y;
        if (f[i - 1] > 1) {
            ++a;
            --b;
        }
        if (a % 2 == 0 && b % 2 == 0)
            printf("Second\n");
        else
            printf("First\n");
    }
    return 0;
}
