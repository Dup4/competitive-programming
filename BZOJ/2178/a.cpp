#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
typedef double db;
typedef pair<db, db> pDD;
#define dbg(x...)                             \
    do {                                      \
        cout << "\033[32;1m" << #x << " -> "; \
        err(x);                               \
    } while (0)
void err() {
    cout << "\033[39;0m" << endl;
}
template <class T, class... Ts>
void err(const T& arg, const Ts&... args) {
    cout << arg << ' ';
    err(args...);
}
const db eps = 1e-6;
const int N = 1e3 + 10, INF = 0x3f3f3f3f;
int n;
struct Circle {
    db x, y, r;
} cir[N];
inline db sqr(db x) {
    return x * x;
}
inline int sgn(db x) {
    return fabs(x) < eps ? 0 : x < 0 ? -1 : 1;
}

pDD sta[N];
db F(db x) {
    int top = 0;
    for (int i = 1; i <= n; ++i)
        if (fabs(cir[i].x - x) < cir[i].r) {
            db len = sqrt(sqr(cir[i].r) - sqr(cir[i].x - x));
            sta[++top] = pDD(cir[i].y - len, cir[i].y + len);
        }
    if (!top)
        return 0;
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

//区间[a,b]上的辛普森值，已知区间长度l和端点及中点处的函数值A，B，C
db S(db L, db R, db FL, db FM, db FR) {
    return (R - L) * (FL + 4 * FM + FR) / 6.0;
}

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

int main() {
    while (scanf("%d", &n) != EOF) {
        db l = INF, r = -INF;
        for (int i = 1; i <= n; ++i) {
            scanf("%lf%lf%lf", &cir[i].x, &cir[i].y, &cir[i].r);
            l = min(l, cir[i].x - cir[i].r);
            r = max(r, cir[i].x + cir[i].r);
        }
        printf("%.3f\n", Simpson(l, r, F(l), F((l + r) / 2), F(r), 1e-5));
    }
    return 0;
}
