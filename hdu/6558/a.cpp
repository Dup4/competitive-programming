#include <bits/stdc++.h>
using namespace std;

#define db double
db f[300], p;

int main() {
    int T;
    scanf("%d", &T);
    for (int kase = 1; kase <= T; ++kase) {
        printf("Case %d: ", kase);
        scanf("%lf", &p);
        p *= 0.01;
        f[200] = 1.0 / p;
        for (int i = 200; i >= 4; --i) {
            db q = i * 0.01 / 2;
            f[i] = p * (1 - q) * f[min(200, i + 4)] + (1 - p) * f[min(200, i + 3)] + 1;
        }
        printf("%.12f\n", f[4]);
    }
    return 0;
}
