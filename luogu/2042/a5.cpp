#include <bits/stdc++.h>
using namespace std;
#define dbg(x...) do { cout << "\033[32;1m" << #x << " -> "; err(x); } while (0) 
void err() { cout << "\033[39;0m" << endl; } 
template <class T, class... Ts> void err(const T& arg, const Ts&... args) { cout << arg << ' '; err(args...); }
typedef long long ll;
const int N = 5e5 + 10, INF = 0x3f3f3f3f;
int n, m, q, a[N];

struct Splay {
	#define ls(o) t[o].son[0]
	#define rs(o) t[o].son[1]
	struct MStack {
		int tot;
		vector <int> vec;
		void init() { vec.clear(); tot = 0; }
		int get() { 
			int tar = 0;
			if (!vec.empty()) {
				tar = vec.back();
				vec.pop_back(); 
			} else {
				tar = ++tot;
			}
			return tar;
		}
		void save(int x) { vec.push_back(x); }
	}mStack;
	struct node {
		int son[2], sze, fa; 
		int val, sum, preMax, sufMax, allMax, modify_tag, rev_tag;
		void init(int _val) { 
			son[0] = son[1] = 0; sze = 1; fa = 0;
			sum = preMax = sufMax = allMax = val = _val;
			modify_tag = INF; rev_tag = 0;
		}
		node() {}
		node(int val) { init(val); } 
		void up_modify(int _modify_tag) { 
			val = _modify_tag;
			modify_tag = _modify_tag;
			sum = _modify_tag * sze;
		    preMax = sufMax = allMax = max(val, sum);	
		}
		void up_rev() {
			swap(son[0], son[1]);
			rev_tag ^= 1;
			swap(preMax, sufMax);
		}
	}t[N];  
	int rt; 
	void init() { mStack.init(); rt = 0; t[0].preMax = t[0].sufMax = t[0].allMax = -INF; } 
	int newnode(int val) {  
		int tmp = mStack.get();
		t[tmp].init(val);
		return tmp;
	}
	void pushup(int o) { 
		t[o].sze = t[ls(o)].sze + t[rs(o)].sze + 1;
		t[o].sum = t[ls(o)].sum + t[rs(o)].sum + t[o].val;
		t[o].preMax = max(t[ls(o)].preMax, t[ls(o)].sum + t[o].val);
		t[o].preMax = max(t[o].preMax, t[ls(o)].sum + t[o].val + t[rs(o)].preMax);
		t[o].sufMax = max(t[rs(o)].sufMax, t[o].val + t[rs(o)].sum);
		t[o].sufMax = max(t[o].sufMax, t[ls(o)].sufMax + t[o].val + t[rs(o)].sum);
		t[o].allMax = t[o].val;
		t[o].allMax = max(t[o].allMax, t[ls(o)].allMax);
		t[o].allMax = max(t[o].allMax, t[rs(o)].allMax);
		t[o].allMax = max(t[o].allMax, t[ls(o)].sufMax + t[o].val);
		t[o].allMax = max(t[o].allMax, t[o].val + t[rs(o)].preMax);
		t[o].allMax = max(t[o].allMax, t[ls(o)].sufMax + t[o].val + t[rs(o)].preMax);
	}
	void pushdown(int o) {
		int &modify_tag = t[o].modify_tag;
		int &rev_tag = t[o].rev_tag;
		if (ls(o)) {
			if (modify_tag != INF) t[ls(o)].up_modify(modify_tag);
			if (rev_tag) t[ls(o)].up_rev();
		}
		if (rs(o)) {
			if (modify_tag != INF) t[rs(o)].up_modify(modify_tag);
			if (rev_tag) t[rs(o)].up_rev();
		}
		modify_tag = INF;
		rev_tag = 0;
	}
	void rotate(int x) {
		int y = t[x].fa;
		int z = t[y].fa;
		int k = (t[y].son[1] == x); 		
		t[z].son[t[z].son[1] == y] = x; 	
		t[x].fa = z;						
		t[y].son[k] = t[x].son[k ^ 1]; 		
		t[t[x].son[k ^ 1]].fa = y; 			
		t[x].son[k ^ 1] = y;				
		t[y].fa = x;
		pushup(y); pushup(x); 				
	}
	//旋转到tar的儿子处 如果tar = 0 即旋转到根
	void splay(int x, int tar) {  
		while (t[x].fa != tar) {
			int y = t[x].fa;
			int z = t[y].fa;
			if (z != tar)     
				(t[y].son[0] == x) ^ (t[z].son[0] == y) ? rotate(x) : rotate(y); 
			rotate(x);        
		}
		if (tar == 0)
			rt = x;
	}
	//找到序列中下标为k的所对应的树上节点
	int findKth(int k) {
		int u = rt;
		while (1) {
			pushdown(u);
			if (t[ls(u)].sze >= k) u = ls(u);
			else {
				if (t[ls(u)].sze + 1 == k) return u;
				else {
					k -= t[ls(u)].sze + 1;
					u = rs(u); 
				}
			}
		}
	}
	//返回区间[l, r]所对应的树上节点
	int split(int l, int r) {
		int x = findKth(l - 1);
		int y = findKth(r + 1);
		splay(x, 0); splay(y, x);
		return ls(y);
	}
	int build(int l, int r, int fa, int *a) {
	    if (l > r) return 0;	
		int mid = (l + r) >> 1, val = a[mid];  
		int o = newnode(val);
		t[o].fa = fa;
		ls(o) = build(l, mid - 1, o, a);
		rs(o) = build(mid + 1, r, o, a);
		pushup(o);
		return o;
	}
	void insert(int id, int tot, int *arr) {
		int x = findKth(id - 1);
		int y = findKth(id);
		int z = build(1, tot, 0, arr);
		splay(x, 0); splay(y, x);
		t[z].fa = y; ls(y) = z;	
		pushup(y); pushup(t[y].fa);
	}
	void del(int x) {
		mStack.save(x);
		if (ls(x)) del(ls(x));
		if (rs(x)) del(rs(x));
	}
	void del(int l, int r) {
		int x = split(l, r), y = t[x].fa;
		del(x);
		ls(y) = 0;
		pushup(y); pushup(t[y].fa);
	}
	void update_modify(int l, int r, int val) {
		int x = split(l, r), y = t[x].fa;
		t[x].up_modify(val);
		pushup(y); pushup(t[y].fa);
	}
	void update_rev(int l, int r) {
		int x = split(l, r), y = t[x].fa;
		t[x].up_rev();
		pushup(y); pushup(t[y].fa);
	}
	node query(int l, int r) {
		return t[split(l, r)];
	}
	void print(int u) {
		if (!u) return;
		print(ls(u));
		printf("%d %d %d\n", u, t[u].val, t[u].sum);
		print(rs(u));
	}
}splay;

int main() {
	while (scanf("%d%d", &n, &q) != EOF) {
		splay.init();
		a[1] = a[n + 2] = 0; 
		for (int i = 2; i <= n + 1; ++i) scanf("%d", a + i);
		splay.rt = splay.build(1, n + 2, 0, a);
		m = n + 2;
		while (q--) {
			static char op[20];
			scanf("%s", op);
			if (strcmp(op, "INSERT") == 0) {
				static int pos, tot;
				scanf("%d%d", &pos, &tot); 
				for (int i = 1; i <= tot; ++i) scanf("%d", a + i);
				splay.insert(pos + 2, tot, a);
				m += tot;
			} else if (strcmp(op, "DELETE") == 0) {
				static int pos, tot;
				scanf("%d%d", &pos, &tot);
				int l = pos, r = pos + tot - 1;
				splay.del(l + 1, r + 1);
				m -= tot;
			} else if (strcmp(op, "MAKE-SAME") == 0) {
				static int pos, tot, c;
				scanf("%d%d%d", &pos, &tot, &c);
				int l = pos, r = pos + tot - 1;
				splay.update_modify(l + 1, r + 1, c);
			} else if (strcmp(op, "REVERSE") == 0) {
				static int pos, tot;
				scanf("%d%d", &pos, &tot);
				int l = pos, r = pos + tot - 1;
				splay.update_rev(l + 1, r + 1);
			} else if (strcmp(op, "GET-SUM") == 0) {
				static int pos, tot;
				static Splay::node ans;
				scanf("%d%d", &pos, &tot);
				int l = pos, r = pos + tot - 1;
				ans = splay.query(l + 1, r + 1);
				printf("%d\n", ans.sum);
			} else if (strcmp(op, "MAX-SUM") == 0) {
				static Splay::node ans;
				ans = splay.query(2, m - 1);
				printf("%d\n", ans.allMax);
			}
		}
	}
	return 0;
}
