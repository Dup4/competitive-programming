#include <bits/stdc++.h>
using namespace std;
typedef double db;
const db eps = 1e-10;
const db PI = acos(-1.0L);
int sgn(db x) {
    if (fabs(x) < eps)
        return 0;
    return x < 0 ? -1 : 1;
}
const int N = 4e3 + 10;

struct Point {
    db x, y;
    Point(db x = 0, db y = 0) : x(x), y(y) {}
    void scan() {
        db _x, _y;
        scanf("%lf%lf", &_x, &_y);
        x = _x, y = _y;
    }
    void print() {
        printf("%.11f %.11f\n", x, y);
    }
    bool operator==(const Point &b) const {
        return sgn(x - b.x) == 0 && sgn(y - b.y) == 0;
    }
    bool operator<(const Point &b) const {
        return sgn(x - b.x) == 0 ? sgn(y - b.y) < 0 : x < b.x;
    }
    Point operator+(const Point &b) const {
        return Point(x + b.x, y + b.y);
    }
    Point operator-(const Point &b) const {
        return Point(x - b.x, y - b.y);
    }
    Point operator*(const db &b) const {
        return Point(x * b, y * b);
    }
    Point operator/(const db &b) const {
        return Point(x / b, y / b);
    }
    db operator^(const Point &b) const {
        return x * b.y - y * b.x;
    }
    db operator*(const Point &b) const {
        return x * b.x + y * b.y;
    }
    db len() {
        return hypot(x, y);
    }
    db len2() {
        return x * x + y * y;
    }
    db dis(Point b) {
        return hypot(x - b.x, y - b.y);
    }
    db dis2(Point b) {
        return (x - b.x) * (x - b.x) + (y - b.y) * (y - b.y);
    }
    int quad() {
        int _x = sgn(x), _y = sgn(y);
        if (_x > 0 && _y >= 0)
            return 1;
        if (_x <= 0 && _y > 0)
            return 2;
        if (_x < 0 && _y <= 0)
            return 3;
        if (_x >= 0 && _y < 0)
            return 4;
    }
    //求PA和PB构成的夹角 lightOJ 1203
    db getRad(Point a, Point b) {
        Point p = *this;
        return fabs(atan2(fabs((a - p) ^ (b - p)), (a - p) * (b - p)));
    }
    //单位法向量
    Point normal() {
        return Point(-y, x) / len();
    }
    //化为长度为r的向量
    Point trunc(db r) {
        db l = len();
        if (!sgn(l))
            return *this;
        r /= l;
        return Point(x * r, y * r);
    }
    //逆时针旋转90度
    Point rotleft() {
        return Point(-y, x);
    }
    //顺时针旋转90度
    Point rotright() {
        return Point(y, -x);
    }
    //绕点p旋转rad弧度
    Point rotate(Point p, db rad) {
        Point v = (*this) - p;
        db c = cos(rad), s = sin(rad);
        return Point(p.x + v.x * c - v.y * s, p.y + v.x * s + v.y * c);
    }
} p[N], q[N << 1];

ll gao() {
    for (int i = 1; i <= n; ++i) {
        int tot = 0;
        for (int j = 1; j <= n; ++j)
            if (i != j) {
                q[++tot] = p[j] - p[i];
            }
        int tmp = 0;
        sort(q + 1, q + 1 + tot);
        for (int j = 1; j <= tot; ++j) q[tot + j] = q[j];
        for (int j = 1; j < tot; ++j) {
        }
    }
}

int main() {
    while (scanf("%d", &n) != EOF) {
        for (int i = 1; i <= n; ++i) p[i].scan();
        ll line = 0;
        ll res = 1ll * n * (n - 1) * (n - 2) / 6;
        res -= gao();
        printf("%lld\n", res);
    }
    return 0;
}
