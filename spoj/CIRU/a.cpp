#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
typedef double db;
typedef pair<db, db> pDD;
const db eps = 1e-8;
const int N = 1e3 + 10, INF = 0x3f3f3f3f;
int n;
db sqr(db x) {
    return x * x;
}
int sgn(db x) {
    return fabs(x) < eps ? 0 : x < 0 ? -1 : 1;
}

struct Circle {
    db x, y, r;
    void scan() {
        scanf("%lf%lf%lf", &x, &y, &r);
    }
    bool operator<(const Circle& b) const {
        return r > b.r;
    }
    db disCircletoCircle(Circle b) {
        return hypot(x - b.x, y - b.y);
    }
};

struct CircleUnion {
    vector<Circle> cir;
    vector<pair<db, db> > sta;
    int sze() {
        return cir.size();
    }
    CircleUnion(int n = 0) {
        cir.clear();
        cir.resize(n);
    }
    void scan(int n = -1) {
        if (n == -1)
            scanf("%d", &n);
        (*this) = CircleUnion(n);
        for (int i = 0; i < n; ++i) cir[i].scan();
    }
    void add(Circle c) {
        cir.push_back(c);
    }
    Circle& operator[](int x) {
        return cir[x];
    }
    //扫描线部分
    db f(db x) {
        int top = 0;
        for (int i = 0; i < sze(); ++i)
            if (fabs(cir[i].x - x) < cir[i].r) {
                db len = sqrt(sqr(cir[i].r) - sqr(cir[i].x - x));
                sta[++top] = pDD(cir[i].y - len, cir[i].y + len);
            }
        if (!top)
            return 0;
        sort(sta.begin() + 1, sta.begin() + top + 1);
        int tmp = 1;
        for (int i = 2; i <= top; ++i) {
            if (sta[i].fi < sta[tmp].se)
                sta[tmp].se = max(sta[tmp].se, sta[i].se);
            else
                sta[++tmp] = sta[i];
        }
        top = min(top, tmp);
        db res = 0;
        for (int i = 1; i <= top; ++i) res += sta[i].se - sta[i].fi;
        return res;
    }
    //辛普森积分
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
        sort(cir.begin(), cir.end());
        for (int i = 0; i < sze(); i++) {
            int ok = 1;
            for (int j = 0; j < cnt; j++)
                if (cir[i].r + cir[i].disCircletoCircle(cir[j]) <= cir[j].r) {
                    ok = 0;
                    break;
                }
            if (ok)
                cir[cnt++] = cir[i];
        }
        cir.resize(cnt);
    }
    //获得圆并面积
    db gao() {
        if (sze() == 0)
            return 0;
        Unique();
        sta.clear();
        sta.resize(sze() + 5);
        db l = cir[0].x - cir[0].r;
        db r = cir[0].x + cir[0].r;
        for (int i = 1; i < sze(); ++i) {
            l = min(l, cir[i].x - cir[i].r);
            r = max(r, cir[i].x + cir[i].r);
        }
        db mid = l + (r - l) / 2;
        return Simpson(l, mid, r, f(l), f(mid), f(r), 0);
    }
};

int main() {
    while (scanf("%d", &n) != EOF) {
        CircleUnion cu;
        cu.scan(n);
        printf("%.3f\n", cu.gao());
        return 0;
    }
}
