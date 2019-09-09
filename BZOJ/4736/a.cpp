#include <bits/stdc++.h>
using namespace std;

const int N = 7e5 + 10;
int n, q, e[N][4]; 

struct LCT {
	#define ls t[x].son[0]
	#define rs t[x].son[1]
	struct node {
		int fa, son[2];
		int v, id, len, sum;  
		//翻转标记
		bool r;
		node() {
			fa = son[0] = son[1] = 0;
			v = id = len = sum = 0;
			r = 0;
		}
	}t[N];
	int sta[N], top;
	//如果x是所在链的根返回1
	inline bool isroot(int x) {
		return t[t[x].fa].son[0] != x && t[t[x].fa].son[1] != x;
	}
	//上传信息
	inline void pushup(int x) {
		t[x].sum = t[x].len;
		if (ls) t[x].sum += t[ls].sum;
		if (rs) t[x].sum += t[rs].sum;
		t[x].id = x;
		if (ls) if (t[t[x].id].v > t[t[ls].id].v) t[x].id = t[ls].id;
		if (rs) if (t[t[x].id].v > t[t[rs].id].v) t[x].id = t[rs].id;
	}
	//翻转操作
	inline void pushr(int x) {
		swap(ls, rs);
		t[x].r ^= 1;
	}
	//判断并且释放lazy
	inline void pushdown(int x) {
		if (t[x].r) {
			if (ls) pushr(ls);
			if (rs) pushr(rs);
			t[x].r = 0; 
		}	
	}
	inline void rotate(int x) {
		int y = t[x].fa, z = t[y].fa;
		int k = t[y].son[1] == x, w = t[x].son[!k];
		if (!isroot(y)) {
			t[z].son[t[z].son[1] == y] = x;
		}
		t[x].son[!k] = y;
		t[y].son[k] = w;
		if (w) {
			t[w].fa = y;
		}
		t[y].fa = x;
		t[x].fa = z;
		pushup(y); pushup(x);
	}
	//把x弄到根
	inline void splay(int x) {
		sta[++top] = x;
		for (int it = x; !isroot(it); it = t[it].fa) sta[++top] = t[it].fa;
		while (top) pushdown(sta[top--]);
		while (!isroot(x)) {
			int y = t[x].fa, z = t[y].fa;
			//此处和普通的splay不同
			if (!isroot(y)) {
				((t[y].son[0] == x) ^ (t[z].son[0] == y)) ? rotate(x) : rotate(y);
			}
			rotate(x);
		}
		pushup(x);
	}
	//把x到原图的同一个联通块的root弄成一条链，放在同一个splay中
	inline void access(int x) {
		for (int y = 0; x; y = x, x = t[x].fa) {
			splay(x);
			rs = y;
			pushup(x);
		}
	}
	//把x拎作原图的根
	inline void makeroot(int x) {
		access(x); splay(x); pushr(x);
	}
	//找到x所在联通块的splay的根
	inline int findroot(int x) {
		access(x); splay(x);
		//更稳妥的写法
		while (ls) pushdown(x), x = ls;
		splay(x);
		return x;
	}
	//把x到y的路径抠出来
	inline void split(int x, int y) {
		//先把x弄成原图的根
		makeroot(x);
		//再把y到根(x)的路径弄成重链
		access(y);
		//然后再让y成为splay的根，那么y的左子树中就是这条链的点
		splay(y); 
	}
	//连接x, y所在的两个联通块
	inline void link(int x, int y) {
		makeroot(x); 
		if (findroot(y) != x) t[x].fa = y;
	}
	//隔断x, y所在的两个联通块
	inline void cut(int x, int y) {
		makeroot(x);
		if (findroot(y) == x && t[y].fa == x && !t[y].son[0]) {
			t[y].fa = t[x].son[1] = 0; 
			pushup(x);
		}
	}
}lct;

int main() {
	scanf("%d%d", &n, &q); 
	for (int i = 0; i <= n + q; ++i) lct.t[i] = LCT::node(), lct.t[i].v = 1e9; 
	char op[10]; int id, u, v, t, l;
	while (q--) {
		scanf("%s", op);
		if (op[0] == 'f') {
			scanf("%d%d%d%d%d", &id, &u, &v, &t, &l); id += n + 1; ++u, ++v;
			e[id][0] = u; e[id][1] = v; e[id][2] = t; e[id][3] = l;
			lct.t[id].v = t; lct.t[id].len = l; 
			if (lct.findroot(u) != lct.findroot(v)) {
				lct.link(u, id); 
				lct.link(v, id);
			} else {
				lct.split(u, v);
				int _id = lct.t[v].id;
				if (e[_id][2] < t) {
				 	lct.cut(e[_id][0], _id);
					lct.cut(e[_id][1], _id);	
					lct.link(u, id);
					lct.link(v, id);
				}
			}
		} else if (op[0] == 'm') {
			scanf("%d%d", &u, &v); ++u, ++v;
			if (lct.findroot(u) != lct.findroot(v)) puts("-1");
			else {
				lct.split(u, v);
				printf("%d\n", lct.t[v].sum);
			}
		} else {
			scanf("%d%d", &id, &l); id += n + 1;
			lct.makeroot(id);
			lct.t[id].len = l;
			lct.pushup(id);
		}
	}
	return 0;
}
