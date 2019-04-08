#include<cstdio>
#include<cstring>
#include<string>
#include<iostream>
#include<sstream>
#include<algorithm>
#include<utility>
#include<vector>
#include<set>
#include<map>
#include<queue>
#include<cmath>
#include<iterator>
#include<stack>
using namespace std;
const int maxn=105;
char S[maxn];
int L,Pnum,Mnum,step;
void init()
{
    L=strlen(S)-1;
    Pnum=Mnum=0;  //豌豆射手与土豆的个数
    for(int i=0;i<=L;i++)
        if(S[i]=='P') Pnum++;
        else Mnum++;
}
bool judge(int totpnum,int pnum,int znum)
{
    int nowstep=step;
    int P_hp=10,Z_hp=50;  //豌豆射手和僵尸的hp
    while(pnum>0&&znum>0)
    {
        if(nowstep>0){ nowstep--; Z_hp-=totpnum; } //没走到豌豆射手处
        else{ P_hp-=znum; Z_hp-=totpnum; } //走到了两个都要受伤害
        if(P_hp<=0)  //死一个射手
        {
            P_hp=10;
            totpnum--; pnum--;
            nowstep=1;
        }
        if(Z_hp<=0){ Z_hp=50; znum--; } //死一个僵尸
    }
    if(pnum<=0&&znum>0) return true; //所有豌豆射手挂掉而僵尸有多的
    return false;
}
int BIS(int totpnum,int pnum) //二分
{
    int x=1,y=2*maxn,mid;
    while(x<=y)
    {
        mid=(x+y)/2;
        if(judge(totpnum,pnum,mid)) y=mid-1;
        else x=mid+1;
    }
    return y+1;
}
int solve()
{
    int ret=0;  //ret是需要的僵尸的个数
    if(S[L]=='M') { ret++; L--; step=2; } //最右边是土豆，step代表走到下一个位置需要的步数
    else step=1;
    while(L>=0)  //知道小于0才算赢
    {
        if(S[L]=='M') //是土豆
        {
            if(step>1) //往前走
            {
                step--;
                if(Pnum>=50) ret++; //超过50个豌豆射手死一个僵尸
                continue;
            }
            else ret++;  //炸死一个
            Mnum--; L--;
            step=2; //step变为2
        }
        else  //如果是豌豆射手
        {
            int pnum=0;
            for(int i=L;i>=0;i--)  //一直到找到土豆
                if(S[i]=='M') break;
                else pnum++;
            ret+=BIS(Pnum,pnum);  //二分得到最小的僵尸个数
            Pnum-=pnum;
            L-=pnum+1;  //多减1表示把土豆算进去了，因为有没死的僵尸在土豆处牺牲
            step=2;
        }
    }
    if(S[0]=='M') ret++; //如果最左边是土豆，则还需要一个僵尸去攻击首脑
    return ret;
}
int main()
{
    int T,Case=0;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%s",S); //植物
        init();
        printf("Case %d: %d\n",++Case,solve());
    }
    return 0;
}
