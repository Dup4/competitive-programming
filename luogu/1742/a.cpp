#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
int const MAX = 1e5 + 10;
struct POINT {
    double x, y;
}p[MAX], stk[MAX], base, ansp;
int n, top;
double ans;
 
double getDist(POINT p1, POINT p2) {
    return sqrt(1.0 * (p2.x - p1.x) * (p2.x - p1.x) + 1.0 * (p2.y - p1.y) * (p2.y - p1.y));
}
 
double getCross(POINT p0, POINT p1, POINT p2) {
    return (p1.x - p0.x) * (p2.y - p0.y) - (p2.x - p0.x) * (p1.y - p0.y);
}
 
bool cmp(POINT p1, POINT p2) {
    if (getCross(base, p1, p2) == 0) {
        return getDist(base, p1) < getDist(base, p2);
    }
    if (getCross(base, p1, p2) > 0) {
        return true;
    } 
    return false;
}
 
void getBase() {
    scanf("%lf %lf", &p[0].x, &p[0].y);
    base.x = p[0].x;
    base.y = p[0].y;
    int pos = 0;
    for (int i = 1; i < n; i ++) {
        scanf("%lf %lf", &p[i].x, &p[i].y);
        if (p[i].y < base.y || (p[i].y == base.y && p[i].x < base.x)) {
            base.x = p[i].x;
            base.y = p[i].y;
            pos = i; 
        }
    }
    swap(p[0], p[pos]);
}
 
void getConvex() {
    stk[0] = p[0];
    stk[1] = p[1];
    top = 1;
    for (int i = 2; i < n; i ++) {
        while (top > 0 && getCross(stk[top - 1], stk[top], p[i]) <= 0) {
            top --;
        }
        stk[++ top] = p[i];
    }
}
 
POINT getCircumcenter(POINT a, POINT b, POINT c) {
    POINT res;   
    double a1 = b.x - a.x, b1 = b.y - a.y, c1 = (a1 * a1 + b1 * b1) / 2.0;  
    double a2 = c.x - a.x, b2 = c.y - a.y, c2 = (a2 * a2 + b2 * b2) / 2.0;  
    double d = a1 * b2 - a2 * b1;  
    res.x = a.x + (c1 * b2 - c2 * b1) / d;  
    res.y = a.y + (a1 * c2 - a2 * c1) / d;  
    return res;   
} 
 
bool judge(double a, double b, double c){
    return a * a + b * b < c * c;
}
 
void calR(POINT p0, POINT p1, POINT p2) {
    double p0p1 = getDist(p0, p1);
    double p0p2 = getDist(p0, p2);
    double p1p2 = getDist(p1, p2);
    if (judge(p0p1, p0p2, p1p2) || judge(p0p1, p1p2, p0p2) || judge(p0p2, p1p2, p0p1)) {
        double maxLen = max(p0p1, max(p0p2, p1p2));
        if (maxLen / 2.0 > ans) {
            ans = max(p0p1, max(p0p2, p1p2)) / 2.0;
            if (maxLen == p0p1) {
                ansp.x = (p0.x + p1.x) / 2.0;
                ansp.y = (p0.y + p1.y) / 2.0;
            }
            if (maxLen == p1p2) {
                ansp.x = (p1.x + p2.x) / 2.0;
                ansp.y = (p1.y + p2.y) / 2.0;
            }
            if (maxLen == p0p2) {
                ansp.x = (p0.x + p2.x) / 2.0;
                ansp.y = (p0.y + p2.y) / 2.0;
            }
        }
    }
    else {
        POINT tmpP = getCircumcenter(p0, p1, p2);
        double tmpR = getDist(p2, tmpP);
        if (tmpR > ans) {
            ans = tmpR;
            ansp = tmpP;
        }
    }
}
 
int main() {
    while(scanf("%d", &n) != EOF) {
        getBase();
        if (n == 1) {
            printf("%.2f %.2f 0.00\n", p[0].x, p[0].y);
            continue;
        }
        sort(p + 1, p + n, cmp);
        getConvex();
        if (top == 1) {
            ansp.x = (stk[0].x + stk[1].x) / 2.0;
            ansp.y = (stk[0].y + stk[1].y) / 2.0;
            ans = getDist(stk[0], stk[1]) / 2.0;
            printf("%.10f\n%.10f %.10f\n", ans, ansp.x, ansp.y);
            continue;
        }
        ans = 0;
        for (int i = 0; i <= top; i ++) {
            for (int j = i + 1; j <= top; j ++) {
                for (int k = j + 1; k <= top; k ++) {
                    calR(stk[i], stk[j], stk[k]);
                }
            }
        }
        printf("%.10f\n%.10f %.10f\n", ans, ansp.x, ansp.y);
    }
}
