#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define db double

int main() {
    int n;
    while (cin >> n) {
        int x, tot = 0;
        while (n--) {
            cin >> x;
            if (x == 0) {
                ++tot;
                continue;
            }
            tot += (x / 70) + (x % 70 != 0);
        }
        printf("%.1f\n", tot * 0.1);
    }
    return 0;
}
