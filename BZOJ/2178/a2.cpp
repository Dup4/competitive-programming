#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
typedef double db;
typedef pair<db, db> pDD;
const db eps = 1e-8;
const int N = 1e3 + 10, INF = 0x3f3f3f3f;
int n;
inline db sqr(db x) {
    return x * x;
}
inline int sgn(db x) {
    return fabs(x) < eps ? 0 : x < 0 ? -1 : 1;
}

struct Circle {
    db x, y, r;
    bool operator<(const Circle &b) const {
        return r > b.r;
    }
    db dis(Circle b) {
        return hypot(x - b.x, y - b.y);
    }
} cir[N];

db f(db x) {
    static pDD sta[N];
    int top = 0;
    for (int i = 1; i <= n; ++i)
        if (sgn(fabs(cir[i].x - x) - cir[i].r) < 0) {
            db len = sqrt(sqr(cir[i].r) - sqr(cir[i].x - x));
            sta[++top] = pDD(cir[i].y - len, cir[i].y + len);
        }
    sort(sta + 1, sta + 1 + top);
    int tmp = 1;
    for (int i = 2; i <= top; ++i) {
        if (sgn(sta[i].fi - sta[tmp].se) <= 0)
            sta[tmp].se = max(sta[tmp].se, sta[i].se);
        else
            sta[++tmp] = sta[i];
    }
    top = tmp;
    db res = 0;
    for (int i = 1; i <= tmp; ++i) res += sta[i].se - sta[i].fi;
    return res;
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

//去除内含圆
void Unique() {
    int cnt = 0;
    sort(cir + 1, cir + 1 + n);
    for (int i = 1; i <= n; i++) {
        int ok = 1;
        for (int j = 1; j <= cnt; j++)
            if (cir[i].r + cir[i].dis(cir[j]) <= cir[j].r) {
                ok = 0;
                break;
            }
        if (ok)
            cir[++cnt] = cir[i];
    }
    n = cnt;
}

int main() {
    while (scanf("%d", &n) != EOF) {
        db l = INF, r = -INF, mid;
        for (int i = 1; i <= n; ++i) {
            scanf("%lf%lf%lf", &cir[i].x, &cir[i].y, &cir[i].r);
            l = min(l, cir[i].x - cir[i].r);
            r = max(r, cir[i].x + cir[i].r);
        }
        Unique();
        mid = l + (r - l) / 2;
        printf("%.3f\n", Simpson(l, mid, r, f(l), f(mid), f(r), 0));
        return 0;
    }
}
