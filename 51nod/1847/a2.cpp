#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;
#define uint unsigned int
#define MAX 100000
uint n,blk;int k;
bool zs[MAX];
int pri[MAX],tot;
uint prik[MAX],sprik[MAX];
uint w[MAX],g[MAX],h[MAX],f[MAX];
int id1[MAX],id2[MAX],m;
uint S[60][60];
int getid(uint x){return (x<=blk)?id1[x]:id2[n/x];}
uint fpow(uint a,int b)
{
    uint s=1;
    while(b){if(b&1)s*=a;a*=a;b>>=1;}
    return s;
}
void pre(int n)
{
    for(int i=2;i<=n;++i)
    {
        if(!zs[i])pri[++tot]=i,prik[tot]=fpow(i,k);
        for(int j=1;j<=tot&&i*pri[j]<=n;++j)
        {
            zs[i*pri[j]]=true;
            if(i%pri[j]==0)break;
        }
    }
    for(int i=1;i<=tot;++i)sprik[i]=sprik[i-1]+prik[i];
}
uint Sumk(int n)
{
    uint ret=0;
    for(int i=1;i<=k;++i)
    {
        uint s=1;
        for(int j=0;j<=i;++j)
            if((n+1-j)%(i+1))s*=n+1-j;
            else s*=(n+1-j)/(i+1);
        ret+=S[k][i]*s;
    }
    return ret;
}
bool vis[MAX];
uint M[MAX];
uint Solve(uint n)
{
    if(vis[getid(n)])return M[getid(n)];
    uint ret=f[getid(n)];
    for(uint i=2,j;i<=n;i=j+1)
        j=n/(n/i),ret-=(j-i+1)*Solve(n/i);
    vis[getid(n)]=true;return M[getid(n)]=ret;
}
int main()
{
    scanf("%u%d",&n,&k);pre(blk=sqrt(n));S[0][0]=1;
    for(int i=1;i<=k;++i)
        for(int j=1;j<=i;++j)
            S[i][j]=S[i-1][j-1]+j*S[i-1][j];
    for(uint i=1,j;i<=n;i=j+1)
    {
        j=n/(n/i);w[++m]=n/i;
        g[m]=w[m]-1;h[m]=Sumk(w[m])-1;
        if(w[m]<=blk)id1[w[m]]=m;
        else id2[n/w[m]]=m;
    }
    for(int j=1;j<=tot;++j)
        for(int i=1;i<=m&&1u*pri[j]*pri[j]<=w[i];++i)
        {
            int k=getid(w[i]/pri[j]);
            g[i]-=g[k]-(j-1);
            h[i]-=prik[j]*(h[k]-sprik[j-1]);
            f[i]+=h[k]-sprik[j-1];
        }
    for(int i=1;i<=m;++i)f[i]+=g[i];
    uint ans=0;
    for(uint i=1,j,lt=0,nw;i<=n;i=j+1)
    {
        j=n/(n/i);uint s=n/i;s*=s;
        nw=Solve(j);ans+=s*(nw-lt);lt=nw;
    }
    printf("%u\n",ans);
    return 0;
}
