#include<iostream>
#include<algorithm>
#include<set>
#include<vector>
#include<list>
#include<queue>
#include<cmath>
#include<cstring>
#include<sstream>
#include<cstdio>
#include<ctime>
#include<map>
#include<bitset>
#include<stack>
#include<string>
using namespace std;
#define ll long long
#define pii pair<int,int>
constexpr int N = 1e5 + 10;
const int maxn = 1e5 + 10;
ll rd(){
    ll x;
    scanf("%lld",&x);
    return x;
}
int n;
pii a[maxn],b[maxn],c[maxn];
int main(){
    int t=rd();
    while(t--){
        int n=rd();
        for(int i=1;i<=n;i++){
            c[i].first=b[i].first=a[i].first=rd();
        }
        for(int i=1;i<=n;i++){
            c[i].second=b[i].second=a[i].second=rd();
        }
        sort(a+1,a+1+n);
        sort(b+1,b+1+n,[&](const pii x,const pii y){
            return x.second<y.second;
        });
        int x=n,y=n;
        int mina=b[n].first,minb=a[n].second;
        while(x>1&&y>1){
            int cnt=0;
            while(x>1&&a[x-1].first>mina){
                cnt++;
                x--;
                mina=min(mina,a[x].first);
                minb=min(minb,a[x].second);
            }
            while(y>1&&b[y-1].second>minb){
                cnt++;
                y--;
                mina=min(mina,b[y].first);
                minb=min(minb,b[y].second);
            }
            if(!cnt)break;
        }
//        printf("min  a  b %d %d\n",mina,minb);
        for(int i=1;i<=n;i++){
            puts((c[i].first>=mina||c[i].second>=minb)?"YES":"NO");
        }
    }

}