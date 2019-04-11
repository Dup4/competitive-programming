#include <bits/stdc++.h>
using namespace std;

#define N 100010
struct Splay
{
	int root[N], tot;
	struct node
	{
		int son[2];
		int val, cnt, fa, sze;
	}t[N * 40];
	
	
}

int n, m, q;
int pre[N], arr[N];;
int find(int x) { return pre[x] == 0 ? x : pre[x] = find(pre[x]); }
void join(int x, int y) 
{
	
}


int main() 
{
	while (scanf("%d%d", &n, &m) != EOF) 
	{
		memset(pre, 0, sizeof pre); 
		for (int i = 1; i <= n; ++i) 
			scanf("%d", arr + i);
		for (int i = 1, u, v; i <= m; ++i)
		{
			scanf("%d%d", &u, &v);
			join(u, v);
		}
			
	}
	return 0;
}
