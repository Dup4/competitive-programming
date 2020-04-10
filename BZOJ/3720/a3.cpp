#include <bits/stdc++.h>
using namespace std;
#define dbg(x...) do { cout << "\033[32;1m" << #x << " -> "; err(x); } while (0) 
void err() { cout << "\033[39;0m" << endl; } 
template <class T, class... Ts> void err(const T& arg, const Ts&... args) { cout << arg << ' '; err(args...); }
#define SZ(x) (int(x.size()))
const int N = 2e5 + 10;
int n, q, a[N];

struct Graph {
	struct E { int to, nx, w; }e[N << 1]; int h[N], cnt;
	void init(int n) { for (int i = 0; i <= n; ++i) h[i] = -1; cnt = -1; }
	void addedge(int u, int v, int w = 0) { e[++cnt] = { v, h[u], w}; h[u] = cnt; } 
}G;

struct FHQ {
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
		int son[2], key, rnd, sze;
	}t[N * 10];
	void init() { mStack.init(); }
	void pushup(int x) { t[x].sze = t[ls(x)].sze + t[rs(x)].sze + 1; }
	int random() {
		static int seed = 703;
		return seed = int(seed * 48217ll % 2147483647);
	}
	int newnode(int key) {
		int tmp = mStack.get();
		t[tmp].sze = 1;
		t[tmp].key = key;
		t[tmp].rnd = random(); 
		t[tmp].son[0] = t[tmp].son[1] = 0;
		return tmp;
	} 
	void Copy(int &x) { int tmp = newnode(0); t[tmp] = t[x]; x = tmp; }
	int merge(int x, int y) {
	    if (!x && !y) return 0;
		if (!x) {
			Copy(y);
			return y;
		}	
		if (!y) {
			Copy(x);
			return x;
		}
		if (t[x].rnd < t[y].rnd) {
			Copy(x);
			t[x].son[1] = merge(t[x].son[1], y);
			pushup(x);
			return x;
		} else {
			Copy(y);
			t[y].son[0] = merge(x, t[y].son[0]);
			pushup(y);
			return y;
		}
	}
	void split(int now, int key, int &x, int &y) {
		if (!now) x = y = 0;
		else {
			if (t[now].key <= key) {
				x = now;
				split(t[now].son[1], key, t[now].son[1], y);
			} else {
				y = now;
				split(t[now].son[0], key, x, t[now].son[0]);
			}
			pushup(now);
		}
	}
	void insert(int &rt, int key) {
		int x, y;
		split(rt, key, x, y); 
		rt = merge(merge(x, newnode(key)), y); 
	}
	void del(int &rt, int key) {
		int x, y, z;
		split(rt, key - 1, x, y);
		split(y, key, y, z);
		if (ls(y) || rs(y)) {
			int tmp = y;
			y = merge(ls(y), rs(y));
			mStack.save(tmp);
		} else {
			mStack.save(y);
			y = 0;	
		}
		rt = merge(merge(x, y), z);
	}
	int query(int &rt, int key) {
		int x, y;
		split(rt, key, x, y);
		int res = t[y].sze;
		rt = merge(x, y);
		return res;
	}
	void save(int rt) {
		if (!rt) return;
		mStack.save(rt);
		if (ls(rt)) save(ls(rt));
		if (rs(rt)) save(rs(rt));
	}
	#undef ls
	#undef rs
}fhq;

struct ScapegoatTree {
	#define ls(o) t[o].ls
	#define rs(o) t[o].rs
	#define alpha 0.75
	struct node {
		int fa, ls, rs, v, sz, valid; 
		bool del;
		int fhqRt; 
		node() {}
		void init(int x) { fa = ls = rs = 0; v = x; sz = valid = 1; del = 0; fhqRt = 0; fhq.insert(fhqRt, x); } 
	}t[N];
	int tot, rt;
	void init() { rt = 0; tot = 0; }
	int newnode(int x = 0) { ++tot; t[tot].init(x); return tot; } 
	bool bad(int o) {
		return (double)t[ls(o)].sz > alpha * t[o].sz || (double)t[rs(o)].sz > alpha * t[o].sz;
	}
	void pushup(int o) {
		t[o].sz = t[ls(o)].sz + t[rs(o)].sz + !t[o].del;
		t[o].valid = t[ls(o)].valid + t[rs(o)].valid + !t[o].del; 
		t[o].fhqRt = fhq.merge(t[ls(o)].fhqRt, t[rs(o)].fhqRt);
		fhq.insert(t[o].fhqRt, t[o].v);
	}
	void dfs(int o, vector<int> &v) { 
		if (!o) return;
		dfs(ls(o), v);
		if (!t[o].del) v.push_back(o);
		dfs(rs(o), v);
		return;
	}
	int build(vector<int> &v, int l, int r, int fa) {  
		if (l >= r) return 0;
		int mid = (l + r) >> 1;
		int o = v[mid];
		t[o].fa = fa;
		fhq.save(t[o].fhqRt);
		t[o].fhqRt = 0;
		fhq.insert(t[o].fhqRt, t[o].v);
		ls(o) = build(v, l, mid, o);
		rs(o) = build(v, mid + 1, r, o);
		pushup(o);
		return o;
	}
	void reBuild(int &o, int fa) {
		vector <int> v;
		dfs(o, v); 
		o = build(v, 0, (int)v.size(), fa);
	}
	//在第id个位置插入x
	void insert(int &o, int id, int x, int fa) {
		if (!o) {
			o = newnode(x); 
			t[o].fa = fa;
			return;
		}
		t[o].sz++; t[o].valid++; 
		fhq.insert(t[o].fhqRt, x);
		if (id <= t[ls(o)].valid + !t[o].del)
			insert(ls(o), id, x, o);
		else 
			insert(rs(o), id - t[ls(o)].valid - !t[o].del, x, o);
		if (bad(o)) reBuild(o, t[o].fa); 
		return;
	}
	//修改第id个数
	int modify(int o, int id, int x) { 
		if (!t[o].del && id == t[ls(o)].valid + 1) {
			int pre = t[o].v;
			fhq.del(t[o].fhqRt, pre);
			fhq.insert(t[o].fhqRt, x);
			t[o].v = x;
			return pre; 
		}
		int pre = 0;
		if (t[ls(o)].valid >= id)
			pre = modify(ls(o), id, x);
		else
			pre = modify(rs(o), id - t[ls(o)].valid - !t[o].del, x);
		fhq.del(t[o].fhqRt, pre);
		fhq.insert(t[o].fhqRt, x);
		return pre;
	}
	int getRank(int o) {
		int ans = t[ls(o)].valid + 1;
		while (t[o].fa) {
			if (rs(t[o].fa) == o) ans += t[ls(t[o].fa)].valid + 1;
			o = t[o].fa;
		}
		return ans;
	}
	int query(int o, int l, int r, int x) { 
		if (!o) return 0;
		if (l <= 1 && t[o].valid <= r) {
			return fhq.query(t[o].fhqRt, x);
		} else {
			int ans = 0;
			if (l <= t[ls(o)].valid)
			    ans += query(ls(o), l, r, x);	
			if (r > t[ls(o)].valid + !t[o].del) 
				ans += query(rs(o), l - t[ls(o)].valid - !t[o].del, r - t[ls(o)].valid - !t[o].del, x);
			if (!t[o].del && t[o].v > x && l <= t[ls(o)].valid + 1 && r >= t[ls(o)].valid + 1)
				++ans;
			return ans;
		}
	}
	#undef ls
	#undef rs
	#undef alpha
}scapegoatTree;

int in[N], out[N];
namespace Tree { 
	vector <int> v;
	void dfs(int u, int fa) {
		in[u] = ++*in;
		v.push_back(*in);
		scapegoatTree.t[v.back()].init(a[u]);
		for (int i = G.h[u]; ~i; i = G.e[i].nx) {
			int v = G.e[i].to;
			if (v == fa) continue;
			dfs(v, u);
		}
		out[u] = ++*in; 
		v.push_back(*in);
		scapegoatTree.t[v.back()].init(0);
	}
	void init() {
		*in = 0;
		v.clear();
		dfs(1, 0);
		scapegoatTree.rt = scapegoatTree.build(v, 0, SZ(v), 0);
		scapegoatTree.tot = *in;
	}
}

int main(){
	scanf("%d", &n);
	G.init(n); 
	for (int i = 1, u, v; i < n; ++i) {
		scanf("%d%d", &u, &v);
		G.addedge(u, v);
		G.addedge(v, u); 
	}
	for (int i = 1; i <= n; ++i) scanf("%d", a + i); 
	Tree::init();
	int ans = 0;
	scanf("%d", &q);
	for (int i = 1; i <= q; ++i) {
		int opt, u, x;
		scanf("%d%d%d", &opt, &u, &x);
		u ^= ans; x ^= ans;
		if (opt == 0) {
			ans = scapegoatTree.query(scapegoatTree.rt, scapegoatTree.getRank(in[u]), scapegoatTree.getRank(out[u]), x);
			printf("%d\n",ans);
		} else if (opt == 1) {
			scapegoatTree.modify(scapegoatTree.rt, scapegoatTree.getRank(in[u]), x);
		} else if (opt == 2) {
			++n;
			in[n] = scapegoatTree.tot + 2;
			out[n] = scapegoatTree.tot + 1;
			int tmp = scapegoatTree.getRank(out[u]);
			scapegoatTree.insert(scapegoatTree.rt, tmp, 0, 0);
			scapegoatTree.insert(scapegoatTree.rt, tmp, x, 0);
		}
	}
	return 0;
}
