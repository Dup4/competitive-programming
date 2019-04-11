#include <bits/stdc++.h>
using namespace std;

#define N 100010
int n, q;
bool flag;
struct Splay
{
	int root, tot;
	struct node
	{
		int son[2];
		int val, fa, sze, lazy; 
		node () {}
		node (int val, int fa) : val(val), fa(fa) 
		{
			son[0] = son[1] = 0;
			sze = 1;
			lazy = 0;
		}
	}t[N];
	void init() { root = tot = 0; }
	void pushup(int x) { t[x].sze = t[t[x].son[0]].sze + t[t[x].son[1]].sze + 1; }
	void pushdown(int x) 
	{
		if (t[x].lazy)
		{
			int ls = t[x].son[0];
			int rs = t[x].son[1];
			if (ls) t[ls].lazy ^= 1;
			if (rs) t[rs].lazy ^= 1;
			swap(t[x].son[0], t[x].son[1]);
			t[x].lazy = 0;
		}
	}
	void rotate(int x)
	{
		int y = t[x].fa;
		int z = t[y].fa;
		int k = t[y].son[1] == x;
		t[x].fa = z; t[z].son[t[z].son[1] == y] = x; 
		t[t[x].son[k ^ 1]].fa = y; t[y].son[k] = t[x].son[k ^ 1];
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
				(t[z].son[0] == y) ^ (t[y].son[0] == x) ? rotate(x) : rotate(y);
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
		u = ++tot;
		if (fa) t[fa].son[x > t[fa].val] = u;
		t[u] = node(x, fa);
		splay(u, 0);
	}
	int kth(int k)
	{
		int u = root;
		while (1)
		{
			pushdown(u);
			int y = t[u].son[0];
			if (t[y].sze + 1 < k)
			{
				k -= t[y].sze + 1;	
				u = t[u].son[1];
			}
			else
			{
				if (t[y].sze + 1 == k)
					return u;
				else
					u = t[u].son[0];
			}
		}
	}
	void print(int u)
	{
		if (u == 0) return;
		pushdown(u); 
		print(t[u].son[0]);
		if (t[u].val > 1 && t[u].val < n + 2) 
		{
			if (!flag) flag = 1;
			else printf(" ");
			printf("%d", t[u].val - 1);
		}
		print(t[u].son[1]);
	}
	void work(int l, int r)
	{
		int x = kth(l);
		int y = kth(r + 2);
		splay(x, 0); splay(y, x);
		t[t[t[root].son[1]].son[0]].lazy ^= 1;
	}
}sp;

int main()
{
	while (scanf("%d%d", &n, &q) != EOF)
	{
		sp.init();
		for (int i = 1; i <= n + 2; ++i) sp.insert(i);
		int l, r;
		while (q--)
		{
			scanf("%d%d", &l, &r);
			sp.work(l, r);
		}
		flag = 0;
		sp.print(sp.root);
		puts("");
	}
	return 0;
}
