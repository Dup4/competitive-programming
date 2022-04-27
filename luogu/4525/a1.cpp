#include <bits/stdc++.h>
using namespace std;
using db = double;
const db eps = 1e-8;
db a, b, c, d;
db f(db x) {
    return (c * x + d) / (a * x + b);
}

db Simpson(db L, db M, db R, db fL, db fM, db fR, int dep) {
    db M1 = (L + M) / 2, M2 = (M + R) / 2, fM1 = f(M1), fM2 = f(M2);
    db g1 = (M - L) * (fL + 4 * fM1 + fM) / 6;
    db g2 = (R - M) * (fM + 4 * fM2 + fR) / 6;
    db g = (R - L) * (fL + 4 * fM + fR) / 6;
    //迭代次数和精度控制
    if (dep > 11 && fabs(g - g1 - g2) < eps)
        return g;
    return Simpson(L, M1, M, fL, fM1, fM, dep + 1) + Simpson(M, M2, R, fM, fM2, fR, dep + 1);
}

int main() {
    db l, r;
    scanf("%lf%lf%lf%lf%lf%lf", &a, &b, &c, &d, &l, &r);
    db mid = l + (r - l) / 2;
    printf("%.6f\n", Simpson(l, mid, r, f(l), f(mid), f(r), 0));
    return 0;
}
