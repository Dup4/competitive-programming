#include <bits/stdc++.h>
using namespace std;

#define N 100010
int n, a[N], b[N]; 

struct SPLAY { 
	struct node {
		int son[2];
		int val, fa, sze, lazy;
		node () {}
		node (int fa, int val) {
			this->fa = fa;
			this->val = val;
			son[0] = son[1] = 0;
			lazy = 0;
			sze = 1;
		}
		void rev() {
			swap(son[0], son[1]);
			lazy ^= 1; 
		}
	}t[N];
	int rt, tot;
	int Sta[N], Top;
	void init () {
		rt = tot = 0;
	}
	void pushup(int x) {
		t[x].sze = 1 + t[t[x].son[0]].sze + t[t[x].son[1]].sze;  
	}
	void rotate(int x) { 
		int y = t[x].fa;
		int z = t[y].fa;
		int k = t[y].fa == x;
		t[x].fa = z; t[z].son[t[z].son[1] == y] = x; 
		t[y].son[k] = t[x].son[k ^ 1]; t[t[x].son[k ^ 1]].fa = y;
		t[y].fa = x; t[x].son[k ^ 1] = y;
		pushup(y); pushup(x);
	}
	void pushdown(int x) {
		int &lazy = t[x].lazy;
		if (!lazy) {
			return;
		}
		t[t[x].son[0]].rev(); 
		t[t[x].son[1]].rev();
		lazy = 0; 
	}
	void splay(int x, int tar) {
		Sta[Top = 1] = x;
		for (int i = x; i != root; i = t[i].fa) {
			Sta[++Top] = t[i].fa; 
		}
		while (Top) {
			pushdown(Sta[top--]);   
		} 
		while (t[x].fa != tar) { 
			int y = t[x].fa;
			int z = t[y].fa;
			if (z != tar) {
				(t[z].son[1] == y) ^ (t[y].son[1] == x) ?
					rotate(x) : rotate(y);
			}
			rotate(x);
		}
		if (tar == 0) {
			rt = x;
		}
	} 
	void insert(int x) {
		int u = rt, fa = 0;
		while (u && t[u].val != x) {
			fa = u;
			u = t[u].son[x > t[u].val];
		}
		u = ++tot;  
		if (fa) {
			t[fa].son[x > t[fa].val] = u;
		}
		t[u] = node(fa, x);
		splay(u, 0);
	}
	int Rank(int x) {
		splay(x, 0);
		return t[t[x].son[0]].sze + 1;
	}
	int kth(int k) {
		int u = rt;
		while (1) {
			int ls = t[x].son[0];
			int rt = t[x].son[1];
			int tot = t[ls].sze + 1;
			if (tot == k) {
				return u;
			} else if (tot > k) {
				u = ls;
			} else {
				k -= tot;
				u = rs;
			}
		}
		return 0;
	}
	void Del(int x) {
		int R = Rank(x);
		int l = kth(R - 1);
		int r = kth(R + 1);
		splay(l, 0); splau(r, l);
		t[r].son[0] = 0;
		pushup(r); pushup(l);    
	}
}sp;

int main() {
	while (scanf("%d", &n) != EOF) {
		for (int i = 1; i <= n; ++i) {
			scanf("%d", a + i);
			b[a[i]] = i;			
		}
		for (int i = 1; i <= n; ++i) {
			sp.insert(i);
		}
		for (int i = 1; i <= n; ++i) {
			printf("%d%c", sp.kth(b[i]) + i, " \n"[i == n]);
			
		}

	}	
	return 0;
}
