#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#include<cmath>
#define INF 0x3f3f3f3f
#define maxv 505
#define maxe 1505
#define maxlogv 10 
using namespace std;
#define dbg(x...) do { cout << "\033[32;1m" << #x << " -> "; err(x); } while (0) 
void err() { cout << "\033[39;0m" << endl; } 
template <class T, class... Ts> void err(const T& arg, const Ts&... args) { cout << arg << ' '; err(args...); }
int n,m,q;
namespace network_flow{ 
    struct edge{
        int from;
        int to;
        int next;
        int flow;
    }E[maxe<<2];
    int head[maxv];
    int deep[maxv];
    int sz=1;
    void add_edge(int u,int v,int w){
        sz++;
        E[sz].from=u;
        E[sz].to=v;
        E[sz].next=head[u];
        E[sz].flow=w;
        head[u]=sz;
        sz++;
        E[sz].from=v;
        E[sz].to=u;
        E[sz].next=head[v];
        E[sz].flow=0;
        head[v]=sz;
    }
    bool bfs(int s,int t){
        memset(deep,0,sizeof(deep));
        deep[s]=1;
        queue<int>q;
        q.push(s);
        while(!q.empty()){
            int x=q.front();
            q.pop();
            for(int i=head[x];i;i=E[i].next){
                int y=E[i].to;
                if(!deep[y]&&E[i].flow){
                    deep[y]=deep[x]+1;
                    q.push(y);
                }
            }
        }
        return deep[t]!=0;
    }
    int dfs(int x,int t,int minf){
        if(x==t) return minf;
        int k,rest=minf;
        for(int i=head[x];i;i=E[i].next){
            int y=E[i].to;
            if(deep[y]==deep[x]+1&&E[i].flow){
                k=dfs(y,t,min(rest,E[i].flow));
                rest-=k;
                E[i].flow-=k;
                E[i^1].flow+=k;
                if(k==0) deep[y]=0;
                if(rest==0) break;
            }
        } 
        return minf-rest;
    }
    void init(){
        for(int i=2;i<=sz;i+=2){
            E[i].flow=(E[i].flow+E[i^1].flow);
            E[i^1].flow=0;
        }
    }
    int dinic(int s,int t){
        init();
        int ans=0,now=0;
        while(bfs(s,t)){
            while(now=dfs(s,t,INF)) ans+=now;
        }
        return ans;
    }

} 

namespace mincut_tree{
    struct edge{
        int from;
        int to;
        int next;
        int len;
    }E[maxv<<1];
    int head[maxv];
    int sz=1;
    void add_edge(int u,int v,int w){
//      printf("tree: %d->%d len=%d\n",u,v,w);
        sz++;
        E[sz].from=u;
        E[sz].to=v;
        E[sz].next=head[u];
        E[sz].len=w;
        head[u]=sz;
        sz++;
        E[sz].from=v;
        E[sz].to=u;
        E[sz].next=head[v];
        E[sz].len=w;
        head[v]=sz;
    }
    
    int node[maxv];
    int tmp1[maxv],tmp2[maxv];
    void build(int l,int r){
        if(l==r) return;
        int s=node[l],t=node[l+1];
        int cut=network_flow::dinic(s,t);
		dbg(s, t, cut);
        add_edge(s,t,cut);
        int cnt1=0,cnt2=0;
        for(int i=l;i<=r;i++){
            if(network_flow::deep[node[i]]) tmp1[++cnt1]=node[i];
            else tmp2[++cnt2]=node[i];
        }
        for(int i=l;i<=l+cnt1-1;i++) node[i]=tmp1[i-l+1];
        for(int i=l+cnt1;i<=r;i++) node[i]=tmp2[i-cnt1-l+1];
        build(l,l+cnt1-1);
        build(l+cnt1,r);
    }
    
    int log2n;
    int deep[maxv];
    int anc[maxv][maxlogv];
    int minl[maxv][maxlogv];
    void dfs(int x,int fa){
        deep[x]=deep[fa]+1;
        for(int i=1;i<=log2n;i++){
            anc[x][i]=anc[anc[x][i-1]][i-1];
            minl[x][i]=min(minl[x][i-1],minl[anc[x][i-1]][i-1]);
        }
        for(int i=head[x];i;i=E[i].next){
            int y=E[i].to;
            if(y!=fa){
                anc[y][0]=x;
                minl[y][0]=E[i].len;
                dfs(y,x);
            }
        }
    }
    
    void work(){
        log2n=log2(n)+1;
        for(int i=1;i<=n;i++) node[i]=i;
        build(1,n);
        dfs(1,0);
    }
    
    int query(int x,int y){
        int ans=INF;
        if(deep[x]<deep[y]) swap(x,y);
        for(int i=log2n;i>=0;i--){
            if(deep[anc[x][i]]>=deep[y]){
                ans=min(ans,minl[x][i]);
                x=anc[x][i];
            }
        }
        if(x==y) return ans;
        for(int i=log2n;i>=0;i--){
            if(anc[x][i]!=anc[y][i]){
                ans=min(ans,minl[x][i]);
                ans=min(ans,minl[y][i]);
                x=anc[x][i];
                y=anc[y][i];
            }
        }
        ans=min(ans,minl[x][0]);
        ans=min(ans,minl[y][0]);
        return ans;
    }
}

int main(){
    int u,v,w;
    scanf("%d %d",&n,&m);
    for(int i=1;i<=m;i++){
        scanf("%d %d %d",&u,&v,&w);
        network_flow::add_edge(u,v,w); 
        network_flow::add_edge(v,u,w);
    }
    mincut_tree::work();
    scanf("%d",&q);
    for(int i=1;i<=q;i++){
        scanf("%d %d",&u,&v);
        int ans=mincut_tree::query(u,v);
        if(ans==INF) ans=-1;
        printf("%d\n",ans);
    }
}
