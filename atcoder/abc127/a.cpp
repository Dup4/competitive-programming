#include <bits/stdc++.h>
using namespace std;

int main() {
    int a, b;
    while (scanf("%d%d", &a, &b) != EOF) {
        if (a < 6) {
            b = 0;
        } else if (a < 13) {
            b /= 2;
        }
        printf("%d\n", b);
    }
    return 0;
}
