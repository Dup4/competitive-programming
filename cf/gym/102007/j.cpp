#include <bits/stdc++.h>

using namespace std;

using db = double;

const db eps = 1e-8;

int sgn(db x) {
    if (fabs(x) < eps)
        return 0;
    else
        return x > 0 ? 1 : -1;
}

inline db F(db a, db b, db c) {
    db p = (a + b + c) / 2.0;
    db res = sqrt(p * (p - a) * (p - b) * (p - c));
    return res;
}

inline db f(db a, db b, db c, db d) {
    db res = 0.0;
    db l = max(fabs(a - b), fabs(c - d));
    db r = min(fabs(a + b), fabs(c + d));
    for (db e = l; e < r; e += 0.0005) {
        if (a + b - e <= 0)
            continue;
        if (a + e - b <= 0)
            continue;
        if (b + e - a <= 0)
            continue;

        if (c + d - e <= 0)
            continue;
        if (c + e - d <= 0)
            continue;
        if (d + e - a <= 0)
            continue;

        res = max(res, F(a, b, e) + F(c, d, e));
    }
    return res;
}

int a, b, c, d;

int main() {
    while (scanf("%d %d %d %d", &a, &b, &c, &d) != EOF) {
        if (a == b && b == c && c == d) {
            db res = a * b;
            printf("%.10f\n", res);
            continue;
        }
        db res = f(a, b, c, d);
        res = max(res, f(a, c, b, d));
        res = max(res, f(a, d, b, c));
        printf("%.15f\n", res);
    }
    return 0;
}
