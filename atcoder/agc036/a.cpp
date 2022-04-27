#include <bits/stdc++.h>
using namespace std;

#define ll long long
ll S, x[3], y[3];

int main() {
    while (scanf("%lld", &S) != EOF) {
        ll E9 = 1e9;
        x[0] = 0, y[0] = 0;
        x[2] = 1e9, y[2] = 1;
        y[1] = S / (E9) + (S % E9 != 0);
        x[1] = y[1] * E9 - S;
        for (int i = 0; i < 3; ++i) {
            printf("%lld %lld%c", x[i], y[i], " \n"[i == 2]);
        }
    }
    return 0;
}
