#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<set>
#include<map>
#include<vector>
#include<queue>
using namespace std;
#define ll long long
#define RG register
#define MAX 222222
#define MOD 1000000007
inline int read()
{
    RG int x=0,t=1;RG char ch=getchar();
    while((ch<'0'||ch>'9')&&ch!='-')ch=getchar();
    if(ch=='-')t=-1,ch=getchar();
    while(ch<='9'&&ch>='0')x=x*10+ch-48,ch=getchar();
    return x*t;
}
int fpow(int a,int b)
{
    int s=1;
    while(b){if(b&1)s=1ll*s*a%MOD;a=1ll*a*a%MOD;b>>=1;}
    return s;
}
struct Line{int v,next;}e[MAX<<1];
int h[MAX],cnt=1;
inline void Add(int u,int v){e[cnt]=(Line){v,h[u]};h[u]=cnt++;}
int a[MAX],b[MAX],n;
int phi[MAX],mu[MAX],pri[MAX],tot;
bool zs[MAX];
void pre(int N)
{
    zs[1]=true;phi[1]=mu[1]=1;
    for(int i=2;i<=N;++i)
    {
        if(!zs[i])pri[++tot]=i,mu[i]=-1,phi[i]=i-1;
        for(int j=1;j<=tot&&i*pri[j]<=N;++j)
        {
            zs[i*pri[j]]=true;
            if(i%pri[j])phi[i*pri[j]]=phi[i]*phi[pri[j]],mu[i*pri[j]]=-mu[i];
            else{mu[i*pri[j]]=0,phi[i*pri[j]]=phi[i]*pri[j];break;}
        }
    }
}
int dfn[MAX],low[MAX],size[MAX],hson[MAX],top[MAX],fa[MAX],tim,dep[MAX];
void dfs1(int u,int ff)
{
    fa[u]=ff;dep[u]=dep[ff]+1;size[u]=1;
    for(int i=h[u];i;i=e[i].next)
    {
        int v=e[i].v;if(v==ff)continue;
        dfs1(v,u);size[u]+=size[v];
        if(size[v]>size[hson[u]])hson[u]=v;
    }
}
void dfs2(int u,int tp)
{
    top[u]=tp;dfn[u]=++tim;
    if(hson[u])dfs2(hson[u],tp);
    for(int i=h[u];i;i=e[i].next)
        if(e[i].v!=fa[u]&&e[i].v!=hson[u])
            dfs2(e[i].v,e[i].v);
    low[u]=tim;
}
int LCA(int u,int v)
{
    while(top[u]^top[v])dep[top[u]]<dep[top[v]]?v=fa[top[v]]:u=fa[top[u]];
    return dep[u]<dep[v]?u:v;
}
bool cmp(int a,int b){return dfn[a]<dfn[b];}
int ans=0,K,p[MAX<<1],S[MAX],f[MAX];
bool vis[MAX];
void Plus(int &x,int y){x+=y;if(x>=MOD)x-=MOD;}
void DP(int u)
{
    f[u]=vis[u]?phi[a[u]]:0;
    Plus(ans,MOD-1ll*f[u]*f[u]%MOD*dep[u]%MOD);
    for(int i=h[u];i;i=e[i].next)
    {
        DP(e[i].v);
        Plus(ans,MOD-2ll*f[u]*f[e[i].v]%MOD*dep[u]%MOD);
        Plus(f[u],f[e[i].v]);
    }
}
int F[MAX],G[MAX];
int main()
{
    n=read();pre(n);
    for(int i=1;i<=n;++i)a[i]=read(),b[a[i]]=i;
    for(int i=1;i<n;++i)
    {
        int u=read(),v=read();
        Add(u,v);Add(v,u);
    }
    dfs1(1,0);dfs2(1,1);
    memset(h,0,sizeof(h));
    for(int T=1;T<=n;++T)
    {
        K=n/T;int s1=0,s2=0;cnt=1;
        for(int i=1;i<=K;++i)p[i]=b[i*T];
        for(int i=1;i<=K;++i)
            Plus(s1,phi[a[p[i]]]),Plus(s2,1ll*dep[p[i]]*phi[a[p[i]]]%MOD);
        for(int i=1;i<=K;++i)vis[p[i]]=true;
        sort(&p[1],&p[K+1],cmp);
        for(int i=K;i>1;--i)p[++K]=LCA(p[i],p[i-1]);
        sort(&p[1],&p[K+1],cmp);K=unique(&p[1],&p[K+1])-p-1;
        for(int i=1,tp=0;i<=K;++i)
        {
            while(tp&&low[S[tp]]<dfn[p[i]])--tp;
            Add(S[tp],p[i]);S[++tp]=p[i];
        }
        DP(p[1]);Plus(ans,ans);
        Plus(ans,2ll*s1*s2%MOD);
        for(int i=1;i<=K;++i)h[p[i]]=0,vis[p[i]]=false;
        F[T]=ans;ans=0;
    }
    for(int i=1;i<=n;++i)
        for(int j=i;j<=n;j+=i)
            if(mu[j/i]!=0)Plus(G[i],(mu[j/i]==1)?F[j]:(MOD-F[j]));
    for(int i=1;i<=n;++i)G[i]=1ll*G[i]*i%MOD*fpow(phi[i],MOD-2)%MOD;
    for(int i=1;i<=n;++i)Plus(ans,G[i]);
    ans=1ll*ans*fpow(n,MOD-2)%MOD*fpow(n-1,MOD-2)%MOD;
    printf("%d\n",ans);
    return 0;
}
