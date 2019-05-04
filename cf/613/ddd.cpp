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
#define MAX 111111
inline int read()
{
    RG int x=0,t=1;RG char ch=getchar();
    while((ch<'0'||ch>'9')&&ch!='-')ch=getchar();
    if(ch=='-')t=-1,ch=getchar();
    while(ch<='9'&&ch>='0')x=x*10+ch-48,ch=getchar();
    return x*t;
}
struct Line{int v,next;}e[MAX<<1];
int h[MAX],cnt=1;
inline void Add(int u,int v){e[cnt]=(Line){v,h[u]};h[u]=cnt++;}
int fa[MAX],dep[MAX],size[MAX],hson[MAX],dfn[MAX],low[MAX],top[MAX],tim;
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
int p[MAX<<1],S[MAX];
bool cmp(int a,int b){return dfn[a]<dfn[b];}
int f[MAX],g[MAX],n,Q,K;
bool FL=false,vis[MAX];
void DP(int u)
{
    for(int i=h[u];i;i=e[i].next)
    {
        int v=e[i].v;DP(v);
        f[u]+=f[v];g[u]+=g[v];
    }
    if(vis[u])f[u]+=g[u],g[u]=1;
    else f[u]+=(g[u]>1),g[u]=(g[u]==1);
}
int Calc(int rt)
{
    DP(rt);
    for(int i=1;i<=K;++i)if(vis[p[i]]&&vis[fa[p[i]]])return -1;
    return f[rt];
}
int main()
{
    n=read();
    for(int i=1,u,v;i<n;++i)u=read(),v=read(),Add(u,v),Add(v,u);
    dfs1(1,0);dfs2(1,1);
    memset(h,0,sizeof(h));
    Q=read();
    while(Q--)
    {
        K=read();cnt=1;
        for(int i=1;i<=K;++i)vis[p[i]=read()]=true;
        sort(&p[1],&p[K+1],cmp);
        for(int i=K;i>1;--i)p[++K]=LCA(p[i],p[i-1]);
        sort(&p[1],&p[K+1],cmp);K=unique(&p[1],&p[K+1])-p-1;
        for(int i=1,tp=0;i<=K;++i)
        {
            while(tp&&low[S[tp]]<dfn[p[i]])--tp;
		 	Add(S[tp],p[i]);S[++tp]=p[i];
        }
        printf("%d\n",Calc(p[1]));
        for(int i=1;i<=K;++i)h[p[i]]=0,vis[p[i]]=false,f[p[i]]=g[p[i]]=0;
    }
    return 0;
}
