#include <bits/stdc++.h>
using namespace std;

#define db double
int l, r, L, R;
db f(db x) {
    return max(0.0, (x - l) * 1.0 * ((L + R) * 1.0 / 2 - x) / (r - l));
}

int main() {
    while (scanf("%d%d%d%d", &l, &r, &L, &R) != EOF) {
        int x = 2 * l + L + R;
        if (x >= 4 * l && x <= 4 * r) {
            printf("%.4f\n", f(x * 1.0 / 4));
        } else {
            printf("%.4f\n", max(0.0, f(r)));
        }
    }
    return 0;
}
