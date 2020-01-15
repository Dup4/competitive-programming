#include<cstdio>
#include<queue>
#include<algorithm>
#include<iostream>
#include<cstring>
#include<cmath>
#define maxn 12
using namespace std;
int vis[maxn];
int t;
int b,a,bb[5];
bool sushu(int x){
	for(int i=2;i<=sqrt(x);i++){
		if(x%i==0)
		  return false;
	}
	return true;
}
struct node{
	int aa[5];
	int step;
}now,next;
int bfs(int step){
	now.step=step;
	queue<node> q;
	q.push(now);
	vis[a]=1;
	while(!q.empty()){
		now=q.front();
		q.pop();
		for(int i=0;i<4;i++){
			for(int j=0;j<=9;j++){
				next.aa[0]=now.aa[0];
				next.aa[1]=now.aa[1];
				next.aa[2]=now.aa[2];
				next.aa[3]=now.aa[3];
				next.aa[i]=j;
				if(next.aa[0]==bb[0]&&next.aa[1]==bb[1]&&next.aa[2]==bb[2]&&next.aa[3]==bb[3])
				      return next.step;
				if(next.aa[i]==now.aa[i]||next.aa[0]==0)
				   continue;  
				int num=next.aa[0]*1000+next.aa[1]*100+next.aa[2]*10+next.aa[3];
				if(vis[num]==0&&sushu(num)){
						vis[num]=1;
						next.step++;
						q.push(next);
					}
				}
			}
		}
}
int main(void){
	cin>>t;
	while(t--){
		memset(vis,0,sizeof(vis));
		scanf("%d%d",&a,&b);
		now.aa[0]=a%10;
		now.aa[1]=a/10%10;
		now.aa[2]=a/100%10;
		now.aa[3]=a/1000;
		bb[0]=b%10;
		bb[1]=b/10%10;
		bb[2]=b/100%10;
		bb[3]=b/1000;
		if(a==b)
		  printf("0\n");
		else{
			int count=bfs(0);
	       printf("%d\n",count);
	 }
	}
}
