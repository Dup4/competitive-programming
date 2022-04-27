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
    db F(db x) {
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
            if (sgn(sta[i].fi - sta[tmp].se) <= 0)
                sta[tmp].se = max(sta[tmp].se, sta[i].se);
            else
                sta[++tmp] = sta[i];
        }
        top = min(top, tmp);
        db res = 0;
        for (int i = 1; i <= top; ++i) res += sta[i].se - sta[i].fi;
        return res;
    }
    //区间[a,b]上的辛普森值，已知区间长度l和端点及中点处的函数值A，B，C
    db S(db L, db R, db FL, db FM, db FR) {
        return (R - L) * (FL + 4 * FM + FR) / 6.0;
    }
    //辛普森积分
    db Simpson(db L, db R, db FL, db FM, db FR, db eps) {
        db mid = (L + R) / 2, nans = S(L, R, FL, FM, FR);
        db FLM = F((L + mid) / 2), FRM = F((mid + R) / 2);
        if (R - L <= 1) {
            if (abs(S(L, mid, FL, FLM, FM) + S(mid, R, FM, FRM, FR) - nans) <= 15 * eps)
                return nans;
        }
        nans = Simpson(L, mid, FL, FLM, FM, eps / 2) + Simpson(mid, R, FM, FRM, FR, eps / 2);
        return nans;
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
        return Simpson(l, r, F(l), F((l + r) / 2), F(r), 1e-5);
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
