#include <bits/stdc++.h>
using namespace std;

int main() {
    freopen("auxiliary.in", "r", stdin);
    freopen("auxiliary.out", "w", stdout);
    int n;
    int mp[20];
    mp[2] = 1;
    mp[3] = 7;
    mp[4] = 4;
    mp[5] = 5;
    mp[6] = 9;
    mp[7] = 8;
    while (scanf("%d", &n) != EOF) {
        int x = n % 3;
        if (x == 0) {
            x = 0;
        } else if (x == 1) {
            n -= 4;
            x = 4;
        } else {
            x = 1;
        }
        printf("%d\n", n / 3 * 7 + x);
    }
    return 0;
}
