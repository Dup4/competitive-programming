#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pint;
typedef pair<ll,ll> pll;
const int MAXN = 1e5+5;
#define in(a) scanf("%d",&a)
#define inll(a) scanf("%lld",&a)
#define out(a) printf("%d",a)
#define outll(a) printf("%lld",a)
#define outln(a) printf("%d\n",a)
#define outllln(a) printf("%lld\n",a)
#define fin(i,st,n) for(int i=st;i<n;i++)
#define fin2(i,st,n) for(int i=st;i<=n;i++)
#define mk make_pair
#define pb push_back
#define f first
#define s second
#define IOS ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
 
ll n;
 
bool judge(ll m){
    if(m%2==1){
        if(m*(m-1)/2<n)
            return true;
        else return false;
    }
    else{
        if(m*(m-1)/2+(m/2-1)<n)
            return true;
        else return false;
    }
}
 
struct node
{
    int to,next;
}edge[40*MAXN];
int head[40*MAXN];
 
int ans[40*MAXN];
bool visit[40*MAXN]; 
int ansi=1;
 
inline void dfs(int now){
    for(int &i=head[now];i!=-1;i=edge[i].next){
        if(visit[i] == false){
            int v=edge[i].to;
			visit[i] = true;
			visit[i ^ 1] = true;
            dfs(v);
            ans[ansi++]=v; 
        }
    }
}
 
int cnt=0;
void add(int u,int v){
    edge[cnt].to=v;
    edge[cnt].next=head[u];
//	edge[cnt].vis = 0;
    head[u]=cnt;
    cnt++;
    edge[cnt].to=u;
    edge[cnt].next=head[v];
//	edge[cnt].vis = 0;
    head[v]=cnt;
    cnt++;
}
 
void s_olve(ll m){
    for(int i=3;i<=m;i+=2){
        add(i,i+1);
    }
    fin2(i,1,m){
        fin2(j,1,i-1){
            add(i,j);
        }
    }
    dfs(1);
    ans[ansi++]=1;
    return;
}
 
void solve(ll m){
    fin2(i,1,m){
        fin2(j,1,i-1){
            add(i,j);
        }
    }
    dfs(1);
    ans[ansi++]=1;
    return;
}
 
int main(){
    inll(n);
    //
    //m是奇数的话
    //m*(m-1)/2<=n
    //
    //m是偶数的话
    //m*(m-1)/2+m/2-1<=n
    //
    memset(head,-1,sizeof(head));
    ll lb=0,ub=INT_MAX;
    while(ub-lb>1){
        ll mid=(lb+ub)/2;
        if(judge(mid)) lb=mid;
        else ub=mid;
    }
    ll m=lb;
    outllln(m);
    if(n>2*1e6) return 0;
    if(m%2==0) s_olve(m);
    else solve(m);
    fin(i,1,ansi) {
        printf("%d",ans[i]);
        if(i!=n)  printf(" ");
    }
    fin2(i,ansi,n) {
        printf("1");
        if(i!=n) printf(" ");
    }
    printf("\n");
    return 0;
}
