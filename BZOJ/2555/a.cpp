#include <bits/stdc++.h>
using namespace std;

const int N = 6e5 + 10;
const int ALP = 26; 
int n, q;

struct LCT {
	#define ls t[x].son[0]
	#define rs t[x].son[1]
	struct node {
		int fa, son[2];
		int v, add; 
		//翻转标记
		bool r;
		node() {
			fa = son[0] = son[1] = 0;
			v = add = 0;
			r = 0;
		}
		void upadd(int _add) {
			v += _add;
			add += _add;
		}
	}t[N];
	int sta[N], top;
	//如果x是所在链的根返回1
	inline bool isroot(int x) {
		return t[t[x].fa].son[0] != x && t[t[x].fa].son[1] != x;
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
		if (t[x].add) {
			int &add = add;
			if (ls) t[ls].upadd(add);
			if (rs) t[rs].upadd(add);
			add = 0;
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

struct SAM {
	//空间开两倍，节点个数是两倍字符串长度
	//maxlen 表示节点i表示的最大后缀长度, nx[j]表示节点i加一个字符j所表示的字符串对应的节点
	//minlen 表示节点i表示的最小后缀长度，其等于t[t[i].fa].maxlen + 1 
	//fa 表示节点i的后缀链接 cnt 表示节点i的enspos集合大小 
	//c[]表示拓扑排序辅助数组,　rk[]表示拓扑序，rk[i],i小的节点所表示的后缀长度也小
	//pos表示那个结点在字符串的endpos的最小值，即firstpos
	struct node {
		int maxlen, cnt, fa, nx[ALP];
		node() { maxlen = cnt = fa = 0; memset(nx, 0, sizeof nx); }
	}t[N << 1];
	int tot, lst, c[N << 1], rk[N << 1];  
	inline int newnode() { 
		++tot;
		t[tot] = node();
		return tot;
	}
	inline void init() {
		tot = 0;
		lst = newnode();
	}
	inline void extend(int id) { 
		int cur = newnode(), p; 
		t[cur].cnt = 1;
		t[cur].maxlen = t[lst].maxlen + 1; 
		for (p = lst; p && !t[p].nx[id]; p = t[p].fa) t[p].nx[id] = cur;
		if (!p) {
			t[cur].fa = 1;
		} else {
			int q = t[p].nx[id];
			if (t[q].maxlen == t[p].maxlen + 1) {
				t[cur].fa = q;
			} else {
				int clone = newnode();
			  	t[clone] = t[q]; t[clone].cnt = 0;
				t[clone].maxlen = t[p].maxlen + 1; 
				for (; p && t[p].nx[id] == q; p = t[p].fa) t[p].nx[id] = clone;
				t[cur].fa = t[q].fa = clone;
			}
		}
		lst = cur; 	
	}
	//字符串从0开始 
	void build(char *s) { 
		init();
		for (int i = 0; s[i]; ++i) {
			extend(s[i] - 'a');
		}
		memset(c, 0, sizeof c); 
		for (int i = 1; i <= tot; ++i) c[t[i].maxlen]++;
		for (int i = 1; i <= tot; ++i) c[i] += c[i - 1];
		for (int i = 1; i <= tot; ++i) rk[c[t[i].maxlen]--] = i;
		for (int i = tot; i; --i) t[t[rk[i]].fa].cnt += t[rk[i]].cnt;
	}
	void solve() {
		ll res = 0;
		for (int i = 1; i <= tot; ++i) if (t[i].cnt > 1) {
			res = max(res, 1ll * t[i].cnt * t[i].maxlen);
		}
		printf("%lld\n", res);
	}
}sam;
