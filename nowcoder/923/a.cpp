#include <bits/stdc++.h>
using namespace std;

int main() {
    int a, b, c;
    while (scanf("%d", &c) != EOF) {
        if (c == -1) {
            puts("No solution");
        } else {
            a = 2147483647;
            b = 2147483647 + c + 2;
            printf("%d %d\n", a, b);
        }
    }
    return 0;
}
