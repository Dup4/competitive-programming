#include <bits/stdc++.h>
using namespace std;

#define N 2530
double eps = 1e-8;
int n, m;
int vis[N];
int sgn(int x) {
    if (x == 0) {
        return 0;
    } else if (x < 0) {
        return -1;
    } else {
        return 1;
    }
}
struct Point {
    int x, y;
    Point() {}
    Point(int x, int y) {
        this->x = x;
        this->y = y;
    }
    void scan() {
        scanf("%d%d", &x, &y);
    }
    Point operator-(const Point &b) const {
        return Point(x - b.x, y - b.y);
    }
    double operator^(const Point &b) const {
        return x * b.y - y * b.x;
    }
} P[N];

struct Line {
    Point s, e;
    Line() {}
    Line(Point s, Point e) : s(s), e(e) {}
    bool parallel(Line v) {
        return sgn((e - s) ^ (v.e - v.s)) == 0;
    }
    int relation(Point p) {
        int c = sgn((p - s) ^ (e - s));
        if (c < 0) {
            return 1;
        } else if (c > 0) {
            return 2;
        } else {
            return 3;
        }
    }
    int linecrossline(Line v) {
        if ((*this).parallel(v)) {
            return v.relation(s) == 3;
        }
        return 2;
    }
} a[N], b[N];

int main() {
    while (scanf("%d", &n) != EOF) {
        m = 0;
        memset(vis, 0, sizeof vis);
        for (int i = 1; i <= n; ++i) {
            P[i].scan();
        }
        for (int i = 1; i <= n; ++i) {
            for (int j = i + 1; j <= n; ++j) {
                a[++m] = Line(P[i], P[j]);
            }
        }
        for (int i = 1; i <= m; ++i)
            if (vis[i] == 0) {
                for (int j = i + 1; j <= m; ++j)
                    if (vis[j] == 0) {
                        if (a[i].linecrossline(a[j]) == 1) {
                            vis[j] = 1;
                        }
                    }
            }
        int tmp = m;
        m = 0;
        for (int i = 1; i <= tmp; ++i)
            if (vis[i] == 0) {
                b[++m] = a[i];
            }
        int res = 0;
        for (int i = 1; i <= m; ++i) {
            for (int j = i + 1; j <= m; ++j) {
                if (b[i].linecrossline(b[j]) > 0) {
                    ++res;
                }
            }
        }
        printf("%d\n", res);
    }
    return 0;
}
