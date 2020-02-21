#include <iostream>
#include <cstdio>
#include <cmath>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;
typedef double db;
const int N = 110;
const db eps = 1e-8;
int sgn(db x) { if (fabs(x) < eps) return 0; return x < 0 ? -1 : 1; }

struct Point {
	db x, y;
	Point(db x = 0, db y = 0) : x(x), y(y) {}
	void scan() { db _x, _y; scanf("%lf%lf", &_x, &_y); x = _x, y = _y; }
	void print() { printf("%.11f %.11f\n", x, y); }
	bool operator == (const Point &b) const { return sgn(x - b.x) == 0 && sgn(y - b.y) == 0; }
	bool operator < (const Point &b) const { return sgn(x - b.x) == 0 ? sgn(y - b.y) < 0 : x < b.x; }
	Point operator + (const Point &b) const { return Point(x + b.x, y + b.y); }
	Point operator - (const Point &b) const { return Point(x - b.x, y - b.y); }
	Point operator * (const db &b) const { return Point(x * b, y * b); }
	Point operator / (const db &b) const { return Point(x / b, y / b); }
	db operator ^ (const Point &b) const { return x * b.y - y * b.x; }
	db operator * (const Point &b) const { return x * b.x + y * b.y; }
	db len() { return hypot(x, y); }
	db len2() { return x * x + y * y; }
	db dis(Point b) { return hypot(x - b.x, y - b.y); }
}s[N], p[N];

bool cmp(Point a, Point b) {
	if (sgn(a ^ b) != 0) return sgn(a ^ b) > 0;
   	return a.len2() < b.len2();	
}

int n, dp[N][N];

int gao(int m) {
    int res = 0;
    memset(dp, 0, sizeof dp);
    for (int i = 2; i <= m; ++i) {
        int now = i - 1;
        while (now >= 1 && sgn(p[i] ^ p[now]) == 0) --now;
		int ok = false;
        if (now == i - 1) ok = true;
        while (now >= 1) {
            int S = p[now] ^ p[i];
            int k = now - 1;
            while (k >= 1 && sgn((p[now] - p[i]) ^ (p[k] - p[now])) > 0) --k;
            if (k >= 1) S += dp[now][k];
            if (ok) dp[i][now] = S;
            res = max(res, S);
            now = k;
        }
        if (!ok) continue;
        for (int j = 1; j <= i - 1; ++j) {
            dp[i][j] = max(dp[i][j], dp[i][j - 1]);
        }
    }
    return res;
}

int main() {
    int _T;
    scanf("%d", &_T);
    while (_T--) {
        scanf("%d", &n);
        for (int i = 1; i <= n; ++i) s[i].scan();
        int res = 0;
        for (int i = 1; i <= n; i++) {
            int m = 0;
            for (int j = 1; j <= n; j++) {
            	if (s[j].y > s[i].y || (s[j].y == s[i].y && s[j].x >= s[i].x))
                    p[++m] = s[j] - s[i];
            }
            sort(p + 1, p + m + 1, cmp);
            res = max(res, gao(m));
        }
        printf("%.1f\n", res / 2.0);
    }
    return 0;
}
