#include<cstring>
#include<queue>
#include<cctype>
#include<algorithm>
#include<cstdio>
#include<iostream>
#include<cmath>
using namespace std;
#define dbg(x...) do { cout << "\033[32;1m" << #x << " -> "; err(x); } while (0) 
void err() { cout << "\033[39;0m" << endl; } 
template <class T, class... Ts> void err(const T& arg, const Ts&... args) { cout << arg << ' '; err(args...); }
#define ll long long
#define re register
#define gc getchar
#define pc putchar
#define cs const
#define st static

inline
int getint(){
    re int num=0;
    re bool f=1;
    re char ch=getchar();
    while(!isdigit(ch)){if(ch=='-')f=0;ch=gc();}
    while(isdigit(ch))num=(num<<3)+(num<<1)+(ch^48),ch=gc();
    return f?num:-num;
}

int x[1005],y[1005],h[1005];
int n;
double cost[1005][1005];
double dist[1005][1005];
double w[1005];
bool vis[1005];
double val[1005];
double ans,L;
inline
double prim(double k){
    double x=0.0,y=0.0;
    for(int re i=1;i<=n;++i){
        w[i]=cost[1][i]-dist[1][i]*k;
        val[i]=cost[1][i];
    }
    memset(vis,0,sizeof vis);
    vis[1]=true;
    for(int re kk=2;kk<=n;++kk){
        double minn=1e9;
        int pos=0;
        for(int re i=1;i<=n;++i){
            if(vis[i])continue;
            if(w[i]<minn)minn=w[i],pos=i;
        }
        vis[pos]=1;
        x+=val[pos];
        y+=val[pos]-w[pos];
        for(int re i=1;i<=n;++i){
            if(vis[i])continue;
            if(w[i]>cost[pos][i]-dist[pos][i]*k){
                w[i]=cost[pos][i]-dist[pos][i]*k;
                val[i]=cost[pos][i];
            }
        }
    }
    dbg(x, k, y);
	return x*k/y;
}

signed main(){
    while(n=getint()){
        double maxn=-1e9,minn=1e9;
        for(int re i=1;i<=n;++i)x[i]=getint(),y[i]=getint(),h[i]=getint();
        for(int re i=1;i<=n;++i){
            for(int re j=i+1;j<=n;++j) {
            dist[i][j]=dist[j][i]=sqrt((x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j])),
            cost[i][j]=cost[j][i]=fabs(h[i]-h[j]),
            minn=min(minn,cost[i][j]),
            maxn=max(maxn,dist[i][j]);
        					printf("%d %d %lf %lf\n", i, j, cost[i][j], dist[i][j]);
			}

		}
        L=minn/maxn;
		printf("%lf\n", L);
		while(true){
            ans=prim(L);
            if(fabs(ans-L)<1e-8)break;
            L=ans;
        }
        printf("%.3f\n",ans);
    //  printf("%.3lf\n",ans);这样写有毒，会WA
    }
    return 0;
}
