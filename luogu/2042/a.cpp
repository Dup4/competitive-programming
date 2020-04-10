#include <bits/stdc++.h>
using namespace std;
#define dbg(x...) do { cout << "\033[32;1m" << #x << " -> "; err(x); } while (0) 
void err() { cout << "\033[39;0m" << endl; } 
template <class T, class... Ts> void err(const T& arg, const Ts&... args) { cout << arg << ' '; err(args...); }
typedef long long ll;
const int N = 4e6 + 10, INF = 0x3f3f3f3f;
int n, q, a[N];

struct ScapegoatTree {
	#define ls(o) t[o].ls
	#define rs(o) t[o].rs
	const double alpha = 0.76;
	struct node {
		int ls, rs, sz, valid; 
		bool del;
		ll v, sum, preMax, sufMax, allMax, modify_tag;
		int rev_tag; 
		void init(int x) { ls = rs = 0; sz = valid = 1; del = 0; sum = preMax = sufMax = allMax = v = x; modify_tag = INF; rev_tag = 0; } 
		node() {}
		node(int x) { init(x); }
		void up_modify(ll _modify_tag) { 
			v = _modify_tag;
			modify_tag = _modify_tag;
			sum = _modify_tag * valid;
		}
		void up_rev() {
			swap(ls, rs);
			rev_tag ^= 1;
		}
		node operator + (const node &other) const {
			node res = node(0); 
			res.sum = sum + other.sum;
			res.preMax = max(preMax, sum + other.preMax);
			res.sufMax = max(other.sufMax, sufMax + other.sum);
			res.allMax = max(allMax, other.allMax);
			res.allMax = max(res.allMax, sufMax + other.preMax);
			return res;
		}
	}t[N];
	int tot = 0, rt = 0;
	void init() { rt = 0; tot = 0; }
	int newnode(int x = 0) { ++tot; t[tot].init(x); return tot; } 
	bool bad(int o) {
		return (double)t[ls(o)].sz > alpha * t[o].sz || (double)t[rs(o)].sz > alpha * t[o].sz; 
	}
	void pushup(int o) { 
		t[o].sz = t[ls(o)].sz + t[rs(o)].sz + !t[o].del;
		t[o].valid = t[ls(o)].valid + t[rs(o)].valid + !t[o].del;
		t[o].sum = t[ls(o)].sum + t[rs(o)].sum + t[o].v; 
		t[o].preMax = max(t[ls(o)].preMax, t[ls(o)].sum + t[o].v);
		t[o].preMax = max(t[o].preMax, t[ls(o)].sum + t[o].v + t[rs(o)].preMax);
		t[o].sufMax = max(t[rs(o)].sufMax, t[o].v + t[rs(o)].sufMax);
		t[o].sufMax = max(t[o].sufMax, t[ls(o)].sufMax + t[o].v + t[rs(o)].sum);
		t[o].allMax = max(t[ls(o)].allMax, t[rs(o)].allMax);
		t[o].allMax = max(t[o].allMax, t[ls(o)].sufMax + t[o].v);
		t[o].allMax = max(t[o].allMax, t[o].v + t[rs(o)].preMax);
		t[o].allMax = max(t[o].allMax, t[ls(o)].sufMax + t[o].v + t[rs(o)].preMax);
	}
	void pushdown(int o) {
		ll &modify_tag = t[o].modify_tag;
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
	void dfs(int o, vector<int> &v) {
		if (!o) return;
		pushdown(o);
		dfs(ls(o), v);
		if (!t[o].del) v.push_back(o);
		dfs(rs(o), v);
		return;
	}
	int build(vector<int> &v, int l, int r) {
		if (l >= r) return 0;
		int mid = (l + r) >> 1;
		int o = v[mid];
		ls(o) = build(v, l, mid);
		rs(o) = build(v, mid + 1, r);
		pushup(o);
		return o;
	}
	void reBuild(int &o) {
		vector <int> v;
		dfs(o,v);
		o = build(v, 0, (int)v.size());
	}
	//在第id个位置插入x
	void insert(int &o, int id, int x) {
		if (!o) {
			o = newnode(x);
			//dbg(o, t[o].valid);
			//dbg(t[o].v, t[o].sum, t[o].preMax, t[o].sufMax, t[o].allMax);
			return;
		}
		pushdown(o);
		if (id <= t[ls(o)].valid + !t[o].del)
			insert(ls(o), id, x);
		else 
			insert(rs(o), id - t[ls(o)].valid - !t[o].del, x);
		pushup(o);
		//dbg(o, t[o].v, t[o].valid, ls(o), t[ls(o)].valid, rs(o), t[rs(o)].valid);
		if (bad(o)) reBuild(o);
		return;
	}
	//删除第id个数
	int del(int o, int id) {
		if (!t[o].del && id == t[ls(o)].valid + 1) {
			t[o].del = 1;
			int tmp = t[o].v;
			t[o].v = 0; 
			pushup(o);
			return tmp; 
		}
		pushdown(o);
		int x = 0;
		if (t[ls(o)].valid >= id)
			x = del(ls(o), id);
		else
			x = del(rs(o), id - t[ls(o)].valid - !t[o].del);
		pushup(o);
		return x;
	}
	//区间修改
	void update_modify(int o, int l, int r, int x) {
		if (!o) return;
		pushdown(o);
		if (l <= 1 && t[o].valid <= r) {
			t[o].up_modify(x);
		} else {
			if (l <= t[ls(o)].valid)
				update_modify(ls(o), l, r, x);
			if (r > t[ls(o)].valid + !t[o].del)
				update_modify(rs(o), l - t[ls(o)].valid - !t[o].del, r - t[ls(o)].valid - !t[o].del, x);
			if (!t[o].del && l <= t[ls(o)].valid + 1 && r >= t[ls(o)].valid + 1)
				t[o].v = x;
			pushup(o);
		}
	}
	//区间翻转
	void update_rev(int o, int l, int r) {
		if (!o) return;
		pushdown(o);
		if (l <= 1 && t[o].valid <= r) {
			t[o].up_rev();
		} else {
			if (l <= t[ls(o)].valid)
				update_rev(ls(o), l, r);
			if (r > t[ls(o)].valid + !t[o].del)
				update_rev(rs(o), l - t[ls(o)].valid - !t[o].del, r - t[ls(o)].valid - !t[o].del);
			pushup(o);
		}
	}
	//查询
	node query(int o, int l, int r) {
		if (!o) return node(0);
		pushdown(o);
		if (l <= 1 && t[o].valid <= r) {
			return t[o];
		} else {
			node ans = node(0); 
			if (l <= t[ls(o)].valid) 
				ans = ans + query(ls(o), l, r);
			if (!t[o].del && l <= t[ls(o)].valid + 1 && r >= t[ls(o)].valid + 1)  
				ans = ans + node(t[o].v);
			if (r > t[ls(o)].valid + !t[o].del) 
				ans = ans + query(rs(o), l - t[ls(o)].valid - !t[o].del, r - t[ls(o)].valid - !t[o].del);
			return ans;
		}
	}
}scapegoatTree;

int main() {
	while (scanf("%d%d", &n, &q) != EOF) {
		for (int i = 1; i <= n; ++i) scanf("%d", a + i);
		scapegoatTree.init();
		for (int i = 1; i <= n; ++i) scapegoatTree.insert(scapegoatTree.rt, i, a[i]);
	//	for (int i = 1; i <= n; ++i) {
	//		ScapegoatTree::node ans;
	//		ans = scapegoatTree.query(scapegoatTree.rt, i, i);
	//		dbg(i, ans.sum);
	//	}
		while (q--) {
			static char op[20];
			scanf("%s", op);
			if (strcmp(op, "INSERT") == 0) {
				static int pos, tot;
				scanf("%d%d", &pos, &tot);
				for (int i = 1, x; i <= tot; ++i) {
					scanf("%d", &x);
					scapegoatTree.insert(scapegoatTree.rt, pos + i, x);
				}
			} else if (strcmp(op, "DELETE") == 0) {
				static int pos, tot;
				scanf("%d%d", &pos, &tot);
				for (int i = 0; i < tot; ++i)
					scapegoatTree.del(scapegoatTree.rt, pos + i);
			} else if (strcmp(op, "MAKE-SAME") == 0) {
				static int pos, tot, c;
				scanf("%d%d%d", &pos, &tot, &c);
				scapegoatTree.update_modify(scapegoatTree.rt, pos, pos + tot - 1, c);	
			} else if (strcmp(op, "REVERSE") == 0) {
				static int pos, tot;
				scanf("%d%d", &pos, &tot);
				scapegoatTree.update_rev(scapegoatTree.rt, pos, pos + tot - 1);
			} else if (strcmp(op, "GET-SUM") == 0) {
				static int pos, tot;
				static ScapegoatTree::node ans;
				scanf("%d%d", &pos, &tot);
				ans = scapegoatTree.query(scapegoatTree.rt, pos, pos + tot - 1);
				printf("%lld\n", ans.sum);
			} else if (strcmp(op, "MAX-SUM") == 0) {
				static ll ans;
			   	ans = scapegoatTree.t[scapegoatTree.rt].allMax;
				printf("%lld\n", ans);
			}
			puts("------------------------------------------");
			int _n = scapegoatTree.t[scapegoatTree.rt].valid;
			for (int i = 1; i <= _n; ++i) {
				ScapegoatTree::node ans;
				ans = scapegoatTree.query(scapegoatTree.rt, i, i);
				dbg(i, ans.sum);
			}
		}
	}
	return 0;
}
