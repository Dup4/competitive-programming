#include <bits/stdc++.h>
using namespace std;

#define pii pair <int, int>
#define fi first
#define se second
const int N = 1e5 + 3e4 + 10;
const int M = 1e5 + 10;
int n, m, q;
map <pii, int> id;
struct Edge { int u, v, br; }e[M]; 
struct qnode { int op, u, v, ans; }qrr[40010];
struct LCT {
	#define ls t[x].son[0]
	#define rs t[x].son[1]
	struct node {
		int fa, son[2];
		int v, sum, lazy; 
		//翻转标记
		bool r;
		node() {
			fa = son[0] = son[1] = 0;
			v = sum = lazy = 0;
			r = 0;
		}
		void upzero() {
			sum = v = 0;
			lazy = 1;
		}
	}t[N];
	int sta[N], top;
	//如果x是所在链的根返回1
	inline bool isroot(int x) {
		return t[t[x].fa].son[0] != x && t[t[x].fa].son[1] != x;
	}
	//上传信息
	inline void pushup(int x) {
		t[x].sum = t[x].v;
		if (ls) t[x].sum += t[ls].sum;
		if (rs) t[x].sum += t[rs].sum;
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
		if (t[x].lazy) {
			if (ls) t[ls].upzero();
			if (rs) t[rs].upzero();
			t[x].lazy = 0;
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
		pushup(y);
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
	scanf("%d%d", &n, &m);
	id.clear();
	for (int i = 1, u, v; i <= m; ++i) {
		scanf("%d%d", &u, &v);
		if (u > v) swap(u, v);
		id[pii(u, v)] = i;
		e[i] = {u, v, 0};
	}
	int op, u, v; q = 0;
	while (1) {
		scanf("%d", &op); 
		if (op == -1) break;
		scanf("%d%d", &u, &v);
		if (u > v) swap(u, v);
		qrr[++q] = {op, u, v, 0};
		if (op == 0) e[id[pii(u, v)]].br = 1; 
	}
	for (int i = 0; i <= n + m; ++i) lct.t[i] = LCT::node();
	for (int i = 1; i <= m; ++i) {
		lct.t[i + n].v = 1;
		if (!e[i].br) {
			int u = e[i].u, v = e[i].v;
			if (lct.findroot(u) != lct.findroot(v)) {
				lct.link(u, i + n);
			    lct.link(v, i + n); 	
			} else {
				lct.split(u, v);
				lct.t[v].upzero();
			}
		}
	}
	for (int i = q; i >= 1; --i) {
		if (qrr[i].op) {
			int u = qrr[i].u, v = qrr[i].v;
			lct.split(u, v);
			qrr[i].ans = lct.t[v].sum; 
		} else {
			int u = qrr[i].u, v = qrr[i].v, _id = id[pii(u, v)];
			if (lct.findroot(u) != lct.findroot(v)) {
				lct.link(u, _id + n);
				lct.link(v, _id + n);
			} else {
				lct.split(u, v);
				lct.t[v].upzero(); 
			}
		}
	}
	for (int i = 1; i <= q; ++i) if (qrr[i].op) printf("%d\n", qrr[i].ans); 
	return 0;
}
