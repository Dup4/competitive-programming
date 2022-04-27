#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;
typedef double db;
const db eps = 1e-10;
const db PI = acos(-1.0);
int sgn(db x) {
    if (fabs(x) < eps)
        return 0;
    return x < 0 ? -1 : 1;
}
db fixOut(db x) {
    if (sgn(x) == 0)
        return 0;
    return x;
}
db toRad(db angle) {
    return angle / 180 * PI;
}

struct Point3 {
    db x, y, z;
    Point3(db x = 0, db y = 0, db z = 0) : x(x), y(y), z(z) {}
    void scan() {
        scanf("%lf%lf%lf", &x, &y, &z);
    }
    void print() {
        printf("%.5f %.5f %.5f\n", x, y, z);
    }
    bool operator==(const Point3 &b) const {
        return sgn(x - b.x) == 0 && sgn(y - b.y) == 0 && sgn(z - b.z) == 0;
    }
    bool operator<(const Point3 &b) const {
        return sgn(x - b.x) == 0 ? (sgn(y - b.y == 0) ? sgn(z - b.z) < 0 : y < b.y) : x < b.x;
    }
    Point3 operator+(const Point3 &b) const {
        return Point3(x + b.x, y + b.y, z + b.z);
    }
    Point3 operator-(const Point3 &b) const {
        return Point3(x - b.x, y - b.y, z - b.z);
    }
    Point3 operator*(const db &k) const {
        return Point3(x * k, y * k, z * k);
    }
    Point3 operator/(const db &k) const {
        return Point3(x / k, y / k, z / k);
    }
    db operator*(const Point3 &b) const {
        return x * b.x + y * b.y + z * b.z;
    }
    Point3 operator^(const Point3 &b) const {
        return Point3(y * b.z - z * b.y, z * b.x - x * b.z, x * b.y - y * b.x);
    }
    db len() {
        return sqrt(x * x + y * y + z * z);
    }
    db len2() {
        return x * x + y * y + z * z;
    }
    db dis(Point3 b) {
        return sqrt((x - b.x) * (x - b.x) + (y - b.y) * (y - b.y) + (z - b.z) * (z - b.z));
    }
    db dis2(Point3 b) {
        return (x - b.x) * (x - b.x) + (y - b.y) * (y - b.y) + (z - b.z) * (z - b.z);
    }
    db rad(Point3 a, Point3 b) {
        Point3 p = (*this);
        return acos(((a - p) * (b - p)) / (a.dis(p) * b.dis(p)));
    }
    //变换长度
    Point3 trunc(db r) {
        db l = len();
        if (!sgn(l))
            return *this;
        r /= l;
        return (*this) * r;
    }
};

struct Line3 {
    Point3 s, e;
    Line3() {}
    Line3(Point3 s, Point3 e) : s(s), e(e) {}
    void scan() {
        s.scan();
        e.scan();
    }
    void print() {
        s.print();
        e.print();
    }
    bool operator==(const Line3 &b) {
        return s == b.s && e == b.e;
    }
    db len() {
        return s.dis(e);
    }
    //点到直线距离
    db disPointToLine(Point3 b) {
        return ((e - s) ^ (b - s)).len() / s.dis(e);
    }
    //点到线段距离
    db disPointToSeg(Point3 b) {
        if (sgn((b - s) * (e - s)) < 0 || sgn((b - e) * (s - e)) < 0)
            return min(s.dis(b), e.dis(b));
        return disPointToLine(b);
    }
    //点b 在直线上的投影
    Point3 lineProg(Point3 b) {
        return s + (((e - s) * ((e - s) * (b - s))) / ((e - s).len2()));
    }
    //点b 绕此向量逆时针rad角度
    Point3 rotate(Point3 b, db rad) {
        if (sgn(((s - b) ^ (e - b)).len()) == 0)
            return b;
        Point3 f1 = (e - s) ^ (b - s);
        Point3 f2 = (e - s) ^ f1;
        db len = ((s - b) ^ (e - b)).len() / s.dis(e);
        f1 = f1.trunc(len);
        f2 = f2.trunc(len);
        Point3 h = b + f2;
        Point3 pp = h + f1;
        return h + ((b - h) * cos(rad)) + ((pp - h) * sin(rad));
    }
    bool pointOnSeg(Point3 b) {
        return sgn(((s - b) ^ (e - b)).len()) == 0 && sgn((s - b) * (e - b)) == 0;
    }
};

struct Plane {
    Point3 a, b, c, o;
    Plane() {}
    Plane(Point3 a, Point3 b, Point3 c, Point3 o) : a(a), b(b), c(c), o(o) {}
    void scan() {
        a.scan();
        b.scan();
        c.scan();
        o.scan();
    }
    // ax + by + cz + d = 0
    Plane(db _a, db _b, db _c, db _d) {
        o = Point3(_a, _b, _c);
        if (sgn(_a) != 0)
            a = Point3((-_d - _c - _d) / _a, 1, 1);
        else if (sgn(_b) != 0)
            a = Point3(1, (-_d - _c - _a) / _b, 1);
        else if (sgn(_c) != 0)
            a = Point3(1, 1, (-_d - _a - _b) / _c);
    }
    Point3 pvec() {
        return (b - a) ^ (c - a);
    }
    //点是否在平面上
    bool pointOnPlane(Point3 b) {
        return sgn((b - a) * o) == 0;
    }
    //两平面夹角
    db radPlane(Plane f) {
        return acos(o * f.o) / (o.len() * f.o.len());
    }
    //平面和直线的交点，返回值是交点个数
    int crossLine(Line3 u, Point3 &p) {
        db x = o * (u.e - a);
        db y = o * (u.s - a);
        db d = x - y;
        if (sgn(d) == 0)
            return 0;
        p = ((u.s * x) - (u.e * y)) / d;
        return 1;
    }
    //点到平面最近点(投影)
    Point3 pointToPlane(Point3 b) {
        Line3 u = Line3(b, b + o);
        crossLine(u, b);
        return b;
    }
    //平面和平面的交线
    int crossPlane(Plane f, Line3 &u) {
        Point3 oo = o ^ f.o;
        Point3 v = o ^ oo;
        db d = fabs(f.o * v);
        if (sgn(d) == 0)
            return 0;
        Point3 q = a + (v * (f.o * (f.a - a)) / d);
        u = Line3(q, q + oo);
        return 1;
    }
};

struct CH3D {
    struct face {
        //表示凸包一个面上的三个点的编号
        int a, b, c;
        //表示该面是否属于最终的凸包上的面
        bool ok;
    };
    vector<Point3> P;
    //凸包表面的三角形
    vector<face> F;
    //凸包表面的三角形数
    int num;
    vector<vector<int> > g;
    CH3D(int n = 0) {
        P.clear();
        P.resize(n);
    }
    void scan(int n = -1) {
        if (n == -1)
            scanf("%d", &n);
        (*this) = CH3D(n);
        for (int i = 0; i < n; ++i) P[i].scan();
    }
    int sze() {
        return P.size();
    }
    Point3 &operator[](int x) {
        return P[(x + sze()) % sze()];
    }
    void add(Point3 q) {
        P.push_back(q);
    }
    //三角形面积 * 2
    db areaTriangle(Point3 a, Point3 b, Point3 c) {
        return ((b - a) ^ (c - a)).len();
    }
    //四面体有向面积 * 6
    db volume(Point3 a, Point3 b, Point3 c, Point3 d) {
        return ((b - a) ^ (c - a)) * (d - a);
    }
    //正: 点在面同向
    db dblcmp(Point3 &p, face &f) {
        Point3 p1 = P[f.b] - P[f.a];
        Point3 p2 = P[f.c] - P[f.a];
        Point3 p3 = p - P[f.a];
        return (p1 ^ p2) * p3;
    }
    void deal(int p, int a, int b) {
        int f = g[a][b];
        face add;
        if (F[f].ok) {
            if (dblcmp(P[p], F[f]) > eps)
                dfs(p, f);
            else {
                add.a = b;
                add.b = a;
                add.c = p;
                add.ok = true;
                g[p][b] = g[a][p] = g[b][a] = num;
                F.push_back(add);
                ++num;
            }
        }
    }
    //递归搜索所有应该从凸包内删除的面
    void dfs(int p, int now) {
        F[now].ok = false;
        deal(p, F[now].b, F[now].a);
        deal(p, F[now].c, F[now].b);
        deal(p, F[now].a, F[now].c);
    }
    bool same(int s, int t) {
        Point3 &a = P[F[s].a];
        Point3 &b = P[F[s].b];
        Point3 &c = P[F[s].c];
        return fabs(volume(a, b, c, P[F[t].a])) < eps && fabs(volume(a, b, c, P[F[t].b])) < eps &&
               fabs(volume(a, b, c, P[F[t].c])) < eps;
    }
    //构建三维凸包
    void create() {
        F.clear();
        num = 0;
        g.clear();
        g.resize(sze() + 1, vector<int>(sze() + 1, 0));
        face add;
        //保证前4个点不共面
        sort(P.begin(), P.end());
        P.erase(unique(P.begin(), P.end()), P.end());
        random_shuffle(P.begin(), P.end());
        for (int i = 0; i < 4; ++i) {
            add.a = (i + 1) % 4;
            add.b = (i + 2) % 4;
            add.c = (i + 3) % 4;
            add.ok = true;
            if (dblcmp(P[i], add) > 0)
                swap(add.b, add.c);
            g[add.a][add.b] = g[add.b][add.c] = g[add.c][add.a] = num;
            F.push_back(add);
            ++num;
        }
        for (int i = 4; i < sze(); ++i) {
            for (int j = 0; j < num; ++j) {
                if (F[j].ok && dblcmp(P[i], F[j]) > eps) {
                    dfs(i, j);
                    break;
                }
            }
        }
        int tmp = num;
        num = 0;
        for (int i = 0; i < tmp; ++i) {
            if (F[i].ok) {
                F[num++] = F[i];
            }
        }
        F.resize(num);
    }
    //表面积
    // POJ3528 BZOJ 1209
    db getArea() {
        db res = 0;
        if (sze() == 3) {
            Point3 p = (P[1] - P[0]) ^ (P[2] - P[0]);
            return p.len() / 2;
        }
        for (int i = 0; i < num; ++i) res += areaTriangle(P[F[i].a], P[F[i].b], P[F[i].c]);
        return res / 2.0;
    }
    //体积
    db getVolume() {
        db res = 0;
        Point3 tmp = Point3(0, 0, 0);
        for (int i = 0; i < num; ++i) res += volume(tmp, P[F[i].a], P[F[i].b], P[F[i].c]);
        return fabs(res / 6.0);
    }
    //表面三角形个数
    int triangleNum() {
        return num;
    }
    //表面多边形个数
    // HDU 3662
    int polygonNum() {
        int res = 0;
        for (int i = 0; i < num; ++i) {
            int ok = 1;
            for (int j = 0; j < i; ++j) {
                if (same(i, j)) {
                    ok = 0;
                    break;
                }
            }
            res += ok;
        }
        return res;
    }
    //重心
    // HDU4273
    Point3 getBarycenter() {
        Point3 ans = Point3(0, 0, 0);
        Point3 o = Point3(0, 0, 0);
        db all = 0;
        for (int i = 0; i < num; ++i) {
            db vol = volume(o, P[F[i].a], P[F[i].b], P[F[i].c]);
            ans = ans + (((o + P[F[i].a] + P[F[i].b] + P[F[i].c]) / 4.0) * vol);
            all += vol;
        }
        ans = ans / all;
        return ans;
    }
    //点到面的距离
    // HDU4273 HDU 4266
    db disPointToFace(Point3 p, int i) {
        db tmp1 = fabs(volume(P[F[i].a], P[F[i].b], P[F[i].c], p));
        db tmp2 = ((P[F[i].b] - P[F[i].a]) ^ (P[F[i].c] - P[F[i].a])).len();
        return tmp1 / tmp2;
    }
};

int main() {
    int n;
    while (scanf("%d", &n) != EOF) {
        CH3D hull;
        hull.scan(n);
        hull.create();
        printf("%d\n", hull.polygonNum());
    }
    return 0;
}
