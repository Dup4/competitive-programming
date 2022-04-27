#include <bits/stdc++.h>
using namespace std;
typedef double db;
typedef long long ll;
const db eps = 1e-10;
const db PI = acos(-1.0);
int sgn(db x) {
    if (fabs(x) < eps)
        return 0;
    return x < 0 ? -1 : 1;
}
int n;

struct Point {
    db x, y;
    Point(db x = 0, db y = 0) : x(x), y(y) {}
    void scan() {
        db _x, _y;
        scanf("%lf%lf", &_x, &_y);
        x = _x, y = _y;
    }
};

vector<Point> po;

ll C(int n, int m) {
    if (n < m)
        return 0;
    ll res = 1;
    for (int i = n; i > n - m; --i) res = res * i;
    for (int i = 1; i <= m; ++i) res /= i;
    return res;
}

inline db calc(Point a, Point b) {
    return atan2(b.y - a.y, b.x - a.x);
}

ll gao() {
    ll res = 0;
    for (int i = 0; i < n; ++i) {
        vector<db> vec;
        for (int j = 0; j < n; ++j)
            if (i != j) {
                vec.push_back(calc(po[i], po[j]));
                if (vec.end()[-1] < -eps)
                    vec.end()[-1] += PI * 2;
            }
        sort(vec.begin(), vec.end());
        for (int j = 0; j < n - 1; ++j) vec.push_back(vec[j] + PI * 2);
        ll now = C(n - 1, 3);
        int r = 1;
        for (int l = 0; l < n - 1; ++l) {
            while (fabs(vec[r] - vec[l]) - PI < -eps) ++r;
            now -= C(r - l - 1, 2);
        }
        res -= now;
    }
    return res;
}

int main() {
    int _T;
    scanf("%d", &_T);
    while (_T--) {
        scanf("%d", &n);
        po.resize(n);
        for (int i = 0; i < n; ++i) po[i].scan();
        ll res = C(n, 4) + gao();
        printf("%lld\n", res);
    }
    return 0;
}
