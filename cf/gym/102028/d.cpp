#include <bits/stdc++.h>

using namespace std;

using db = double;

const db PI = acos(-1.0);
const db eps = 1e-8;

int sgn(db x) {
    if (fabs(x) < eps)
        return 0;
    else
        return x > 0 ? 1 : -1;
}

db a, b, r, d;

int main() {
    int _T;
    scanf("%d", &_T);
    while (_T--) {
        scanf("%lf %lf %lf %lf", &a, &b, &r, &d);
        d = d / 180 * PI;
        db arc = atan2(b, (a + r));
        db res = 0.0;
        if (sgn(arc - d) <= 0) {
            res = sqrt(b * b + (a + r) * (a + r)) - r;
        } else {
            res = sqrt(b * b + (a + r) * (a + r)) * cos(arc - d) - r;
        }
        printf("%.12f\n", res);
    }
    return 0;
}
