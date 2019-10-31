#include <bits/stdc++.h>
using namespace std;
const long long INF=0x3f3f3f3f3f3f;
int n,m;
long long s[105][105],ss[105][105];
void floyd(){
    long long i,j,k,ans;
    ans=INF;
    for(i=1;i<=n;i++){
        for(j=1;j<=n;j++){
            for(k=1;k<=n;k++){
                if(j!=i&&k!=i&&j!=k)
                ans=min(ans,s[j][k]+ss[j][i]+ss[i][k]);
            }                                   //没更新前的s[j][k]一定是不经过i点的
        }                                       //所以这时再加上i点，满足是至少三个点
        for(j=1;j<=n;j++)                       //的环，求出最小值
        for(k=1;k<=n;k++)
        s[j][k]=min(s[j][k],s[j][i]+s[i][k]);
    }
    if(ans==INF)
    puts("It's impossible.");
    else
    printf("%lld\n",ans);
}
int main(){
    int i,j,u,v,w;
    while(scanf("%d%d",&n,&m)!=EOF){
        for(i=1;i<=n;i++)
        for(j=1;j<=n;j++)
        s[i][j]=ss[i][j]=INF;
        for(i=0;i<m;i++){
            scanf("%d%d%d",&u,&v,&w);
            s[u][v]=min(s[u][v],1ll * w);
            s[v][u]=s[u][v];
            ss[u][v]=ss[v][u]=s[u][v];
        }
        floyd();
    }
    return 0;
}
