\section{计算几何}

\subsection{最小圆覆盖}
\begin{lstlisting}
// hdu 3007 
//先求凸包，然后枚举凸包上的三点求包含这个三角形的最小圆，注意特判n为1和2的情况
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
int const MAX = 505;
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
    while(scanf("%d", &n) && n) {
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
            printf("%.2f %.2f %.2f\n", ansp.x, ansp.y, ans);
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
        printf("%.2f %.2f %.2f\n", ansp.x, ansp.y, ans);
    }
}
\end{lstlisting}
\subsection{最小球覆盖}
Gym 101981D
\begin{lstlisting}
#include<bits/stdc++.h>
using namespace std;

#define db double
#define N 200010
const db eps = 1e-12;
struct Tpoint{
	db x,y,z;
	Tpoint() {}
	void scan() {
		scanf("%lf%lf%lf", &x, &y, &z);
	}
}pt[N], outer[4], res;
int npoint,nouter;
db radius;
inline db dist(Tpoint p1,Tpoint p2) {
	double dx = p1.x-p2.x,dy = p1.y-p2.y,dz = p1.z-p2.z;
	return (dx*dx+dy*dy+dz*dz);
}
inline db dot(Tpoint p1,Tpoint p2) {
	return p1.x*p2.x+p1.y*p2.y+p1.z*p2.z;
}
void ball()
{
	Tpoint q[3];
	db m[3][3],sol[3],L[3],det;
	res.x = res.y = res.z = radius = 0.;
	switch(nouter) {
		case 1:res = outer[0];break;
		case 2:
			res.x = (outer[0].x+outer[1].x)/2;
			res.y = (outer[0].y+outer[1].y)/2;
			res.z = (outer[0].z+outer[1].z)/2;
			radius = dist(res,outer[0]);
			break;
		case 3:
			for(int i = 0; i < 2; i++) {
				q[i].x = outer[i+1].x-outer[0].x;
				q[i].y = outer[i+1].y-outer[0].y;
				q[i].z = outer[i+1].z-outer[0].z;
			}
			for(int i = 0; i < 2; i++) {
				for(int j = 0;j < 2;j++) {
					m[i][j] = dot(q[i],q[j])*2;
				}
			}
			for(int i = 0; i < 2; i++) sol[i] = dot(q[i],q[i]);
			if(fabs(det = m[0][0]*m[1][1]-m[0][1]*m[1][0])<eps)
				return ;
			L[0] = (sol[0]*m[1][1]-sol[1]*m[0][1])/det;
			L[1] = (sol[1]*m[0][0]-sol[0]*m[1][0])/det;
			res.x = outer[0].x+q[0].x*L[0]+q[1].x*L[1];
			res.y = outer[0].y+q[0].y*L[0]+q[1].y*L[1];
			res.z = outer[0].z+q[0].z*L[0]+q[1].z*L[1];
			radius = dist(res,outer[0]);
			break;
		case 4:
			for(int i = 0; i < 3; i++) {
				q[i].x = outer[i+1].x-outer[0].x;
				q[i].y = outer[i+1].y-outer[0].y;
				q[i].z = outer[i+1].z-outer[0].z;
				sol[i] = dot(q[i],q[i]);
			}
			for(int i = 0; i < 3; i++) {
				for(int j = 0; j < 3; j++) { 
					m[i][j] = dot(q[i],q[j])*2;
				}
			}
			det = m[0][0]*m[1][1]*m[2][2]
			+m[0][1]*m[1][2]*m[2][0]
			+m[0][2]*m[2][1]*m[1][0]
			-m[0][2]*m[1][1]*m[2][0]
			-m[0][1]*m[1][0]*m[2][2]
			-m[0][0]*m[1][2]*m[2][1];
			if(fabs(det) < eps)
				return;
			for(int j = 0; j < 3; j++) {
				for(int i = 0; i < 3; i++)
					m[i][j] = sol[i];
				L[j] = (m[0][0]*m[1][1]*m[2][2]
						+m[0][1]*m[1][2]*m[2][0]
						+m[0][2]*m[2][1]*m[1][0]
						-m[0][2]*m[1][1]*m[2][0]
						-m[0][1]*m[1][0]*m[2][2]
						-m[0][0]*m[1][2]*m[2][1])/det;
				
				for(int i = 0; i < 3; i++)
					m[i][j] = dot(q[i],q[j])*2;
			}
			res = outer[0];
			for(int i = 0; i < 3; i++) {
				res.x += q[i].x*L[i];
				res.y += q[i].y*L[i];
				res.z += q[i].z*L[i];
			}
			radius=dist(res,outer[0]);
	}
//	cout << nouter <<"***" << radius<<"**"<<endl;
}
void minball(int n) {
	ball();
	if(nouter < 4) {
		for(int i = 0; i < n; i++) {
			if(dist(res,pt[i])-radius>eps) {
				outer[nouter]=pt[i];
				++nouter;
				minball(i);
				--nouter;
				if(i > 0){
					Tpoint Tt=pt[i];
					memmove(&pt[1],&pt[0],sizeof(Tpoint)*i);
					pt[0] = Tt;
				}
			}
		}
	}
}
double smallest_ball() {
	radius = -1;
	for(int i = 0; i < npoint; i++) {
		if(dist(res,pt[i])-radius>eps) {
			nouter = 1;
			outer[0]=pt[i];
			minball(i);
		}
	}
	return sqrt(radius);
}
int main() {
	scanf("%d",&npoint);
	for(int i = 0; i < npoint; i++) {
		pt[i].scan();
	}
	db ans = smallest_ball();
	printf("%.15f\n",ans);
	return 0;
}
\end{lstlisting}


\subsection{模拟退火}
\begin{lstlisting}
// POJ2069 最小球覆盖
#include <iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
using namespace std;
const double eps=1e-7;
struct point3D
{
    double x,y,z;
} data[35];
int n;
double dis(point3D a,point3D b)
{
    return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y)+(a.z-b.z)*(a.z-b.z));
}
double solve()
{
    double step=100,ans=1e30,mt;
    point3D z;
    z.x=z.y=z.z=0;
    int s=0;
    while(step>eps)
    {
        for(int i=0; i<n; i++)
            if(dis(z,data[s])<dis(z,data[i])) s=i;
        mt=dis(z,data[s]);
        ans=min(ans,mt);
        z.x+=(data[s].x-z.x)/mt*step;
        z.y+=(data[s].y-z.y)/mt*step;
        z.z+=(data[s].z-z.z)/mt*step;
        step*=0.98;
    }
    return ans;
}
int main()
{
    double ans;
    while(~scanf("%d",&n),n)
    {
        for(int i=0; i<n; i++)
            scanf("%lf%lf%lf",&data[i].x,&data[i].y,&data[i].z);
        ans=solve();
        printf("%.5f\n",ans);
    return 0;
}

\end{lstlisting}

\subsection{最大空凸包}
\begin{lstlisting}
// O(n^3)
#include <bits/stdc++.h>
using namespace std;
#define LL long long
#define mod 1000000007
typedef struct Point
{
	int x, y;
	Point() {}
	Point(int x, int y): x(x),y(y) {}
	Point operator + (const Point &b) const {  return Point(x+b.x,y+b.y);  }
	Point operator - (const Point &b) const {  return Point(x-b.x,y-b.y);  }
	int operator * (const Point &b) const {  return x*b.y-y*b.x;  }
	int len() const {  return x*x+y*y;  }
	int operator < (const Point &a) const
	{
		if((*this)*a>0 || (*this)*a==0 && len()<a.len())
			return 1;
		return 0;
	}
}Point;
int n;
Point s[122], p[122];
int dp[122][122];
int Jud(int m)
{
	int ans, i, j, now, k, flag, S;
	memset(dp, 0, sizeof(dp));
	ans = 0;
	for(i=2;i<=m;i++)
	{
		now = i-1;
		while(now>=1 && p[i]*p[now]==0)
			now--;
		flag = 0;
		if(now==i-1)
			flag = 1;
		while(now>=1)
		{
			S = p[now]*p[i];
			k = now-1;
			while(k>=1 && (p[now]-p[i])*(p[k]-p[now])>0)
				k--;
			if(k>=1)
				S += dp[now][k];
			if(flag)
				dp[i][now] = S;
			ans = max(ans, S);
			now = k;
		}
		if(flag==0)
			continue;
		for(j=1;j<=i-1;j++)
			dp[i][j] = max(dp[i][j],dp[i][j-1]);
	}
	return ans;
}
int main(void)
{
	int T, i, j, m, ans;
	scanf("%d", &T);
	while(T--)
	{
		scanf("%d", &n);
		for(i=1;i<=n;i++)
			scanf("%d%d", &s[i].x, &s[i].y);
		ans = 0;
		for(i=1;i<=n;i++)
		{
			m = 0;
			for(j=1;j<=n;j++)
			{
				if(s[j].y>s[i].y || s[j].y==s[i].y && s[j].x>=s[i].x)
					p[++m] = s[j]-s[i];
			}
			sort(p+1, p+m+1);
			ans = max(ans, Jud(m));
		}
		printf("%.1f\n", ans/2.0);
	}
	return 0;
}
\end{lstlisting}

\subsection{凸包内最大三角形}
\begin{lstlisting}
/*
translation:
	给出一组点，从这些点里面选择三个点构成三角形。求这个三角形面积最大是多少？
solution:
	凸包
	很容易想到三角形的三个点肯定在凸包上面，但是关键怎么找出来三个点。一一枚举肯定超时。
note:
	* 如果固定一条边的话，那么枚举剩下的一个点，在枚举过程中面积肯定有达到极大值后又减小。根据这一特性，可以先固定
	  一点i，然后让另外两点a，b不断旋转来找三角形面积最大值（a,b事先设定成是点1和点2）。具体步骤如下：
	  1.枚举i后就将i固定，旋转a，直到找到三角形的最大值。同时更新答案。
	  2.旋转b，直到找到此时三角形的最大值。同时更新答案。此时即找到三角形一点为i时的最大面积。
	  3.枚举下一个i，重复1,2步骤。
*/
#include <iostream>
#include <cstdio>
#include <vector>
#include <cmath>
#include <algorithm>
 
using namespace std;
const int maxn = 50000 + 5;
 
struct Point
{
    double x, y;
    Point(){}
    Point(double x_, double y_):x(x_),y(y_){}
} p[maxn], ch[maxn];
typedef Point Vector;
int n;
 
Vector operator + (Vector a, Vector b)  { return Vector(a.x + b.x, a.y + b.y); }
Vector operator - (Point a, Point b)    { return Point(a.x - b.x, a.y - b.y); }
Vector operator * (Vector a, double p)  { return Vector(a.x * p, a.y * p); }
Vector operator / (Vector a, double p)  { return Vector(a.x / p, a.y / p); }
 
bool operator < (const Point& a, const Point& b)
{
    return a.x < b.x || (a.x == b.x && a.y < b.y);
}
 
const double eps = 1e-10;
int dcmp(double x)
{
    if(fabs(x) < eps)    return 0;
    else                return x < 0 ? -1 : 1;
}
 
bool operator == (const Point& a, const Point& b)
{
    return dcmp(a.x - b.x) == 0 && dcmp(a.y - b.y) == 0;
}
 
double dot(Vector a, Vector b)      { return a.x * b.x + a.y * b.y; }
double length(Vector a)             { return sqrt(dot(a, a)); }
double angle(Vector a, Vector b)    { return acos(dot(a, b) / length(a) / length(b)); }
double angle(Vector v)              { return atan2(v.y, v.x); }
double cross(Vector a, Vector b)    { return a.x * b.y - b.x * a.y; }
double dist(Point p1,Point p2)      { return sqrt((p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y)); }
 
int convexHull(Point* p, int n, Point* ch)
{
	sort(p, p + n);
	int m = 0;
	for(int i = 0; i < n; i++) {
		while(m > 1 && cross(ch[m-1] - ch[m-2], p[i] - ch[m-2]) <= 0)	m--;
		ch[m++] = p[i];
	}
	int k = m;
	for(int i = n-2; i >= 0; i--) {
		while(m > k && cross(ch[m-1] - ch[m-2], p[i] - ch[m-2]) <= 0)	m--;
		ch[m++] = p[i];
	}
	if(n > 1)	m--;
	return m;
}
 
double area(Point a,Point b,Point c){
    return (a.x-c.x)*(b.y-c.y)-(b.x-c.x)*(a.y-c.y);
}
 
double solve()
{
	int m = convexHull(p, n, ch);
	//ch[++m] = ch[0];
	int a = 1, b = 2;
	double res = 0;
	for(int i = 0; i < m; i++) {
		while(area(ch[i], ch[a], ch[(b+1)%m]) > area(ch[i], ch[a], ch[b]))
			b = (b + 1) % m;
		res = max(res, area(ch[i], ch[a], ch[b]) / 2.0);
		while(area(ch[i], ch[(a+1)%m], ch[b]) > area(ch[i], ch[a], ch[b]))
			a = (a + 1) % m;
		res = max(res, area(ch[i], ch[a], ch[b]) / 2.0);
	}
	return res;
}
 
int main()
{
	//freopen("in.txt", "r", stdin);
    while(~scanf("%d", &n) && n != -1) {
		for(int i = 0; i < n; i++) {
			scanf("%lf%lf", &p[i].x, &p[i].y);
		}
 
		printf("%.2f\n", solve());
    }
    return 0;
}
\end{lstlisting}

\subsection{Andrew求凸包}
\begin{lstlisting}
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <cmath>
 
using namespace std;
 
const double eps = 1e-8,Pi=3.14159265;
 
int n;
 
inline int dcmp(double x)//三态函数
{
	if(fabs(x) < eps)	return 0;
	else return x>0 ? 1 : -1;
}
 
#define Vector Point
struct Point
{
	double x,y;
	inline Point(double x=0,double y=0):x(x),y(y) {}
}p[10000+5],ch[10000+5];
 
bool myCmp(Point A, Point B)
{
	if(A.x != B.x)	return A.x < B.x;
	else return A.y < B.y;
} 
 
Vector operator + (Vector A, Vector B) {return Vector(A.x + B.x, A.y + B.y);}
Vector operator - (Vector A, Vector B) {return Vector(A.x - B.x, A.y - B.y);}
bool operator == (const Vector& A, const Vector& B) {return dcmp(A.x-B.x)==0 && dcmp(A.y-B.y)==0;}
 
inline double Cross(Vector A, Vector B)//叉积
{
	return A.x * B.y - A.y * B.x;
}
 
int ConvexHull()
{
	sort(p,p+n,myCmp);
	int m = 0;
	for(int i = 0; i <n; i++)
	{
		while(m > 1 && dcmp(Cross(ch[m-1]-ch[m-2], p[i]-ch[m-2])) <= 0) m--;
		ch[m++] = p[i];
	}
	int k = m;
	for(int i = n-2; i >= 0; i--)
	{
		while(m > k && dcmp(Cross(ch[m-1]-ch[m-2], p[i]-ch[m-2])) <= 0) m--;
		ch[m++] = p[i];
	}
	if(n > 1) m--;
	return m;
}
 
double Dis(Point A, Point B)
{
	return sqrt((A.x - B.x)*(A.x - B.x) + (A.y - B.y)*(A.y - B.y));
}
 
int main()
{
	int m;
	cin>>n;
	for(int i = 0; i < n; i++)
	{
		int a,b;
		cin>>a>>b;
		p[i] = Point(a,b);
	}
	m = ConvexHull();
	//计算凸包周长 
	double ans=0.0;
	for(int i = 0; i < m-1; i++)
		ans += Dis(ch[i],ch[i+1]);
	ans += Dis(ch[m-1],ch[0]);
	printf("%.1f",ans);
}
\end{lstlisting}

\subsection{判断四点共面}
\begin{lstlisting}
struct  point
{
    double x, y, z;
    point  operator - (point &o)
    {
        point  ans;
        ans.x = this->x - o.x;
        ans.y = this->y - o.y;
        ans.z = this->z - o.z;
        return ans;
    }
};

double  dot_product(const point &a, const point &b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

point cross_product(const point &a, const point &b)
{
    point  ans;
    ans.x = a.y * b.z - a.z * b.y;
    ans.y = a.z * b.x - a.x * b.z;
    ans.z = a.x * b.y - a.y * b.x;
    return ans;
}

int main()
{
    point p[4];
    int T;
    for (scanf("%d", &T); T--;)
    {
        for (int i = 0; i < 4; ++i)
        {
            scanf("%lf%lf%lf", &p[i].x, &p[i].y, &p[i].z);
        }
        puts(dot_product(p[3] - p[0], cross_product(p[2] - p[0], p[1] - p[0])) == 0.0 ? "Yes\n" : "No\n");
    }
    return 0;
}
\end{lstlisting}

\subsection{求多边形重心}
\begin{lstlisting}
/*
 *  求多边形重心
 *  INIT: pnt[]已按顺时针(或逆时针)排好序; | CALL: res = bcenter(pnt, n);
 */
struct point
{
    double x, y;
};

point bcenter(point pnt[], int n)
{
    point p, s;
    double tp, area = 0, tpx = 0, tpy = 0;
    p.x = pnt[0].x;
    p.y = pnt[0].y;
    for (int i = 1; i <= n; ++i)
    {   //  point:0 ~ n - 1
        s.x = pnt[(i == n) ? 0 : i].x;
        s.y = pnt[(i == n) ? 0 : i].y;
        tp = (p.x * s.y - s.x * p.y);
        area += tp / 2;
        tpx += (p.x + s.x) * tp;
        tpy += (p.y + s.y) * tp;
        p.x = s.x;
        p.y = s.y;
    }
    s.x = tpx / (6 * area);
    s.y = tpy / (6 * area);
    return s;
}
\end{lstlisting}

\subsection{三角形相关重点}
\begin{lstlisting}
//三角形重点

//设三角形的三条边为a, b, c, 且不妨假设a <= b <= c.
//面积

//三角形面积可以根据海伦公式求得：

    s = sqrt(p * (p - a) * (p - b) * (p - c));
    p = (a + b + c) / 2;

//关键点与A, B, C三顶点距离之和
/*
费马点

该点到三角形三个顶点的距离之和最小。
有个有趣的结论:
若三角形的三个内角均小于120度,那么该点连接三个顶点形成的三个角均为120度;若三角形存在一个内角大于120度,则该顶点就是费马点。
计算公式如下:

若有一个内角大于120度(这里假设为角C),则距离为a + b;若三个内角均小于120度,则距离为sqrt((a * a + b * b + c * c + 4 * sqrt(3.0) * s) / 2)。
内心

角平分线的交点。
令x = (a + b - c) / 2, y = (a - b + c) / 2, z = (-a + b + c) / 2, h = s / p.
计算公式为sqrt(x * x + h * h) + sqrt(y * y + h * h) + sqrt(z * z + h * h)。
重心

中线的交点。
计算公式如下:
2.0 / 3 * (sqrt((2 * (a * a + b * b) - c * c) / 4)
+ sqrt((2 * (a * a + c * c) - b * b) / 4) + sqrt((2 * (b * b + c * c) - a * a) / 4))。
垂心

垂线的交点。
计算公式如下:
3 * (c / 2 / sqrt(1 - cosC * cosC))。
外心

三点求圆心坐标。
*/

Point waixin(Point a, Point b, Point c)
{
    double a1 = b.x - a.x, b1 = b.y - a.y, c1 = (a1 * a1 + b1 * b1) / 2;
    double a2 = c.x - a.x, b2 = c.y - a.y, c2 = (a2 * a2 + b2 * b2) / 2;
    double d = a1 * b2 - a2 * b1;
    return Point(a.x + (c1 * b2 - c2 * b1) / d, a.y + (a1 * c2 -a2 * c1) / d);
}
\end{lstlisting}

\subsection{旋转卡壳}
\begin{lstlisting}
//求解平面最远点对

struct Point
{
    int x, y;
    Point(int _x = 0, int _y = 0)
    {
        x = _x;
        y = _y;
    }
    Point operator - (const Point &b)const
    {
        return Point(x - b.x, y - b.y);
    }
    int operator ^(const Point &b)const
    {
        return x * b.y - y * b.x;
    }
    int operator *(const Point &b)const
    {
        return x * b.x + y * b.y;
    }
    void input()
    {
        scanf("%d%d", &x, &y);
        return ;
    }
};

//  距离的平方
int dist2(Point a, Point b)
{
    return (a - b) * (a - b);
}

//  二维凸包,int
const int MAXN = 50010;
Point list[MAXN];
int Stack[MAXN], top;
bool _cmp(Point p1, Point p2)
{
    int tmp = (p1 - list[0]) ^ (p2 - list[0]);
    if (tmp > 0)
    {
        return true;
    }
    else if (tmp == 0 && dist2(p1, list[0]) <= dist2(p2, list[0]))
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Graham(int n)
{
    Point p0;
    int k = 0;
    p0 = list[0];
    for (int i = 1; i < n; i++)
    {
        if (p0.y > list[i].y || (p0.y == list[i].y && p0.x > list[i].x))
        {
            p0 = list[i];
            k = i;
        }
    }
    swap(list[k], list[0]);
    sort(list + 1, list + n, _cmp);
    if (n == 1)
    {
        top = 1;
        Stack[0] = 0;
        return ;
    }
    if (n == 2)
    {
        top = 2;
        Stack[0] = 0;
        Stack[1] = 1;
        return ;
    }
    Stack[0] = 0;
    Stack[1] = 1;
    top = 2;
    for (int i = 2; i < n; i++)
    {
        while (top > 1 && ((list[Stack[top - 1]] - list[Stack[top - 2]]) ^ (list[i] - list[Stack[top - 2]])) <= 0)
        {
            top--;
        }
        Stack[top++] = i;
    }
    return ;
}

//  旋转卡壳,求两点间距离平方的最大值
int rotating_calipers(Point p[],int n)
{
    int ans = 0;
    Point v;
    int cur = 1;
    for (int i = 0; i < n; i++)
    {
        v = p[i] - p[(i + 1) % n];
        while ((v ^ (p[(cur + 1) % n] - p[cur])) < 0)
        {
            cur = (cur + 1) % n;
        }
        ans = max(ans, max(dist2(p[i], p[cur]), dist2(p[(i + 1) % n], p[(cur + 1) % n])));
    }
    return ans;
}

Point p[MAXN];

int main()
{
    int n;
    while (scanf("%d", &n) == 1)
    {
        for (int i = 0; i < n; i++)
        {
            list[i].input();
        }
        Graham(n);
        for (int i = 0; i < top; i++)
        {
            p[i] = list[Stack[i]];
        }
        printf("%d\n", rotating_calipers(p, top));
    }
    return 0;
}

//求解平面点集最大三角形

struct Point
{
    int x, y;
    Point(int _x = 0, int _y = 0)
    {
        x = _x;
        y = _y;
    }
    Point operator - (const Point &b)const
    {
        return Point(x - b.x, y - b.y);
    }
    int operator ^(const Point &b)const
    {
        return x * b.y - y * b.x;
    }
    int operator *(const Point &b)const
    {
        return x * b.x + y * b.y;
    }
    void input()
    {
        scanf("%d%d", &x, &y);
        return ;
    }
};

//  距离的平方
int dist2(Point a, Point b)
{
    return (a - b) * (a - b);
}

//  二维凸包,int
const int MAXN = 50010;
Point list[MAXN];
int Stack[MAXN], top;
bool _cmp(Point p1, Point p2)
{
    int tmp = (p1 - list[0]) ^ (p2 - list[0]);
    if (tmp > 0)
    {
        return true;
    }
    else if (tmp == 0 && dist2(p1, list[0]) <= dist2(p2, list[0]))
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Graham(int n)
{
    Point p0;
    int k = 0;
    p0 = list[0];
    for (int i = 1; i < n; i++)
    {
        if (p0.y > list[i].y || (p0.y == list[i].y && p0.x > list[i].x))
        {
            p0 = list[i];
            k = i;
        }
    }
    swap(list[k], list[0]);
    sort(list + 1, list + n, _cmp);
    if (n == 1)
    {
        top = 1;
        Stack[0] = 0;
        return ;
    }
    if (n == 2)
    {
        top = 2;
        Stack[0] = 0;
        Stack[1] = 1;
        return ;
    }
    Stack[0] = 0;
    Stack[1] = 1;
    top = 2;
    for (int i = 2; i < n; i++)
    {
        while (top > 1 && ((list[Stack[top - 1]] - list[Stack[top - 2]]) ^ (list[i] - list[Stack[top - 2]])) <= 0)
        {
            top--;
        }
        Stack[top++] = i;
    }
    return ;
}

int rotating_calipers(Point p[], int n)
{
    int ans = 0;
    Point v;
    for (int i = 0; i < n; i++)
    {
        int j = (i + 1) % n;
        int k = (j + 1) % n;
        while (j != i && k != i)
        {
            ans = max(ans, abs((p[j] - p[i]) ^ (p[k] - p[i])));
            while (((p[i] - p[j]) ^ (p[(k + 1) % n] - p[k])) < 0)
            {
                k = (k + 1) % n;
            }
            j = (j + 1) % n;
        }
    }
    return ans;
}

Point p[MAXN];

int main()
{
    int n;
    while (scanf("%d",&n) == 1)
    {
        if (n == -1)
        {
            break;
        }
        for (int i = 0; i < n; i++)
        {
            list[i].input();
        }
        Graham(n);
        for (int i = 0; i < top; i++)
        {
            p[i] = list[Stack[i]];
        }
        printf("%.2f\n", (double)rotating_calipers(p, top) / 2);
    }
    return 0;
}

//求解两凸包最小距离


const double eps = 1e-8;

int sgn(double x)
{
    if (fabs(x) < eps)
    {
        return 0;
    }
    if (x < 0)
    {
        return -1;
    }
    else
    {
        return 1;
    }
}

struct Point
{
    double x, y;
    Point(double _x = 0, double _y = 0)
    {
        x = _x;
        y = _y;
    }
    Point operator - (const Point &b)const
    {
        return Point(x - b.x, y - b.y);
    }
    double operator ^ (const Point &b)const
    {
        return x * b.y - y * b.x;
    }
    double operator * (const Point &b)const
    {
        return x * b.x + y * b.y;
    }
    void input()
    {
        scanf("%lf%lf", &x, &y);
    }
};

struct Line
{
    Point s, e;
    Line(){}
    Line(Point _s, Point _e)
    {
        s = _s;
        e = _e;
    }
};

//  两点间距离
double dist(Point a, Point b)
{
    return sqrt((a - b) * (a - b));
}

//  点到线段的距离,返回点到线段最近的点
Point NearestPointToLineSeg(Point P, Line L)
{
    Point result;
    double t = ((P - L.s) * (L.e - L.s)) / ((L.e - L.s) * (L.e - L.s));
    if (t >=0 && t <= 1)
    {
        result.x = L.s.x + (L.e.x - L.s.x) * t;
        result.y = L.s.y + (L.e.y - L.s.y) * t;
    }
    else
    {
        if (dist(P,L.s) < dist(P,L.e))
        {
            result = L.s;
        }
        else
        {
            result = L.e;
        }
    }
    return result;
}

/*
 * 求凸包,Graham算法
 * 点的编号0~n-1
 * 返回凸包结果Stack[0~top-1]为凸包的编号 
 */
const int MAXN = 10010;
Point list[MAXN];
int Stack[MAXN], top;   //  相对于list[0]的极角排序
bool _cmp(Point p1, Point p2)
{
    double tmp = (p1 - list[0]) ^ (p2 - list[0]);
    if (sgn(tmp) > 0)
    {
        return true;
    }
    else if (sgn(tmp) == 0 && sgn(dist(p1, list[0]) - dist(p2, list[0])) <= 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Graham(int n)
{
    Point p0;
    int k = 0;
    p0 = list[0];   //  找最下边的一个点
    for (int i = 1; i < n; i++)
    {
        if ((p0.y > list[i].y) || (p0.y == list[i].y && p0.x > list[i].x))
        {
            p0 = list[i];
            k = i;
        }
    }
    swap(list[k], list[0]);
    sort(list + 1, list + n, _cmp);
    if (n == 1)
    {
        top = 1;
        Stack[0] = 0;
        return ;
    }
    if (n == 2)
    {
        top = 2;
        Stack[0] = 0;
        Stack[1] = 1;
        return ;
    }
    Stack[0] = 0;
    Stack[1] = 1;
    top = 2;
    for (int i = 2; i < n; i++)
    {
        while (top > 1 && sgn((list[Stack[top - 1]] - list[Stack[top - 2]]) ^ (list[i] - list[Stack[top - 2]])) <= 0)
        {
            top--;
        }
        Stack[top++] = i;
    }
    return ;
}

//  点p0到线段p1p2的距离
double pointtoseg(Point p0, Point p1, Point p2)
{
    return dist(p0, NearestPointToLineSeg(p0, Line(p1, p2)));
}

//  平行线段p0p1和p2p3的距离
double dispallseg(Point p0, Point p1, Point p2, Point p3)
{
    double ans1 = min(pointtoseg(p0, p2, p3), pointtoseg(p1, p2, p3));
    double ans2 = min(pointtoseg(p2, p0, p1), pointtoseg(p3, p0, p1));
    return min(ans1, ans2);
}

//  得到向量a1a2和b1b2的位置关系
double Get_angle(Point a1, Point a2, Point b1, Point b2)
{
    return (a2 - a1) ^ (b1 - b2);
}

double rotating_calipers(Point p[], int np, Point q[], int nq)
{
    int sp = 0, sq = 0;
    for (int i = 0; i < np; i++)
    {
        if (sgn(p[i].y - p[sp].y) < 0)
        {
            sp = i;
        }
    }
    for (int i = 0; i < nq; i++)
    {
        if (sgn(q[i].y - q[sq].y) > 0)
        {
            sq = i;
        }
    }
    double tmp;
    double ans = dist(p[sp], q[sq]);
    for (int i = 0; i < np; i++)
    {
        while (sgn(tmp = Get_angle(p[sp], p[(sp + 1) % np], q[sq], q[(sq + 1) % nq])) < 0)
        {
            sq = (sq + 1) % nq;
        }
        if (sgn(tmp) == 0)
        {
            ans = min(ans, dispallseg(p[sp], p[(sp + 1) % np], q[sq], q[(sq + 1) % nq]));
        }
        else
        {
            ans = min(ans, pointtoseg(q[sq], p[sp], p[(sp + 1) % np]));
        }
        sp = (sp + 1) % np;
    }
    return ans;
}

double solve(Point p[], int n, Point q[], int m)
{
    return min(rotating_calipers(p, n, q, m), rotating_calipers(q, m, p, n));
}

Point p[MAXN], q[MAXN];

int main()
{
    int n, m;
    while (scanf("%d%d", &n, &m) == 2)
    {
        if (n == 0 && m == 0)
        {
            break;
        }
        for (int i = 0; i < n; i++)
        {
            list[i].input();
        }
        Graham(n);
        for (int i = 0; i < top; i++)
        {
            p[i] = list[i];
        }
        n = top;
        for (int i = 0; i < m; i++)
        {
            list[i].input();
        }
        Graham(m);
        for (int i = 0; i < top; i++)
        {
            q[i] = list[i];
        }
        m = top;
        printf("%.4f\n", solve(p, n, q, m));
    }
    return 0;
}
\end{lstlisting}

\subsection{凸包内最大三角形}
\begin{lstlisting}
#include <bits/stdc++.h>

using namespace std;

const double eps = 1e-8;
#define N 100010

inline int sgn(double x) {
    if (fabs(x) < eps) return 0;
    else return x > 0 ? 1 : -1;
}

struct Point {
    double x, y;

    Point() {}

    Point(double x, double y) : x(x), y(y) {}

    bool operator<(const Point &other) const {
        if (sgn(x - other.x) == 0) {
            return y < other.y;
        } else {
            return x < other.x;
        }
    }

    double operator^(const Point &other) const {
        return x * other.y - y * other.x;
    }

    Point operator+(const Point &other) const {
        return {x + other.x, y + other.y};
    }

    Point operator-(const Point &other) const {
        return {x - other.x, y - other.y};
    }
} p[N], tmp[N];

void convexhull(Point *s, int &n) {
    sort(s, s + n);
    int m = 0;
    s[n] = s[0];
    for (int i = 0; i < n; i++) {
        while (m > 1 && sgn((tmp[m - 1] - tmp[m - 2]) ^ (s[i] - tmp[m - 2])) <= 0)
            m--;
        tmp[m++] = s[i];
    }
    int k = m;
    for (int i = n - 2; i >= 0; i--) {
        while (m > k && sgn((tmp[m - 1] - tmp[m - 2]) ^ (s[i] - tmp[m - 2])) <= 0)
            m--;
        tmp[m++] = s[i];
    }

    m--;
    n = m;
    for (int i = 0; i < n; ++i) {
        s[i] = tmp[i];
    }
}

int n;

int main() {
    while (scanf("%d", &n) != EOF) {
        if (n == -1) {
            break;
        }
        for (int i = 0; i < n; ++i) {
            scanf("%lf %lf", &p[i].x, &p[i].y);
        }
        convexhull(p, n);
        p[n] = p[0];
        p[n + 1] = p[1];
        p[n + 2] = p[2];
        double sum = 0;
        for (int i = 0, j = 1, k = 2; i < n; ++i) {
            while (fabs(((p[j] - p[i]) ^ (p[k + 1] - p[i]))) - fabs(((p[j] - p[i]) ^ (p[k] - p[i]))) >= eps) {
                k = (k + 1) % n;
            }
            while (fabs(((p[k] - p[i]) ^ (p[j + 1] - p[i]))) - fabs(((p[k] - p[i]) ^ (p[j] - p[i]))) >= eps) {
                j = (j + 1) % n;
            }
            double res = fabs((p[j] - p[i]) ^ (p[k] - p[i]));
            if (sgn(res - sum) >= 0) {
                sum = res;
            }
        }
        printf("%.2f\n", sum / 2.0);
    }
    return 0;
}
\end{lstlisting}
