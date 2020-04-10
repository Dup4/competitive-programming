//minamoto
#include<bits/stdc++.h>
#define R register
#define inline __inline__ __attribute__((always_inline))
#define fp(i,a,b) for(R int i=(a),I=(b)+1;i<I;++i)
#define fd(i,a,b) for(R int i=(a),I=(b)-1;i>I;--i)
#define go(u) for(int i=head[u],v=e[i].v;i;i=e[i].nx,v=e[i].v)
template<class T>inline bool cmax(T&a,const T&b){return a<b?a=b,1:0;}
template<class T>inline bool cmin(T&a,const T&b){return a>b?a=b,1:0;}
using namespace std;
const int N=2005;const double Pi=acos(-1.0);
struct Point{
    int x,y;
    inline Point(){}
    inline Point(R int xx,R int yy):x(xx),y(yy){}
    inline Point operator +(const Point &b)const{return Point(x+b.x,y+b.y);}
    inline Point operator -(const Point &b)const{return Point(x-b.x,y-b.y);}
    inline double norm(){return sqrt(x*x+y*y);}
    inline double ang(){return atan2(y,x);}
};
struct Cir{
    Point p;int r;
    inline double oint(R double t1,R double t2){
        return r*(r*(t2-t1)+p.x*(sin(t2)-sin(t1))-p.y*(cos(t2)-cos(t1)));
    }
    inline bool in(const Cir &b)const{return (p-b.p).norm()+b.r<=r;}
    inline bool out(const Cir &b)const{return r+b.r<=(p-b.p).norm();}
}c[N];
struct node{
    double l,r;
    inline node(R double ll,R double rr):l(ll),r(rr){}
    inline bool operator <(const node &b)const{return r<b.r;}
};
set<node>s[N];double res;int n;bool vis[N];
typedef set<node>::iterator IT;
inline void upd(R double &ang){
    if(ang<-Pi)ang+=2*Pi;
    if(ang>Pi)ang-=2*Pi;
}
void remove(int id,double l,double r){
    for(IT it=s[id].lower_bound(node(0,l)),tmp;it!=s[id].end()&&it->l<r;it=tmp){
        double nl=it->l,nr=it->r;
        tmp=it,++tmp,s[id].erase(it),res-=c[id].oint(nl,nr);
        if(nl<l)s[id].insert(node(nl,l)),res+=c[id].oint(nl,l);
        if(nr>r)s[id].insert(node(r,nr)),res+=c[id].oint(r,nr);
    }
}
int main(){
//  freopen("testdata.in","r",stdin);
    scanf("%*d%d",&n);
    fp(i,1,n){
        vis[i]=1;
        scanf("%d%d%d",&c[i].p.x,&c[i].p.y,&c[i].r);
        fp(j,1,i-1)if(vis[j]){
            if(c[j].r>=c[i].r&&c[j].in(c[i])){vis[i]=0;break;}
            if(c[i].r>c[j].r&&c[i].in(c[j]))vis[j]=0,remove(j,-Pi,Pi);
        }
        if(!vis[i]){printf("%.10lf\n",res*0.5);continue;}
        res+=c[i].r*c[i].r*Pi*2,s[i].insert(node(-Pi,Pi));
        fp(j,1,i-1)if(vis[j]&&!c[i].out(c[j])){
            double dis=(c[i].p-c[j].p).norm(),ang,cur,l,r;
            cur=(c[j].p-c[i].p).ang();
            ang=acos((dis*dis+c[i].r*c[i].r-c[j].r*c[j].r)/(2*c[i].r*dis));
            l=cur-ang,r=cur+ang,upd(l),upd(r);
            if(l<=r)remove(i,l,r);else remove(i,-Pi,r),remove(i,l,Pi);
            cur=(c[i].p-c[j].p).ang();
            ang=acos((dis*dis+c[j].r*c[j].r-c[i].r*c[i].r)/(2*c[j].r*dis));
            l=cur-ang,r=cur+ang,upd(l),upd(r);
            if(l<r)remove(j,l,r);else remove(j,-Pi,r),remove(j,l,Pi);
        }
        printf("%.10lf\n",res*0.5);
    }
    return 0;
}
