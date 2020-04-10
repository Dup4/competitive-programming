#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1e5+5;
struct node
{
    int t,p,w;
    bool operator<(const node&o)const
    {
        return t<o.t;
    }
}a[N];
int n,m,num,pos[N],b[N];
int len1,len2,len,hs1[N],hs2[N],hs[N],rt1[N],rt2[N],ls[N*200],rs[N*200];
ll dp[N],t[N*200];
ll query(int l,int r,int x,int now)
{
    if(l>x||!now) return 0;
    if(r<=x) return t[now];
    int m=l+r>>1;
    return max(query(l,m,x,ls[now]),query(m+1,r,x,rs[now]));
}
void fix(int l,int r,int x,ll v,int &now)
{
    if(!now) now=++num;
    t[now]=max(t[now],v);
    if(l==r) return;
    int m=l+r>>1;
    if(x<=m) fix(l,m,x,v,ls[now]);
    else fix(m+1,r,x,v,rs[now]);
}
ll query1(int x,int p)
{
    ll ans=0;
    while(x)
    {
        ans=max(ans,query(1,len1,p,rt1[x]));
        x-=x&-x;
    }
    return ans;
}
ll query2(int x,int p)
{
    x=len-x+1;
    ll ans=0;
    while(x)
    {
        ans=max(ans,query(1,len2,p,rt2[x]));
        x-=x&-x;
    }
    return ans;
}
void add1(int x,int p,ll v)
{
    while(x<=len)
    {
        fix(1,len1,p,v,rt1[x]);
        x+=x&-x;
    }
}
void add2(int x,int p,ll v)
{
    x=len-x+1;
    while(x<=len)
    {
        fix(1,len2,p,v,rt2[x]);
        x+=x&-x;
    }
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++) scanf("%d",&pos[i]),hs[i]=pos[i];
    for(int i=1;i<=m;i++) scanf("%d",&b[i]);
    for(int i=1;i<=n;i++)
        scanf("%d%d%d",&a[i].t,&a[i].p,&a[i].w),a[i].t+=b[a[i].p];
    sort(a+1,a+1+n);
    for(int i=1;i<=n;i++)
    {
        hs1[i]=a[i].t-pos[a[i].p];
        hs2[i]=a[i].t+pos[a[i].p];
    }
    sort(hs1+1,hs1+1+n);
    sort(hs2+1,hs2+1+n);
    sort(hs+1,hs+1+n);
    len1=unique(hs1+1,hs1+1+n)-hs1-1;
    len2=unique(hs2+1,hs2+1+n)-hs2-1;
    len=unique(hs+1,hs+1+n)-hs-1;
    for(int i=1;i<=n;i++)
    {
        dp[i]=a[i].w;
        int s=upper_bound(hs1+1,hs1+1+len1,a[i].t-pos[a[i].p])-hs1-1;
        int p=lower_bound(hs+1,hs+1+len,pos[a[i].p])-hs;
        dp[i]=max(dp[i],query1(p,s)+a[i].w);
        s=upper_bound(hs2+1,hs2+1+len2,a[i].t+pos[a[i].p])-hs2-1;
        dp[i]=max(dp[i],query2(p,s)+a[i].w);
        s=lower_bound(hs1+1,hs1+1+len1,a[i].t-pos[a[i].p])-hs1;
        add1(p,s,dp[i]);
        s=lower_bound(hs2+1,hs2+1+len2,a[i].t+pos[a[i].p])-hs2;
        add2(p,s,dp[i]);
    }
    ll ans=0;
    for(int i=1;i<=n;i++)
        ans=max(ans,dp[i]);
    printf("%lld\n",ans);
}
