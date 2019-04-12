#include <bits/stdc++.h>
using namespace std;

#define N 500010
#define INF 0x3f3f3f3f
int n, m;
vector <int> vec[N];

struct Splay
{
	int root, tot;
	struct node
	{
		int son[2];
		int cnt, fa, sze, val;
	}t[N << 1];
	void init() { root = tot = 0; }
	void pushup(int x) { t[x].sze = t[x].cnt + t[t[x].son[0]].sze + t[t[x].son[1]].sze; }
	void rotate(int x)
	{
		int y = t[x].fa;
		int z = t[y].fa;
		int k = t[y].son[1] == x;
		t[x].fa = z; t[z].son[t[z].son[1] == y] = x;
		t[y].son[k] = t[x].son[k ^ 1]; t[t[x].son[k ^ 1]].fa = y;
		t[x].son[k ^ 1] = y; t[y].fa = x;
		pushup(y); pushup(x); 
	}
	void splay(int x, int tar)
	{
		while (t[x].fa != tar)
		{
			int y = t[x].fa;
			int z = t[y].fa;
			if (z != tar)
				(t[z].son[1] == y) ^ (t[y].son[1] == x) ? rotate(x) : rotate(y);
			rotate(x);
		}
		if (tar == 0)
			root = x;
	}
	void insert(int x)
	{
		int u = root, fa = 0;
		while (u && t[u].val != x)
		{
			fa = u;
			u = t[u].son[x > t[u].val];
		}
		if (u) ++t[u].cnt;
		else
		{
			u = ++tot;
			if (fa) 
				t[fa].son[x > t[fa].val] = u;	
			t[u].fa = fa;
			t[u].val = x;
			t[u].cnt = t[u].sze = 1;
			t[u].son[0] = t[u].son[1] = 0;
		}
		pushup(u);
		splay(u, 0);
	}
	void find(int x)
	{
		int u = root;
		if (!u) return;
		while (t[u].son[x > t[u].val] && t[u].val != x)
			u = t[u].son[x > t[u].val];
		splay(u, 0);
	}
	int Next(int x, int f) //0 前驱 1 后继
	{
		find(x);
		int u = root;
		if (!f && t[u].val < x) return u;
		if (f && t[u].val > x) return u;
		u = t[u].son[f];
		while (t[u].son[f ^ 1]) u = t[u].son[f ^ 1];
		splay(u, 0); 
		return u;
	}
	void Delete(int x)
	{
		int last = Next(x, 0);
		int nx = Next(x, 1);
		splay(last, 0), splay(nx, last);
		int del = t[nx].son[0];
		if (del == 0) return;
		if (t[del].cnt > 1)
		{
			--t[del].cnt;
			splay(del, 0);
		}
		else
		{
			t[nx].son[0] = 0;
			splay(nx, 0);
		}
	}
	int kth(int k)
	{
		int u = root;
		if (t[u].sze < k) return -1;
		while (233)
		{
			int y = t[u].son[0];
			if (t[u].cnt + t[y].sze < k)
			{
				k -= t[u].cnt + t[y].sze;
				u = t[u].son[1];
			}
			else if (t[y].sze >= k) u = y; 
			else return t[u].val;
		}
	}
}sp[3];

int main()
{
	while (scanf("%d%d", &n, &m) != EOF)
	{
		for (int i = 0; i < 3; ++i) 
		{
			sp[i].init();
			sp[i].insert(INF);
			sp[i].insert(-INF); 
		}
		for (int i = 1, x; i <= n; ++i)
		{
			vec[i].clear();
			scanf("%d", &x);
			vec[i].push_back(x); 
			sp[0].insert(x); 
		}
		for (int i = 1; i <= n; ++i)
		{
			int x = vec[i][0];
			int y = sp[0].t[sp[0].Next(x, 0)].val;
			if (y != -INF) sp[1].insert(x - y); 
			if (i > 1) sp[2].insert(abs(x - vec[i - 1][0]));
		}
		char op[25]; int x, k, y, z;
		while (m--)
		{
			scanf("%s", op);
			switch(op[4]) 
			{
				case 'R' :
					scanf("%d%d", &k, &x);
					y = sp[0].t[sp[0].Next(x, 0)].val;
					z = sp[0].t[sp[0].Next(x, 1)].val;
					if (y != -INF) sp[1].insert(x - y);
					if (z != INF) sp[1].insert(z - x); 
					if (k != n)
					{
						sp[2].Delete(abs(vec[k].end()[-1] - vec[k + 1][0]));
						sp[2].insert(abs(x - vec[k + 1][0]));
					}
					sp[2].insert(abs(x - vec[k].end()[-1]));
					vec[k].push_back(x);
					sp[0].insert(x);
					break;
				case 'G' :
					printf("%d\n", sp[2].kth(2));
					break;
				case 'S' :
					printf("%d\n", sp[1].kth(2));
					break;
				default :
					assert(0); 
			}
		}
	}
	return 0;
}
