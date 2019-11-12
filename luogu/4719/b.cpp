#include<iostream>
#include<cstdio>
using namespace std;
#define ll long long
#define MAX 100100
#define lson (now<<1)
#define rson (now<<1|1)
const ll inf=1e17;
inline int read()
{
    int x=0;bool t=false;char ch=getchar();
    while((ch<'0'||ch>'9')&&ch!='-')ch=getchar();
    if(ch=='-')t=true,ch=getchar();
    while(ch<='9'&&ch>='0')x=x*10+ch-48,ch=getchar();
    return t?-x:x;
}
struct Line{int v,next;}e[MAX<<1];
int h[MAX],cnt=1;
inline void Add(int u,int v){e[cnt]=(Line){v,h[u]};h[u]=cnt++;}
int n,Q,V[MAX];
int fa[MAX],top[MAX],bot[MAX],size[MAX],hson[MAX],dfn[MAX],tim,ln[MAX];
void dfs1(int u,int ff)
{
    fa[u]=ff;size[u]=1;
    for(int i=h[u];i;i=e[i].next)
    {
        int v=e[i].v;if(v==ff)continue;
        dfs1(v,u);size[u]+=size[v];
        if(size[v]>size[hson[u]])hson[u]=v;
    }
}
void dfs2(int u,int tp)
{
    top[u]=tp;dfn[u]=++tim,ln[tim]=u;
    if(hson[u])dfs2(hson[u],tp),bot[u]=bot[hson[u]];
    else bot[u]=u;
    for(int i=h[u];i;i=e[i].next)
        if(e[i].v!=fa[u]&&e[i].v!=hson[u])
            dfs2(e[i].v,e[i].v);
}
ll f[MAX][2];
void dfs(int u,int ff)
{
    f[u][0]=0;f[u][1]=V[u];
    for(int i=h[u];i;i=e[i].next)
    {
        int v=e[i].v;if(v==ff)continue;
        dfs(v,u);
        f[u][0]+=max(f[v][0],f[v][1]);
        f[u][1]+=f[v][0];
    }
}
struct Matrix
{
    ll a[2][2];
    ll*operator[](int x){return a[x];}
}t[MAX<<2],tmp[MAX];
Matrix operator*(Matrix a,Matrix b)
{
    Matrix c;
    c[0][0]=max(a[0][0]+b[0][0],a[0][1]+b[1][0]);
    c[0][1]=max(a[0][0]+b[0][1],a[0][1]+b[1][1]);
    c[1][0]=max(a[1][0]+b[0][0],a[1][1]+b[1][0]);
    c[1][1]=max(a[1][0]+b[0][1],a[1][1]+b[1][1]);
    return c;
}
void Build(int now,int l,int r)
{
    if(l==r)
    {
        int u=ln[l];ll g0=0,g1=V[u];
        for(int i=h[u];i;i=e[i].next)
            if(e[i].v!=fa[u]&&e[i].v!=hson[u])
                g0+=max(f[e[i].v][0],f[e[i].v][1]),g1+=f[e[i].v][0];
        tmp[l]=t[now]=(Matrix){g0,g0,g1,-inf};
        return;
    }
    int mid=(l+r)>>1;
    Build(lson,l,mid);Build(rson,mid+1,r);
    t[now]=t[lson]*t[rson];
}
void Modify(int now,int l,int r,int p)
{
    if(l==r){t[now]=tmp[l];return;}
    int mid=(l+r)>>1;
    if(p<=mid)Modify(lson,l,mid,p);
    else Modify(rson,mid+1,r,p);
    t[now]=t[lson]*t[rson];
}
Matrix Query(int now,int l,int r,int L,int R)
{
    if(L==l&&r==R)return t[now];
    int mid=(l+r)>>1;
    if(R<=mid)return Query(lson,l,mid,L,R);
    if(L>mid)return Query(rson,mid+1,r,L,R);
    return Query(lson,l,mid,L,mid)*Query(rson,mid+1,r,mid+1,R);
}
void Modify(int u,int w)
{
    tmp[dfn[u]][1][0]+=w-V[u];V[u]=w;
    while(u)
    {
        Matrix a=Query(1,1,n,dfn[top[u]],dfn[bot[u]]);
        Modify(1,1,n,dfn[u]);
        Matrix b=Query(1,1,n,dfn[top[u]],dfn[bot[u]]);
        u=fa[top[u]];if(!u)break;int x=dfn[u];
        ll g0=a[0][0],g1=a[1][0],f0=b[0][0],f1=b[1][0];
        tmp[x][0][0]=tmp[x][0][1]=tmp[x][0][0]+max(f0,f1)-max(g0,g1);
        tmp[x][1][0]=tmp[x][1][0]+f0-g0;
    }
}
int main()
{
    n=read();Q=read();
    for(int i=1;i<=n;++i)V[i]=read();
    for(int i=1,u,v;i<n;++i)u=read(),v=read(),Add(u,v),Add(v,u);
    dfs1(1,0);dfs2(1,1);dfs(1,0);Build(1,1,n);
    while(Q--)
    {
        int x=read(),w=read();Modify(x,w);
        Matrix ans=Query(1,1,n,dfn[1],dfn[bot[1]]);
        printf("%lld\n",max(ans[0][0],ans[1][0]));
    }
    return 0;
}
