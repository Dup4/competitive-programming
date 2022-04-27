#include <bits/stdc++.h>
using namespace std;

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int n;
        scanf("%d", &n);
        if (n % 2 == 0) {
            printf("%d\n", n / 2);
        } else {
            printf("%d\n", 1 + (n - 3) / 2);
        }
    }
    return 0;
}
