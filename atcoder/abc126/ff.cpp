#include <bits/stdc++.h>
using namespace std;

int main() {
    for (int i = 1;; ++i) {
        int n = (1 << i) - 1;
        int tot = 0;
        for (int j = 1; j <= n; ++j) {
            tot ^= j;
        }
        if (tot == 0) {
            printf("%d\n", n);
        }
    }
    return 0;
}
