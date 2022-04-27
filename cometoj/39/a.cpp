#include <bits/stdc++.h>
using namespace std;

int main() {
    int T;
    cin >> T;
    while (T--) {
        int a[6] = {0};
        for (int i = 0, x; i < 5; ++i) {
            scanf("%d", &x);
            ++a[x];
        }
        int Max = 0, res = 0;
        for (int i = 1; i <= 5; ++i) {
            if (a[i] > Max) {
                Max = a[i];
                res = i;
            }
        }
        printf("%d\n", res);
    }
    return 0;
}
