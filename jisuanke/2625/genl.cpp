
#include <bits/stdc++.h>
using namespace std;

int main() {
    for (int n = 1; n <= 100; ++n) {
        cout << n << endl;
        for (int i = 1; i <= n; ++i) {
            printf("%d%c", i, " \n"[i == n]);
        }
    }
    return 0;
}
