#include<iostream>
#include<cstring>
#include<cstdio>
#include<stack>
#include<vector>
#define maxn 200005
using namespace std;
inline void read(int &x){
    x=0;int f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    x*=f;
}
int N,M,Q;
struct node{
    int nex,from,to;
}edge[maxn<<2][2];
int head[maxn][2],tot[2];
inline void insert(int from,int to,int ty){
    edge[++tot[ty]][ty].nex=head[from][ty];
    head[from][ty]=tot[ty];
    edge[tot[ty]][ty].from=from;
    edge[tot[ty]][ty].to=to;
}
int dfn[maxn],low[maxn],id,belong[maxn],cnt;
stack<int>sta;
bool cut[maxn];
vector<int> q[maxn];
void tarjan(int x){
    int flag=0;
    dfn[x]=low[x]=++id;
    sta.push(x);
    for(int i=head[x][0];i;i=edge[i][0].nex){
        int y=edge[i][0].to;
        if(!dfn[y]){
            tarjan(y);
            low[x]=min(low[x],low[y]);
            if(dfn[x]<=low[y]){
                int u;++cnt;++flag;
                if(flag>1||x!=1)
                    cut[x]=1;
                do{
                    u=sta.top();//cout<<"out: "<<u<<" "<<x<<endl;
                    sta.pop();
                    q[cnt].push_back(u);
                }while(u!=y);
                q[cnt].push_back(x);
            }
        }else
            low[x]=min(low[x],dfn[y]);
    }
}
int anc[maxn][20],dept[maxn];
void dfs1(int x,int u){
    anc[x][0]=u;
    dept[x]=dept[u]+1;
    for(int i=head[x][1];i;i=edge[i][1].nex)
        if(edge[i][1].to^u)
            dfs1(edge[i][1].to,x);
}
int num;
void init(){
    for(int i=1;i<=18;i++)
        for(int a=1;a<=num;a++)
            anc[a][i]=anc[anc[a][i-1]][i-1];
}
int lca(int u,int v){
    if(dept[u]<dept[v])
        swap(u,v);
    for(int i=18;i>=0;i--)
        if(dept[anc[u][i]]>=dept[v]){
            //cout<<u<<" "<<i<<" ";
            u=anc[u][i];
        }
            
    //cout<<u<<" "<<v<<endl;
    if(u==v)    
        return u;
    for(int i=18;i>=0;i--)
        if(anc[u][i]!=anc[v][i]){
            u=anc[u][i];
            v=anc[v][i];
        }
    return anc[u][0];
}
int sum[maxn];
void suodian(){
    int u,v;
    num=cnt;
    for(int i=1;i<=N;i++)
        if(cut[i])
            belong[i]=++num;
    for(int x=1;x<=cnt;x++){
        for(int j=0;j<q[x].size();j++){
            int y=q[x][j];
            if(cut[y]){
                insert(x,belong[y],1);
                insert(belong[y],x,1);
            }else
                belong[y]=x;
        }
    }
}
int dfs(int x,int u){
    //cout<<x<<" ";
    for(int i=head[x][1];i;i=edge[i][1].nex)
        if(edge[i][1].to^u){
            dfs(edge[i][1].to,x);
            sum[x]+=sum[edge[i][1].to];
        }    
}
int final[maxn];
int main(){
    //freopen("1.in","r",stdin);
    //freopen("1.ans","w",stdout);
    read(N);read(M);read(Q);
    int u,v;
    for(int i=1;i<=M;i++){
        read(u);read(v);
        insert(u,v,0);
        insert(v,u,0);
    }
    tarjan(1);
	for (int i = 1; i <= N; ++i) if (dfn[i] == 0)
		cout << i << endl;
    suodian();
    dfs1(1,0);
    init();
    //for(int i=1;i<=20;i++)
        //cout<<anc[90623][i]<<" ";
    while(Q--){
        read(u);read(v);
        final[u]++;final[v]++;
        u=belong[u];v=belong[v];
        sum[u]++;sum[v]++;
        int ancs=lca(u,v);
        //cout<<"lca: "<<u<<" "<<v<<" "<<ancs<<endl;
        sum[ancs]--;
        if(ancs!=1)
            sum[anc[ancs][0]]--;
    }
    
    dfs(1,1);
   // for(int i=1;i<=N;i++)
   //     if(!cut[i])
   //         printf("%d\n",final[i]);
   //     else
   //         printf("%d\n",sum[belong[i]]);
}
