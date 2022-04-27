#include <bits/stdc++.h>
using namespace std;
typedef double db;
int n;
db L, R, a[110], b[110];
const db eps = 1e-10;
const db PI = acos(-1.0);
int sgn(db x) {
    if (fabs(x) < eps)
        return 0;
    return x < 0 ? -1 : 1;
}

db f(db x) {
    b[n] = a[n];
    for (int i = n - 1; i >= 0; --i) b[i] = b[i + 1] * x + a[i];
    return b[0];
}

db ff(db x) {
    db dx = eps;
    db dy = f(x + dx) - f(x);
    return dy / dx;
}

int main() {
    while (scanf("%d", &n) != EOF) {
        scanf("%lf%lf", &L, &R);
        for (int i = n; i >= 0; --i) scanf("%lf", a + i);
        db l = L, r = R, res = 0;
        while (sgn(r - l) != 0) {
            db mid = (l + r) / 2;
            if (f(mid - eps) > f(mid + eps)) {
                res = mid;
                r = mid;
            } else {
                l = mid;
            }
        }
        printf("%.5f\n", res);
    }
    return 0;
}
