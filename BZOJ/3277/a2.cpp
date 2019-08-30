#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<set>
#include<map>
#include<vector>
#include<queue>
using namespace std;
#define ll long long
#define RG register
#define MAX 220000
struct Line{int v,next;}e[MAX<<1];
int h[MAX<<1],cnt=1, c[MAX << 1], rk[MAX << 1];
inline void Add(int u,int v){e[cnt]=(Line){v,h[u]};h[u]=cnt++;}
struct Node
{
    int son[26];
    int ff,len;
    set<int> d;
}t[MAX<<1];
int size[MAX<<1];
int last,tot;
void init(){last=tot=1;}
void extend(int c,int id)
{
    int p=last,np=++tot;last=np;
    t[np].len=t[p].len+1;
    t[np].d.insert(id);
    while(p&&!t[p].son[c])t[p].son[c]=np,p=t[p].ff;
    if(!p)t[np].ff=1;
    else
    {
        int q=t[p].son[c];
        if(t[q].len==t[p].len+1)t[np].ff=q;
        else
        {
            int nq=++tot;
            t[nq]=t[q];
            t[nq].len=t[p].len+1;
            t[q].ff=t[np].ff=nq;
            while(p&&t[p].son[c]==q)t[p].son[c]=nq,p=t[p].ff;
        }
    }
}
void DFS(int u)
{
    for(int i=h[u];i;i=e[i].next)
    {
        int v=e[i].v;
        DFS(v);
        for(set<int>::iterator it=t[v].d.begin();it!=t[v].d.end();++it)
            t[u].d.insert(*it);
    }
    size[u]=t[u].d.size();
}   
int n,K;
string g[MAX];
int main()
{
    ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
    init();
    cin>>n>>K;
    for(int i=1;i<=n;++i)
    {
        cin>>g[i];
        last=1;
        for(int j=0,l=g[i].length();j<l;++j)extend(g[i][j]-97,i);
    }
 	for(int i=1;i<=tot;++i)if(t[i].ff)Add(t[i].ff,i), ++c[i]; 
	*rk = 0;
	queue <int> q;
	for (int i = 1; i <= tot; ++i) if (!c[i]) q.push(i);
	while (!q.empty()) {
		int u = q.front(); q.pop();
		rk[++*rk] = u;
		for (int i = h[u]; i; i = e[i].next) {
			int v = e[i].v;
			if (--c[v] == 0)
				q.push(v);
		}
	}	
    for (int i = tot; i >= 1; --i) if (t[rk[i]].ff) { 
        for(set<int>::iterator it=t[rk[i]].d.begin();it!=t[rk[i]].d.end();++it)
            t[t[rk[i]].ff].d.insert(*it);
        size[rk[i]] = t[rk[i]].d.size(); 
    }
   // DFS(1);
    if(K>n){for(int i=1;i<=n;++i) cout << 0 << " \n"[i == n]; return 0;}
    for(int i=1;i<=n;++i)
    {
        ll ans=0;
        int now=1,len=g[i].length();
        for(int j=0;j<len;++j)
        {
            now=t[now].son[g[i][j]-97];
            while(size[now]<K)now=t[now].ff;
            ans+=t[now].len;
        }
		cout << ans << " \n"[i == n];
    }
    return 0;
}
