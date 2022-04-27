#include <bits/stdc++.h>
using namespace std;
using db = double;
const db eps = 1e-7;
db a;
db f(db x) {
    return pow(x, a / x - x);
}
//区间[a,b]上的辛普森值，已知区间长度l和端点及中点处的函数值A，B，C
db simpson(db l, db A, db B, db C) {
    return (A + 4 * C + B) * l / 6;
}
db asr(db a, db b, db eps, db A, db B, db C) {
    db l = b - a;
    db c = a + l / 2;
    db D = f(a + l / 4), E = f(a + 3 * l / 4);
    db L = simpson(l / 2, A, C, D), R = simpson(l / 2, C, B, E), AB = simpson(l, A, B, C);
    if (fabs(L + R - AB) <= 15 * eps)
        return L + R + (L + R - AB) / 15;
    else
        return asr(a, c, eps / 2, A, C, D) + asr(c, b, eps / 2, C, B, E);
}
int main() {
    scanf("%lf%lf%lf%lf%lf%lf", &a, &b, &c, &d, &l, &r);
    printf("%.6f\n", asr(l, r, eps, f(l), f(r), f(l + (r - l) / 2)));
    return 0;
}
