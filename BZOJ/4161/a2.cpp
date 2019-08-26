#include<bits/stdc++.h>
using namespace std;
const int maxn=4000,mod=1000000007;
int a[maxn+5],p[maxn+5],ans[maxn+5],num[maxn+5];
int h[maxn+5],tmp[maxn+5];
int n,k;
void mul(int *a,int *b,int *ans)
{
    for(int i=0;i<=2*k;++i) tmp[i]=0;
    for(int i=0;i<k;++i)
        for(int j=0;j<k;++j)
            tmp[i+j]=(tmp[i+j]+1LL*a[i]*b[j])%mod;
    for(int i=2*k-2;i>=k;--i)
    {
        for(int j=k-1;j>=0;--j)
            tmp[i-k+j]=(tmp[i-k+j]-1LL*tmp[i]*p[j])%mod,tmp[i-k+j]=(tmp[i-k+j]+mod)%mod;
        tmp[i]=0;
    }
    for(int i=0;i<k;++i) ans[i]=tmp[i];
}
int main()
{
    scanf("%d%d",&n,&k);
    for(int i=1;i<=k;++i) scanf("%d",&a[i]);
    for(int i=0;i<k;++i) scanf("%d",&h[i]);
    p[k]=1;
    for(int i=1;i<=k;++i) p[k-i]=mod-a[i];
    for(int i=k;i<2*k;++i)
        for(int j=1;j<=k;++j)
        {
            h[i]=h[i]+1LL*h[i-j]*a[j]%mod;
            h[i]%=mod;
        }
    if(n<2*k) return 0*printf("%d\n",h[n]);
    int b=n-k+1;
    num[1]=1,ans[0]=1;
    while(b)
    {
        if(b&1) mul(ans,num,ans);
        mul(num,num,num);
        b>>=1;
    }
    long long res=0;
    for(int i=0;i<k;++i) res=(res+1LL*ans[i]*h[i+k-1])%mod;
    printf("%lld\n",(res+mod)%mod);
    return 0;
}
