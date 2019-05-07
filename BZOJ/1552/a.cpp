#include <bits/stdc++.h>
using namespace std;

#define INF 0x3f3f3f3f
#define N 100010
#define pii pair <int, int>
#define fi first 
#define se second
int n, a[N];
pii b[N];

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
		int k = (t[y].son[1] == x);
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
		for (int i = x; i != rt; i = t[i].fa) {
			Sta[++Top] = t[i].fa; 
		}
		while (Top) {
			pushdown(Sta[Top--]);   
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
		//	printf("%d %d %d\n", u, t[u].val, k);
			if (t[u].lazy) {
				pushdown(u);
			}
			int ls = t[u].son[0];
			int rs = t[u].son[1];
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
		splay(l, 0); splay(r, l);
		t[r].son[0] = 0;
		pushup(r); pushup(l);    
	}
	void Reverse(int l, int r) {
		int pre = kth(l - 1);
		int nx = kth(r + 1); 
		splay(pre, 0); splay(nx, pre);
		if (t[nx].son[0] != 0) {
			t[t[nx].son[0]].rev();
		}
	}
	void output(int x) {
		if (!x) {
			return;
		}
		output(t[x].son[0]);
		printf("%d %d\n", x, t[x].val);
		output(t[x].son[1]);
	}
}sp;  

int main() {
	while (scanf("%d", &n) != EOF) {
		sp.init();
		for (int i = 1; i <= n; ++i) {
			scanf("%d", a + i);
			b[i] = pii(a[i], i);						
		}
		for (int i = 1; i <= n; ++i) {
			sp.insert(i);
		}
		sort(b + 1, b + 1 + n);  
		sp.insert(-INF);
		sp.insert(INF); 
		for (int i = 1; i <= n; ++i) { 
			int x = b[i].se;
			int y = sp.Rank(b[i].se);
			printf("%d%c", y + i - 2, " \n"[i == n]);
			sp.Reverse(2, y); 
			sp.Del(x);
		}
	}	
	return 0;
}
