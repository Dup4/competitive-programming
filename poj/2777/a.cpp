#include<cstdio>
#include<cstring>
#include<algorithm>
#include <cassert>
using namespace std;
/*如果i结点代表的区间包含多种颜色那么 tree[i] == 0 否则 tree[i]代表的就是这段区间的颜色(不同的颜色用不同的非零整数表示)*/ 
const int maxn = 1e5+5;
int color[35],tree[maxn<<2],sum = 0;//color代表当前这种颜色是否被访问过 0没访问过 1访问过
void pushDown(int i){
	if (tree[i]){
		tree[i<<1] = tree[i<<1|1] = tree[i];
		tree[i] = 0;
	}
}
void update(int i,int l,int r,int L,int R,int val){
	if (l <= L && r >= R){
		tree[i] = val;
		return;
	}
	if (L == R) return;
	pushDown(i);
	int mid = (L+R) >> 1;
	if (l <= mid) update(i<<1,l,r,L,mid,val);
	if (r >  mid) update(i<<1|1,l,r,mid+1,R,val);
}
void query(int i,int l,int r,int L,int R){
	if (l <= L && r >= R){
		if (tree[i]){
			if (color[tree[i]] == 0){
				sum++;
				color[tree[i]] = 1;
			}
		}
		else{ 
			int mid = (L+R) >> 1;
			if (l <= mid) query(i<<1,l,r,L,mid);
			if (r >  mid) query(i<<1|1,l,r,mid+1,R);
		}
		return;		
	}
	if (L == R) return;
	pushDown(i);
	int mid = (L+R) >> 1;
	if (l <= mid) query(i<<1,l,r,L,mid);
	if (r >  mid) query(i<<1|1,l,r,mid+1,R);
}
int main(void){
	int L,T,O,l,r,val;
	char ch;
	tree[1] = 1;//题目要求刚开始整块板子的颜色为1 所有刚开始1号结点为1代表区间1~L全都是1 
	scanf("%d%d%d",&L,&T,&O);
	while (O--){
		getchar();
		scanf("%c",&ch);
		if (ch == 'C'){
			scanf("%d%d%d",&l,&r,&val);
			if (l > r) swap(l,r); 
			update(1,l,r,1,L,val);
		}
		else {
			memset(color,0,sizeof color);
			scanf("%d%d",&l,&r);
			if (l > r) swap(l,r);
			sum = 0;
			query(1,l,r,1,L);
			printf("%d\n",sum);
		}
	}
	return 0;
}
