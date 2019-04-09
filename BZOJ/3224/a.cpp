#include <bits/stdc++.h>
using namespace std;

#define N 500010

struct Splay
{
	int root, tot;
	struct node
	{
		int son[2];
		int val, cnt, fa, sze;
		node() {}
	}t[N];
	void init() { root = tot = 0; }
	//更新子树大小
	void pushup(int u) 
	{
		int ls = t[u].son[0], rs = t[u].son[1];
		t[u].sze = t[ls].sze + t[rs].sze + t[u].cnt;
	}
	void rotate(int x)
	{
		int y = t[x].fa;
		int z = t[y].fa;
		int k = (t[y].son[1] == x);
		t[z].son[t[z].son[1] == y] = x;
		t[x].fa = z;
		t[y].son[k] = t[x].son[k ^ 1];
		t[t[x].son[k ^ 1]].fa = y;
		t[x].son[k ^ 1] = y;
		t[y].fa = x;
		pushup(x); pushup(y);
	}
	void splay(int x, int tar)
	{
		while (t[x].fa != tar)
		{
			int y = t[x].fa;
			int z = t[y].fa;
			if (z != tar)
				(t[y].son[0] == x) ^ (t[z].son[0] == y) ? rotate(x) : rotate(y);
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
			t[u].son[0] = t[u].son[1] = 0;
			t[u].fa = fa;
			t[u].val = x;
			t[u].cnt = t[u].sze = 1;
		}
		splay(u, 0);
	}
	void find(int x)
	{
		int u = root;
		if (!u) return;
		while (t[u].son[x > t[u].val] && x != t[u].val)
			u = t[u].son[x > t[u].val];
		splay(u, 0);
	}
	int Next(int x, int f)
	{
		find(x);
		int u = root;
		if (f && t[u].val > x) return u;
		if (!f && t[u].val < x) return u;
		u = t[u].son[f];
		while (t[u].son[f ^ 1]) u = t[u].son[f ^ 1];
		return u;
	}
	void Delete(int x)
	{
		int last = Next(x, 0);
		int nx = Next(x, 1);
		splay(last, 0); splay(nx, last); 
		int del = t[nx].son[0];
		if (t[del].cnt > 1) 
		{
			--t[del].cnt;
			splay(del, 0);
		}
		else
			t[nx].son[0] = 0;
	}
	int kth(int k)
	{
		int u = root;
		if (t[u].sze < k)
			return 0;
		while (1)
		{
			int y = t[u].son[0];
			if (k > t[y].sze + t[u].cnt)
			{
				k -= t[y].sze + t[u].cnt;
				u = t[u].son[1];
			}
			else
			{
				if (t[y].sze >= k)
					u = y;
				else
					return t[u].val;
			}
		}
	}
}splay;

int main()
{
	int n; scanf("%d", &n);
	splay.init();
	splay.insert(+2147483647);
	splay.insert(-2147483647);
	int op, x;
	while (n--)
	{
		scanf("%d%d", &op, &x);
		switch(op)
		{
			case 1: 
				splay.insert(x);
				break;
			case 2:
				splay.Delete(x);
				break;
			case 3:
				splay.find(x);
				printf("%d\n", splay.t[splay.t[splay.root].son[0]].sze);
				break;
			case 4:
				printf("%d\n", splay.kth(x + 1));
				break;
			case 5:
				printf("%d\n", splay.t[splay.Next(x, 0)].val);
				break;
			case 6:
				printf("%d\n", splay.t[splay.Next(x, 1)].val);
				break;
			default:
				assert(0);
		}
	}
	return 0;
}
