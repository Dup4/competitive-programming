#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<vector>
using namespace std;
#define ll long long
#define MAX 1001000
inline int read()
{
    int x=0;bool t=false;char ch=getchar();
    while((ch<'0'||ch>'9')&&ch!='-')ch=getchar();
    if(ch=='-')t=true,ch=getchar();
    while(ch<='9'&&ch>='0')x=x*10+ch-48,ch=getchar();
    return t?-x:x;
}
char S[MAX],T[MAX];
int n,Q,rt[MAX];
namespace SegmentTree
{
    struct Node{int ls,rs;}t[MAX*60];int tot;
    void Modify(int &x,int l,int r,int p)
    {
        if(!x)x=++tot;if(l==r)return;
        int mid=(l+r)>>1;
        if(p<=mid)Modify(t[x].ls,l,mid,p);
        else Modify(t[x].rs,mid+1,r,p);
    }
    int Merge(int x,int y)
    {
        if(!x||!y)return x|y;
        int z=++tot;
        t[z].ls=Merge(t[x].ls,t[y].ls);
        t[z].rs=Merge(t[x].rs,t[y].rs);
        return z;
    }
    bool Query(int x,int l,int r,int L,int R)
    {
        if(!x)return false;if(L<=l&&r<=R)return true;
        int mid=(l+r)>>1;
        if(L<=mid&&Query(t[x].ls,l,mid,L,R))return true;
        if(R>mid&&Query(t[x].rs,mid+1,r,L,R))return true;
        return false;
    }
}
namespace SAM
{
    struct Node{int son[26],ff,len;}t[MAX];
    int last=1,tot=1;
    void extend(int c,int pos)
    {
        int p=last,np=++tot;last=tot;
        t[np].len=t[p].len+1;
        while(p&&!t[p].son[c])t[p].son[c]=np,p=t[p].ff;
        if(!p)t[np].ff=1;
        else
        {
            int q=t[p].son[c];
            if(t[q].len==t[p].len+1)t[np].ff=q;
            else
            {
                int nq=++tot;
                t[nq]=t[q];t[nq].len=t[p].len+1;
                t[q].ff=t[np].ff=nq;
                while(p&&t[p].son[c]==q)t[p].son[c]=nq,p=t[p].ff;
            }
        }
        SegmentTree::Modify(rt[last],1,n,pos);
    }
    vector<int> E[MAX];
    void dfs(int u)
    {
        for(int i=0,l=E[u].size();i<l;++i)
            dfs(E[u][i]),rt[u]=SegmentTree::Merge(rt[u],rt[E[u][i]]);
    }
    void pre()
    {
        for(int i=1;i<=tot;++i)E[t[i].ff].push_back(i);
        dfs(1);
    }
}
using namespace SAM;
int Check(int u,int len,int l,int r,int c)
{
    if(l+len>r)return false;
    if(!t[u].son[c])return false;
    u=t[u].son[c];
    return SegmentTree::Query(rt[u],1,n,l+len,r);
}
namespace SAMT
{
    struct Node{int son[26],ff,len;}t[MAX];
    int last=1,tot=1,Len[MAX];
    void extend(int c,int len)
    {
        int p=last,np=++tot;last=tot;
        t[np].len=t[p].len+1;
        while(p&&!t[p].son[c])t[p].son[c]=np,p=t[p].ff;
        if(!p)t[np].ff=1;
        else
        {
            int q=t[p].son[c];
            if(t[q].len==t[p].len+1)t[np].ff=q;
            else
            {
                int nq=++tot;Len[nq]=Len[q];
                t[nq]=t[q];t[nq].len=t[p].len+1;
                t[q].ff=t[np].ff=nq;
                while(p&&t[p].son[c]==q)t[p].son[c]=nq,p=t[p].ff;
            }
        }
        Len[last]=len;
    }
    void clear()
    {
        for(int i=1;i<=tot;++i)
            for(int j=0;j<26;++j)t[i].son[j]=0;
        for(int i=1;i<=tot;++i)Len[i]=0,t[i].len=t[i].ff=0;
        last=tot=1;
    }
    void calc()
    {
        ll ans=0;
        for(int i=2;i<=tot;++i)ans+=max(0,t[i].len-max(t[t[i].ff].len,Len[i]));
        printf("%lld\n",ans);
    }
}
int main()
{
    scanf("%s",S+1);n=strlen(S+1);
    for(int i=1;i<=n;++i)extend(S[i]-97,i);
    pre();Q=read();
    while(Q--)
    {
        scanf("%s",T+1);int m=strlen(T+1),l=read(),r=read();
        for(int i=1,p=1,len=0;i<=m;++i)
        {
            int c=T[i]-97;
            while(p&&!Check(p,len,l,r,c))
                if(--len<=t[t[p].ff].len)p=t[p].ff;
            if(!p)p=1,len=0;
            else p=t[p].son[c],len+=1;
            SAMT::extend(c,len);
        }
        SAMT::calc();SAMT::clear();
    }
    return 0;
}
