#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int maxn = 5e5+10;
const ll INF = 1e17;
ll dp[maxn];
char s[maxn];
int n;
char c[maxn];
struct AC_machine
{
    int ch[maxn][26];
    int f[maxn];
    // f即为fail指针.
    int tot;
    ll val[maxn];
    int len[maxn];
    void insert(ll tmp)
    {
        int u=0,len1=strlen(s);
        for(int i=0;i<len1;i++)
        {
            if(!ch[u][s[i]-'a'])
                ch[u][s[i]-'a']=++tot,val[tot]=INF;
            u=ch[u][s[i]-'a'];
        }
        val[u]=min(val[u],tmp);
        len[u]=len1;
    } //往Trie树里插入元素.
    void build()
    {
        queue<int> q;
        for(int i=0;i<26;i++)
        {
            if(ch[0][i])
            f[ch[0][i]]=0,
            //第一层与其他单词不可能有公共前后缀,fail直接为根. 
            q.push(ch[0][i]);
        } 
        while(q.empty()!=1)
        {
            int u=q.front(); q.pop();
            for(int i=0;i<26;i++)
            if(ch[u][i])
            {
                f[ch[u][i]]=ch[f[u]][i];
                q.push(ch[u][i]);
                //画图理解贼容易.
            }
            else ch[u][i]=ch[f[u]][i];
            //这一步直接省略了查询时的比较.
        }
    } //构建Fail指针.
    void query()
    {
        int u=0;
        for(int i=1;i<=n;i++)
        {
            u=ch[u][c[i]-'a'];
            for(int j=u;j;j=f[j]) 
            //就用这个循环实现跳的过程.
            dp[i]=min(dp[i],dp[i-len[j]]+val[j]);
        }
    }
}AC;
 
int main()
{
    scanf("%d",&n);
    ll tmp;
    for(int i=1;i<=n;i++)
    {
        scanf("%s",s);
        scanf("%lld",&tmp);
        AC.insert(tmp);
    }
    scanf("%s",c+1);
    n=strlen(c+1);
    for(int i=1;i<=n;i++) dp[i]=INF;
    AC.build();
    AC.query();
    if(dp[n]==INF) printf("-1");
    else printf("%lld",dp[n]);
    return 0;
}
