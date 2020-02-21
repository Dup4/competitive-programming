#include <bits/stdc++.h>
using namespace std;
int main(){
    int T;
    cin>>T;
    for(int kase=1;kase<=T;kase++){
        int n;
        scanf("%d",&n);
        printf("Case #%d: %d\n",kase,n/2);
        if(n%2==0){
            for(int i=1;i<=n/2;i++){
                printf("%d %d\n",i,i+1);
                for(int j=1;j<=n/2-1;j++){
                    int u=i+j;
                    int v=(u+n-j*2-1)%n+1;
                    printf("%d %d\n",u,v);
                    printf("%d %d\n",v,u+1);
                }
            }
        }
        else{
            n--;
            for(int i=1;i<=n/2;i++){
                printf("%d %d\n",i,i+1);
                for(int j=1;j<=n/2-1;j++){
                    int u=i+j;
                    int v=(u+n-j*2-1)%n+1;
                    printf("%d %d\n",u,v);
                    printf("%d %d\n",v,u+1);
                }
                printf("%d %d\n",i,n+1);
            }
        }
    }
}
