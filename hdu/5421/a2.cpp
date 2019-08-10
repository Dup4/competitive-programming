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
#define MAX 222222
inline int read()
{
    RG int x=0,t=1;RG char ch=getchar();
    while((ch<'0'||ch>'9')&&ch!='-')ch=getchar();
    if(ch=='-')t=-1,ch=getchar();
    while(ch<='9'&&ch>='0')x=x*10+ch-48,ch=getchar();
    return x*t;
}
struct Node
{
    int son[26],ff;
    int len,dep;
}t[MAX];
char s[MAX];
ll ans;
int tot,l,r,pre,suf,n;
void init()
{
    l=1e5,r=l-1;memset(s,'\0',sizeof(s));
    memset(t,0,sizeof(t));ans=0;
    t[pre=suf=0].ff=t[tot=1].ff=1;t[1].len=-1;
}
void extend(int c,int n,int &last,int op)
{
    int p=last;
    while(s[n]!=s[n-op*t[p].len-op])p=t[p].ff;
    if(!t[p].son[c])
    {
        int v=++tot,k=t[p].ff;t[v].len=t[p].len+2;
        while(s[n]!=s[n-op*t[k].len-op])k=t[k].ff;
        t[v].ff=t[k].son[c];t[p].son[c]=v;
        t[v].dep=t[t[v].ff].dep+1;
    }
    last=t[p].son[c];ans+=t[last].dep;
	cout << last << endl;
    if(t[last].len==r-l+1)pre=suf=last;
}
int main()
{
    while(scanf("%d",&n)!=EOF)
    {
        init();
        while(n--)
        {
            int opt=read();
            if(opt<=2)
            {
                char c=getchar();
                if(opt==1)s[--l]=c,extend(c-97,l,pre,-1);
                else s[++r]=c,extend(c-97,r,suf,1);
            }
            else if(opt==3)printf("%d\n",tot-1);
            else printf("%lld\n",ans);
        }
    }
    return 0;
}
