#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<queue>
#include<vector>
#include<algorithm>
using namespace std;
#define INF 1000000000
#define MAX 110000
int root;
struct Node
{
    int ch[2];
    int val;
    int ff;
    int cnt;
    int size;
}t[MAX];
int tot,n,mm,ans,add;
inline void pushup(int x)
{
    t[x].size=t[t[x].ch[0]].size+t[t[x].ch[1]].size+t[x].cnt;
}
inline void rotate(int x)
{
    int y=t[x].ff;
    int z=t[y].ff;
    int k=(x==t[y].ch[1]);
    t[z].ch[y==t[z].ch[1]]=x;
    t[x].ff=z;
    t[y].ch[k]=t[x].ch[k^1];   t[t[x].ch[k^1]].ff=y;
    t[x].ch[k^1]=y;            t[y].ff=x;
    pushup(y);pushup(x);
}
inline void splay(int x,int goal)
{
    while(t[x].ff!=goal)
    {
        int y=t[x].ff;
        int z=t[y].ff;
        if(z!=goal)
            (t[z].ch[0]==y)^(t[y].ch[0]==x)?rotate(x):rotate(y);
        rotate(x);
    }
    if(goal==0)root=x;
}
inline void insert(int x)
{
    int u=root,ff=0;
    while(u&&t[u].val!=x)
    {
        ff=u;
        u=t[u].ch[x>t[u].val];
    }
    if(u)t[u].cnt++;
    else
    {
        u=++tot;
        if(ff)t[ff].ch[x>t[ff].val]=u;
        t[u].ch[0]=t[u].ch[1]=0;
        t[u].val=x;
        t[u].cnt=1;
        t[u].size=1;
        t[u].ff=ff;
    }
    splay(u,0);
}
inline void find(int x)
{
    int u=root;
    if(!u)return;
    while(t[u].ch[x>t[u].val]&&t[u].val!=x)
        u=t[u].ch[x>t[u].val];
    splay(u,0);
}
inline int Next(int x,int f)
{
    find(x);
    int u=root;
    if(t[u].val>=x&&f)return u;
    if(t[u].val<=x&&!f)return u;
    u=t[u].ch[f];
    while(t[u].ch[f^1])u=t[u].ch[f^1];
    return u;
}
inline int kth(int x)
{
    int u=root;
    if(t[u].size<x||x<=0)return -INF;
    while(233)
    {
        int y=t[u].ch[0];
        if(t[y].size+t[u].cnt<x)
        {
            x-=t[y].size+t[u].cnt;
            u=t[u].ch[1];
        }
        else
            if(t[y].size>=x)
                u=y;
            else
                return t[u].val;
    }
}

void Delete(int x) 
{
	int last = Next(x, 0);
	int nx = Next(x, 1);
	splay(last, 0); splay(nx, last); 
	int del = t[nx].ch[0];
	if (t[del].cnt > 1) 
	{
		--t[del].cnt;
		splay(del, 0);
	}
	else
	{
		t[nx].ch[0] = 0;
		//splay(nx, 0);
		pushup(nx); pushup(last);
	}
}
int main()
{
	//insert(-INF); 
    insert(+INF);
    scanf("%d%d",&n,&mm);
    int peo=0;
    while(n--)
    {
        int x;char ch[3];
        scanf("%s%d",ch,&x);
        if(ch[0]=='I')
        {
            if(x<mm);
            else
            {
                insert(x-add);
                peo++;
            }
        }
        if(ch[0]=='A')
            add+=x;
        if(ch[0]=='S')
        {
            add-=x;
			/*
			while (peo >= 1 && kth(2) < mm - add)  
			{
				Delete(kth(2)), ++ans, --peo;
			}
			*/
				
            int gg=Next(mm-add,1);
            splay(gg,0);
            ans+=t[t[root].ch[0]].size;
            peo-=t[t[root].ch[0]].size;
            t[t[root].ch[0]].size=t[t[root].ch[0]].cnt=0;
            t[root].ch[0]=0;t[0].size=0;
            pushup(root);
			
        }
        if(ch[0]=='F')
        {
			//peo = t[root].size - 1;
        	int gg=kth(peo-x+1);
            printf("%d\n",gg==-INF?-1:(gg+add));
    	}
	}
    printf("%d\n",ans);
    return 0;
}
