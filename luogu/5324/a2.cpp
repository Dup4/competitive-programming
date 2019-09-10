#include<iostream>
#include<cstdio>
using namespace std;
#define MAX 150150
#define lson (now<<1)
#define rson (now<<1|1)
inline int read()
{
    int x=0;bool t=false;char ch=getchar();
    while((ch<'0'||ch>'9')&&ch!='-')ch=getchar();
    if(ch=='-')t=true,ch=getchar();
    while(ch<='9'&&ch>='0')x=x*10+ch-48,ch=getchar();
    return t?-x:x;
}
int n,m,a[MAX];
int t[MAX<<4],cnt[MAX<<4],mn[MAX<<4],tag[MAX<<4],ans[MAX<<4];
void pushup(int now)
{
    mn[now]=min(mn[lson],mn[rson]);
    cnt[now]=(mn[now]==mn[lson]?cnt[lson]:0)+(mn[now]==mn[rson]?cnt[rson]:0);
    ans[now]=ans[lson]+ans[rson];
}
void puttag(int now,int w)
{
    mn[now]+=w;tag[now]+=w;ans[now]=(mn[now]==0?cnt[now]:0);
}
void pushdown(int now)
{
    if(!tag[now])return;
    puttag(lson,tag[now]);
    puttag(rson,tag[now]);
    tag[now]=0;
}
void Build(int now,int l,int r)
{
    if(l==r){cnt[now]=ans[now]=1;return;}
    int mid=(l+r)>>1;
    Build(lson,l,mid);Build(rson,mid+1,r);
    pushup(now);
}
void Modify(int now,int l,int r,int L,int R,int w)
{
    if(L<=l&&r<=R){puttag(now,w);return;}
    int mid=(l+r)>>1;pushdown(now);
    if(L<=mid)Modify(lson,l,mid,L,R,w);
    if(R>mid)Modify(rson,mid+1,r,L,R,w);
    pushup(now);
}
int Query(int now,int l,int r,int L,int R)
{
    if(L<=l&&r<=R)return ans[now];
    int mid=(l+r)>>1,ret=0;pushdown(now);
    if(L<=mid)ret+=Query(lson,l,mid,L,R);
    if(R>mid)ret+=Query(rson,mid+1,r,L,R);
    return ret;
}
int py,N,num[MAX<<4],L;
void Modify(int x,int w)
{
    int k=num[py+x]+(w>0);num[py+x]+=w;
    if(x<=n)Modify(1,1,N,py+x-k+1,py+x-k+1,w);
}
int main()
{
    n=read();m=read();N=(n+m)*2+1;py=n+m;Build(1,1,N);
    for(int i=1;i<=n;++i)Modify(a[i]=read(),1);
    while(m--)
    {
        int p=read(),x=read();
        if(p>0)Modify(a[p]+L,-1),a[p]=x-L,Modify(a[p]+L,1);
        else if(x>0)
        {
            --py;++L;int pos=py+n+1;
            if(num[pos]>0)Modify(1,1,N,pos-num[pos]+1,pos,-1);
        }
        else
        {
            int pos=py+n+1;++py;--L;
            if(num[pos]>0)Modify(1,1,N,pos-num[pos]+1,pos,1);
        }
        printf("%d\n",Query(1,1,N,py+1,py+n));
    }
    return 0;
}
