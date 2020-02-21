#include<bits/stdc++.h>
using namespace std;
typedef double db;
const int MAXN=105;
const db eps=1e-6;
inline int sgn(db x)
{
    if(x>eps)return 1;
    if(x<-eps)return -1;
    return 0;
}
struct Point
{
    db x,y;
    Point(){}
    Point(db _x,db _y):x(_x),y(_y){}
    Point operator + (const Point &t)const
    {
        return Point(x+t.x,y+t.y);
    }
    Point operator - (const Point &t)const
    {
        return Point(x-t.x,y-t.y);
    }
    Point operator * (const db &t)const
    {
        return Point(x*t,y*t);
    }
    db operator * (const Point &t)const
    {
        return x*t.y-y*t.x;
    }
    db operator ^ (const Point &t)const
    {
        return x*t.x+y*t.y;
    }
    db len()const
    {
        return sqrt(x*x+y*y);
    }
};
struct Line
{
    Point s,e;
    Line(){}
    Line(Point _s,Point _e):s(_s),e(_e){}
    pair<int,db> operator & (const Line &b)const
    {
        if(sgn((s-e)*(b.s-b.e))==0)return make_pair(0,0.0);
        db t=((s-b.s)*(b.s-b.e))/((s-e)*(b.s-b.e));
        db r=((b.s-s)*(s-e))/((b.s-b.e)*(s-e));
        return make_pair(t>-eps && t<1+eps && r>-eps && r<1+eps,t);
    }
};
db get_area(vector<Point> &p)
{
    int n=(int)p.size();
    db res=0;
    for(int i=0;i<n;i++)
        res+=p[i]*p[(i+1)%n];
    if(res<0)
    {
        res=-res;
        reverse(p.begin(),p.end());
    }
    return res/2;
}
bool inter(Line l1,Line l2)
{
    return max(l1.s.x,l1.e.x)>min(l2.s.x,l2.e.x)-eps
        && max(l2.s.x,l2.e.x)>min(l1.s.x,l1.e.x)-eps
        && max(l1.s.y,l1.e.y)>min(l2.s.y,l2.e.y)-eps
        && max(l2.s.y,l2.e.y)>min(l1.s.y,l1.e.y)-eps
        && sgn((l2.s-l1.e)*(l1.s-l1.e))*sgn((l2.e-l1.e)*(l1.s-l1.e))<=0
        && sgn((l1.s-l2.e)*(l2.s-l2.e))*sgn((l1.e-l2.e)*(l2.s-l2.e))<=0;
}
bool onseg(Point p,Line l)
{
    return sgn((p-l.s)*(p-l.e))==0 && sgn((p-l.s)^(p-l.e))<=0;
}
bool check_inside(Point t,vector<Point> &p)
{
    Line ray=Line(t,t+Point(2000,0));
    int n=(int)p.size(),res=0;
    for(int i=0;i<n;i++)
    {
        Line side=Line(p[i],p[(i+1)%n]);
        if(sgn(side.s.y-side.e.y)==0)continue;
        if(onseg(side.s,ray))res^=(sgn(side.s.y-side.e.y)>0);
        else if(onseg(side.e,ray))res^=(sgn(side.e.y-side.s.y)>0);
        else res^=inter(ray,side);
    }
    return res;
}
vector<Point> poly[MAXN];
db solve(int n)
{
    db res=0;
    for(int i=0;i<n;i++)
        for(int j=0;j<(int)poly[i].size();j++)
        {
            Line now=Line(poly[i][j],poly[i][(j+1)%(int)poly[i].size()]);
            vector<pair<db,int> > event;
            for(int k=0;k<n;k++)if(k!=i)
            {
                vector<db> inter;
                for(int l=0;l<(int)poly[k].size();l++)
                {
                    Line cut=Line(poly[k][l],poly[k][(l+1)%(int)poly[k].size()]);
                    pair<int,db> t=now&cut;
                    if(t.first)inter.push_back(t.second);
                }
                inter.push_back(0);
                inter.push_back(1);
                sort(inter.begin(),inter.end());
                vector<pair<db,db> > seg[2];
                for(int i=0;i+1<(int)inter.size();i++)
                    seg[~i&1].push_back(make_pair(inter[i],inter[i+1]));
                int t=check_inside(now.s,poly[k]);
                for(int i=0;i<(int)seg[t].size();i++)
                {
                    event.push_back(make_pair(seg[t][i].first,-1));
                    event.push_back(make_pair(seg[t][i].second,1));
                }
            }
            res+=now.s*now.e;
            sort(event.begin(),event.end());
            db las=0;
            int cnt=0;
            for(int i=0;i<(int)event.size();i++)
            {
                if(cnt>0)
                {
                    Point lef=now.s+now.e*las;
                    Point rig=now.s+now.e*event[i].first;
                    res-=lef*rig;
                }
                las=event[i].first;
                cnt-=event[i].second;
            }
        }
    return res/2;
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin>>n;
    for(int i=0;i<n;i++)
    {
        int m = 3;
        poly[i].resize(m);
        for(int j=0;j<m;j++)
            cin>>poly[i][j].x>>poly[i][j].y;
    }
    cout<<fixed<<setprecision(2)<<solve(n) - eps <<endl;
    return 0;
}
