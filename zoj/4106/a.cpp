#include <bits/stdc++.h>
using namespace std;

int main() {
    int T;
    cin >> T;
    while (T--) {
        int n;
        scanf("%d", &n);
        for (;; ++n) {
            if (n % 7 == 0 && n % 4) {
                break;
            }
        }
        printf("%d\n", n);
    }
    return 0;
}
