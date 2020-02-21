#include<bits/stdc++.h>
#define LL long long
#define fi first
#define se second
#define mk make_pair
#define PLL pair<LL, LL>
#define PLI pair<LL, int>
#define PII pair<int, int>
#define SZ(x) ((int)x.size())
#define ull unsigned long long

using namespace std;

const int N = 1e5 + 7;
const int inf = 0x3f3f3f3f;
const LL INF = 0x3f3f3f3f3f3f3f3f;
const int mod = 1e9 + 7;
const double eps = 1e-8;
const double PI = acos(-1);

struct Point {
    double x, y;
    Point(double x = 0, double y = 0) : x(x), y(y) { }

};
typedef Point Vector;
int dcmp(double x) {
    if(fabs(x) < eps) return 0;
    else return x < 0 ? -1 : 1;
}
Point operator + (Vector A, Vector B) {return Point(A.x + B.x, A.y + B.y);}
Point operator - (Vector A, Vector B) {return Point(A.x - B.x, A.y - B.y);}
Point operator * (Vector A, double p) {return Point(A.x * p, A.y * p);}
Point operator / (Vector A, double p) {return Point(A.x / p, A.y / p);}
bool operator < (const Vector &A, const Vector &B) {return A.y < B.y || (A.y == B.y && A.x < B.x);}
bool operator == (const Vector &A, const Point &B) {return dcmp(A.x - B.x) == 0 && dcmp(A.y - B.y) == 0;}
double Dot(Vector A, Vector B) {return A.x * B.x + A.y * B.y;}
double Length(Vector A) {return sqrt(Dot(A, A));}
double Angle(Vector A, Vector B) {return acos(Dot(A, B) / Length(A) / Length(B));}
double Cross(Vector A, Vector B) {return A.x * B.y - A.y * B.x;}
double Area2(Point A, Point B, Point C) {return Cross(B - A, C - A);}


double PolygonArea(vector<Point>& p) {
    int n = p.size();
    double area = 0;
    for(int i = 1; i < n - 1; i++)
        area += Cross(p[i]-p[0], p[i+1]-p[0]);
    return fabs(area / 2);
}

double Seg(Point O, Point A, Point B){
    if(dcmp(B.x - A.x) == 0) return (O.y - A.y) / (B.y - A.y);
    return (O.x - A.x) / (B.x - A.x);
}

double MultiPolyArea(vector<Point>* p, int n) {
    double res=0;
    vector<pair<double, int>> s;
    for(int i = 0; i < n; i++) {
        int sz = p[i].size();
        for(int j = 0; j < sz; j++){
            s.clear();
            s.push_back(mk(0, 0));
            s.push_back(mk(1, 0));
            Point a = p[i][j], b = p[i][(j+1)%sz];
            for(int k = 0; k < n; k++){
                if(i != k){
                    int sz2 = p[k].size();
                    for(int z = 0; z < sz2; z++){
                        Point c = p[k][z], d = p[k][(z+1)%sz2];
                        int c1 = dcmp(Cross(b-a, c-a));
                        int c2 = dcmp(Cross(b-a, d-a));
                        if(c1 == 0 && c2 == 0) {
                            if(dcmp(Cross(b-a, d-c))) {
                                s.push_back(mk(Seg(c, a, b), 1));
                                s.push_back(mk(Seg(c, a, b), -1));
                            }
                        } else {
                            double s1 = Cross(d-c, a-c), s2 = Cross(d-c, b-c);
                            if(c1 >= 0 && c2 < 0) s.push_back(mk(s1/(s1-s2), 1));
                            else if(c1 < 0 && c2 >= 0) s.push_back(mk(s1/(s1-s2), -1));
                        }
                    }
                }
            }
            sort(s.begin(), s.end());
            double pre = min(max(s[0].fi, 0.0), 1.0), now, sum=0;
            int cov = s[0].se;
            for(int j = 1; j < s.size(); j++) {
                now = min(max(s[j].fi, 0.0), 1.0);
                if(!cov) sum += now - pre;
                cov += s[j].second;
                pre = now;
            }
            res += Cross(a, b) * sum;
        }
    }
    return fabs(res / 2);
}

int n, m;
vector<Point> poly[110];

int main() {
    scanf("%d", &n);
    for(int i = 0; i < n; i++) {
        poly[i].resize(3);
        for(int j = 0; j < 3; j++) {
            scanf("%lf%lf", &poly[i][j].x, &poly[i][j].y);
        }
    }
    double ans2 = MultiPolyArea(poly, n);
    printf("%.2f\n", ans2 - eps);
    return 0;
}
