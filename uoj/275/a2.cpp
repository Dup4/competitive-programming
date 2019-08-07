#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
#define MOD 1000000007
void add(int &x,int y){x+=y;if(x>=MOD)x-=MOD;}
long long n,m;int T,K,f[65][2][2],sn[65],tn,sm[65],tm,ans;
int main()
{
    cin>>T>>K;
    while(T--)
    {
        cin>>n>>m;m=min(n,m);tn=tm=0;
        ans=(((1+m)%MOD)*(m%MOD)%MOD*500000004%MOD+((n-m+1)%MOD)*((m+1)%MOD)%MOD)%MOD;
        for(;n;n/=K,m/=K)sn[++tn]=n%K,sm[++tm]=m%K;
        memset(f,0,sizeof(f));f[tn+1][1][1]=1;
		cout << ans << endl;
        for(int i=tn;i;--i)
            for(int j=0;j<2;++j)
                for(int k=0;k<2;++k)
                    if(f[i+1][j][k])
                        for(int x=0;x<=(j?sn[i]:K-1);++x)
                            for(int y=0;y<=(k?sm[i]:K-1)&&y<=x;++y)
                                add(f[i][j&(x==sn[i])][k&(y==sm[i])],f[i+1][j][k]);
        for(int i=0;i<2;++i)
            for(int j=0;j<2;++j)
                add(ans,MOD-f[1][i][j]);
        printf("%d\n",ans);
    }
    return 0;
}
