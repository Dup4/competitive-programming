#include<stdio.h>
struct edge
{
    int u,v,tim;
    int cnt,ans,c[6];
}ed[200010],q[200010];

int stk1[5000010],stk2[5000010],fa[200010];
int n,m,T,top,tim;

int getfather(int x)
{
    if(fa[x]==x) return x;
    int y=getfather(fa[x]);
    if(fa[x]!=y) stk1[++top]=x,stk2[top]=fa[x]; //如果路径压缩后x的fa会改变，就将其压入栈中0 
    return fa[x]=y; //路径压缩 
}

void CDQ(int lf,int rg)
{
    int TOP=top; //保留当前栈顶 
    if(lf==rg)
    {
        q[lf].ans=1;
        for(int i=1;i<=q[lf].cnt;i++)  //判断这一个询问所有被卡断的边的两边的点是不是在一个并查集里 
            q[lf].ans*= (getfather(ed[q[lf].c[i]].u)==getfather(ed[q[lf].c[i]].v)) ;
        while(top!=TOP) fa[stk1[top]]=stk2[top],top--; //撤销并查集路径压缩 
        return ;
    }
    int mid=(lf+rg)>>1;tim++;
    for(int i=lf;i<=mid;i++)
        for(int j=1;j<=q[i].cnt;j++)
            ed[q[i].c[j]].tim=tim; //把所有左半区域的询问里不存在的边打上标记 
    for(int i=mid+1;i<=rg;i++)
        for(int j=1;j<=q[i].cnt;j++)
        {
            int v=q[i].c[j]; 
            if(ed[v].tim!=tim)
            {
                int x=getfather(ed[v].u),y=getfather(ed[v].v);
                if(x!=y) stk1[++top]=x,stk2[top]=fa[x],fa[x]=y;
            }
        }// 把所有左半区域的询问里都存在的边加入并查集 
    CDQ(lf,mid); //分治左区间（询问） 
    while(top!=TOP) fa[stk1[top]]=stk2[top],top--; //撤销并查集 
    tim++;
    for(int i=mid+1;i<=rg;i++)
        for(int j=1;j<=q[i].cnt;j++)
            ed[q[i].c[j]].tim=tim; //对所有右区间不存在的边打上标记 
    for(int i=lf;i<=mid;i++)
        for(int j=1;j<=q[i].cnt;j++)
        {
            int v=q[i].c[j];
            if(ed[v].tim!=tim)
            {
                int x=getfather(ed[v].u),y=getfather(ed[v].v);
                if(x!=y) stk1[++top]=x,stk2[top]=fa[x],fa[x]=y;
            }
        } //把所有右区间存在的边加入并查集 
    CDQ(mid+1,rg); //分治右区间 
}

int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++)
        scanf("%d%d",&ed[i].u,&ed[i].v);
    scanf("%d",&T);tim=1; //一开始的标记tim不能是0，这是由于所有边的标记都默认为0，无法区分 
    for(int i=1;i<=T;i++)
    {
        scanf("%d",&q[i].cnt);
        for(int j=1;j<=q[i].cnt;j++)
            scanf("%d",&q[i].c[j]),ed[q[i].c[j]].tim=tim;
    }
    for(int i=1;i<=n;i++)
        fa[i]=i;
    for(int i=1;i<=m;i++)
        if(ed[i].tim!=tim)
        {
            int x=getfather(ed[i].u),y=getfather(ed[i].v);
            if(x!=y) fa[x]=y;
        }// 把对于所有询问都存在的边加入并查集 
    top=0;
    CDQ(1,T); //CDQ分治 
    for(int i=1;i<=T;i++)
        if(q[i].ans) printf("Connected\n");
        else printf("Disconnected\n");
    return 0;
}
/*
Whoso pulleth out this sword from this stone and anvil is duly born King of all England
*/
