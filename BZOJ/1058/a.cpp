#include <bits/stdc++.h>
using namespace std;

#define N 510010
#define INF 0x3f3f3f3f
int n, m, Min;
vector <int> vec[N];

struct Splay
{
	int root, tot;
	struct node
	{
		int son[2];
		int fa, val; 
	}t[N << 1];   
	inline void init() { root = tot = 0; }
	inline void rotate(int x) 
	{
		int y = t[x].fa;
		int z = t[y].fa;
		int k = t[y].son[1] == x;
		t[x].fa = z; t[z].son[t[z].son[1] == y] = x;
		t[y].son[k] = t[x].son[k ^ 1]; t[t[x].son[k ^ 1]].fa = y;
		t[x].son[k ^ 1] = y; t[y].fa = x;
	}
	inline void splay(int x, int tar)    
	{
		while (t[x].fa != tar)
		{
			int y = t[x].fa;
			int z = t[y].fa;
			if (z != tar)
				(t[z].son[0] == y) ^ (t[y].son[0] == x) ? rotate(x) : rotate(y); 
			rotate(x);
		}
		if (tar == 0)
			root = x;
	}
	inline void insert(int x)
	{
		int u = root, fa = 0;
		while (u && t[u].val != x)
		{
			fa = u;
			u = t[u].son[x > t[u].val];
		}
		if (u) Min = 0; 
		else
		{
			u = ++tot;
			if (fa) 
				t[fa].son[x > t[fa].val] = u;	
			t[u].fa = fa;
			t[u].val = x;
			t[u].son[0] = t[u].son[1] = 0;
		}
		splay(u, 0);
	}
	inline int Next(int x, int f) //0 前驱 1 后继
	{
		int u = root;
		u = t[u].son[f];
		while (t[u].son[f ^ 1]) u = t[u].son[f ^ 1];
		return t[u].val;
	}
}sp[1];
struct PQ {
	priority_queue <int, vector <int>, greater <int> > q, d;
	void clear() {
		while (!q.empty()) {
			q.pop();
		}
		while (!d.empty()) {
			d.pop();
		}
	}
	void push(int x) {
		q.push(x);
	}
	void del(int x) {
		d.push(x);
	}
	int top() {
		while (!d.empty() && d.top() == q.top()) {
			d.pop();
			q.pop();
		}
		return q.top();
	}
}pq;
inline int read()
{
    int x=0,t=1;char ch=getchar();
    while((ch<'0'||ch>'9')&&ch!='-')ch=getchar();
    if(ch=='-')t=-1,ch=getchar();
    while(ch<='9'&&ch>='0')x=x*10+ch-48,ch=getchar();
    return x*t;
}

int main()
{
	n = read(), m = read();
	pq.clear(); 
	Min = 1e9; 
	for (int i = 0; i < 1; ++i) 
	{
		sp[i].init();
		sp[i].insert(INF);
		sp[i].insert(-INF); 
	}
	for (int i = 1, x; i <= n; ++i)
	{
		vec[i].clear();
		x = read();
		vec[i].push_back(x);  
		if (i > 1) pq.push(abs(x - vec[i - 1][0]));    
	}
	for (int i = 1; i <= n; ++i)
	{
		int x = vec[i][0]; 
		sp[0].insert(x);
		if (Min > 0) {
			int y = sp[0].Next(x, 0);
			int z = sp[0].Next(x, 1);
			if (y != -INF) {
				Min = min(Min, x - y);  
			}
			if (z != INF) {
				Min = min(Min, z - x);
			}
		}
	}
	char op[25]; int x, k, y, z;
	while (m--)
	{
		scanf("%s", op);
		switch(op[4]) 
		{
			case 'R' :
				k = read(), x = read();
				pq.push(abs(x - vec[k].end()[-1]));
				if (k != n)
				{
					pq.del(abs(vec[k].end()[-1] - vec[k + 1][0]));
					pq.push(abs(x - vec[k + 1][0]));
				}
				vec[k].push_back(x);
				sp[0].insert(x);
				if (Min > 0) {
					y = sp[0].Next(x, 0);
					z = sp[0].Next(x, 1);
					if (y != -INF) {
						Min = min(Min, x - y);
					}
					if (z != INF) {
						Min = min(Min, z - x);
					}
				}
				break;
			case 'G' :
				printf("%d\n", pq.top());
				break;
			case 'S' :
				printf("%d\n", Min);
				break;
			default :
				assert(0); 
		}
	}
	return 0;
}
