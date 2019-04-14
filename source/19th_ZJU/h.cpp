#include <bits/stdc++.h>
using namespace std;

/*
   1.找出所有桥，注意处理重边
   2.去掉所有桥，缩点
   3.遍历所有桥，如果桥是重边，将桥连接的两个点并起来
   4.加入所有桥，建树
   

   判断：
   1.先判联通性，不连通，直接No
   2.再判断u和v或者w是否在同一个联通快
   3.再判断树上两条简单路径是否有交

*/

#define N 100010
struct Edge {
	struct node {
		int to, nx;
		bool cut;
		node () {}
		node (int to, int nx) : to(to), nx(nx) {
			cut = false;
		}
	}a[N << 1];
	int head[N], pos;
	void init(int n) {
		for (int i = 0; i <= n; ++i) {
			head[i] = -1;
		}
		pos = 0;
	}
	void add(int u, int v) {
		a[pos] = node(v, head[u]); head[u] = pos++;
		a[pos] = node(u, head[v]); head[v] = pos++;
	}
}G[2];
#define erp(G, u) for (int it = G.head[u], v = G.a[it].to, cut = G.a[it].cut; ~it; it = G.a[it].nx, v = G.a[it].to, cut = G.a[it].cut)


int main() {
	
	return 0;
}
