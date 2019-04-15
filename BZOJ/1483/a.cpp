#include <bits/stdc++.h>
using namespace std;

#define N 1000010
#define INF 0x3f3f3f3f
int n, q, res;
struct Splay {
	int root[N], tot;  
	struct node {
		int son[2];
		int val, fa;
	}t[N * 40];
	void init() {
		memset(root, 0, sizeof root);
		tot = 0;
	}
	void rotate(int x) {
		int y = t[x].fa;
		int z = t[y].fa;
		int k = t[y].son[1] == x;
		t[x].fa = z; t[z].son[t[z].son[1] == y] = x;
		t[x].son[k ^ 1].fa = y; t[y].son[k] = t[x].son[k ^ 1];
		t[y].fa = x; t[x].son[k ^ 1] = y;
	}
	void splay(int &rt, int x, int tar) {
		while (t[x].fa != tar) {
			int y = t[x].fa;
			int z = t[y].fa;
			if (z != tar) {
				(t[z].son[1] == y) ^ (t[y].son[1] == x) ? rotate(x) : rotate(y);
			}
			rotate(x);
		}
		if (tar == 0) {
			rt = x;
		}
	}
	void insert(int &rt, int x) {
		int u = rt, fa = 0;
		while (t[u].son[x > t[u].val] && x != t[u].val) {
			fa = u;
			u = t[u].son[x > t[u].val];
		}
		if (u) {
			assert(0);
		} else {
			u = ++tot;
			if (fa) {
				t[fa].son[x > t[fa].val] = u;
			} 
			t[u].son[0] = t[u].son[1] = 0;
			t[u].val = x; t[u].fa = fa;
		}
		splay(rt, u, 0);
	}
	void Next(int &rt, int x, int f) {
		int u = rt;
		u = t[u].son[f];
		while (t[u].son[f ^ 1]) {
			u = t[u].son[f ^ 1];
		}
		return t[u].val;
	}
	void merge(int now, int &rt) {
		if (now == 0) {
			return;
		}
		merge(t[now].son[0]);
		insert(rt, t[now].val);
		merge(t[now].son[1]);
	} 
}sp;

int main() {
	while (scanf("%d%d", &n, &q) != EOF) {
		sp.init(); res = n;
		for (int i = 1; i <= n; ++i) {
			sp[i].insert(INF);
			sp[i].insert(-INF);
		}	
		for (int i = 1, x; i <= n; ++i) {
			scanf("%d", &x);
			sp.insert(sp.root[x], i);
			int y = sp.Next(sp.root[x], i, 0);
			if (y == i - 1) {
				--res;
			}	
		}
		int op, x, y;
		while (q--) {
			scanf("%d", &op);
			switch(op) {
				case 1 :
					
					break;
				case 2 :
					printf("%d\n", res);
					break;
				default :
					assert(0);
			}
		}
	}
	return 0;
}
