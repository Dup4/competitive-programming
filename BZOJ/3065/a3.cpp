#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define SZ(x) (int(x.size()))
#define dbg(x...) do { cout << "\033[32;1m" << #x << " -> "; err(x); } while (0) 
void err() { cout << "\033[39;0m" << endl; } 
template <class T, class... Ts> void err(const T& arg, const Ts&... args) { cout << arg << ' '; err(args...); }
const int N = 7e4 + 10;
int n, m, vLimit, q, a[N], segRtVec[N], valVec[N];

struct SEG {
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
		int ls, rs; 
		int sum;
		void init() { ls = rs = sum = 0; }
	}t[N * 250];
	void init() { mStack.init(); }
	int newnode() { int now = mStack.get(); t[now].init(); return now; }
	void pushup(int id) {
		t[id].sum = 0;
		int ls = t[id].ls, rs = t[id].rs;
		if (ls) t[id].sum += t[ls].sum;
		if (rs) t[id].sum += t[rs].sum; 
	}
	void update(int &id, int l, int r, int pos, int v) {
		if (!id) id = newnode();
		if (l == r) {
			t[id].sum += v;
			return;
		}
		int mid = (l + r) >> 1;
		if (pos <= mid) update(t[id].ls, l, mid, pos, v);
		else update(t[id].rs, mid + 1, r, pos, v);
		pushup(id); 
	}
	void save(int id) {
		if (!id) return;
		mStack.save(id);
		save(t[id].ls);
		save(t[id].rs);
	}
	int query(int l, int r, int k) {
		if (l == r) return l;
		int mid = (l + r) >> 1;
		int leftSum = 0;
		for (int i = 1; i <= *segRtVec; ++i) {
			leftSum += t[t[segRtVec[i]].ls].sum;
		}
		for (int i = 1; i <= *valVec; ++i) {
			leftSum += (valVec[i] >= l && valVec[i] <= mid);
		}
		if (leftSum >= k) {
			for (int i = 1; i <= *segRtVec; ++i) segRtVec[i] = t[segRtVec[i]].ls;
			return query(l, mid, k);
		} else {
			for (int i = 1; i <= *segRtVec; ++i) segRtVec[i] = t[segRtVec[i]].rs;	
			return query(mid + 1, r, k - leftSum);
		}
	}
}seg;

const double alpha = 0.75;
struct ScapegoatTree {
	#define ls(o) t[o].ls
	#define rs(o) t[o].rs
//	double alpha = 0.76;
	struct node {
		int ls, rs, v, sz, valid; 
		bool del;
		int segRt;
		node() {}
		void init(int x) { ls = rs = 0; v = x; sz = valid = 1; del = 0; segRt = 0;  } 
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
	}
	void dfs(int o, vector<int> &v, vector <int> &val) {
		if (!o) return;
		dfs(ls(o), v, val);
		if (!t[o].del) v.push_back(o), val.push_back(t[o].v);
		dfs(rs(o), v, val);
		return;
	}
	int build(vector<int> &v, vector <int> &val, int l, int r) {
		if (l >= r) return 0;
		int mid = (l + r) >> 1;
		int o = v[mid];
		seg.save(t[o].segRt); 
		t[o].segRt = 0;
		for (int i = l; i < r; ++i)
			seg.update(t[o].segRt, 0, vLimit, val[i], 1);
		ls(o) = build(v, val, l, mid);
		rs(o) = build(v, val, mid + 1, r);
		pushup(o);
		return o;
	}
	void reBuild(int &o) {
		vector <int> v, val;
		dfs(o, v, val); 
		o = build(v, val, 0, (int)v.size());
	}
	//在第id个位置插入x
	void insert(int &o, int id, int x) {
		if (!o) {
			o = newnode(x);  
			seg.update(t[o].segRt, 0, vLimit, x, 1);
			return;
		}
		t[o].sz++; t[o].valid++; 
		seg.update(t[o].segRt, 0, vLimit, x, 1);
		if (id <= t[ls(o)].valid + !t[o].del)
			insert(ls(o), id, x);
		else 
			insert(rs(o), id - t[ls(o)].valid - !t[o].del, x);
		if (bad(o)) reBuild(o);
		return;
	}
	//修改第id个数
	int modify(int o, int id, int x) {
		if (!t[o].del && id == t[ls(o)].valid + 1) {
			int pre = t[o].v;
			seg.update(t[o].segRt, 0, vLimit, pre, -1);
			seg.update(t[o].segRt, 0, vLimit, x, 1);
			t[o].v = x;
			return pre; 
		}
		int pre = 0;
		if (t[ls(o)].valid >= id)
			pre = modify(ls(o), id, x);
		else
			pre = modify(rs(o), id - t[ls(o)].valid - !t[o].del, x);
		seg.update(t[o].segRt, 0, vLimit, pre, -1);
		seg.update(t[o].segRt, 0, vLimit, x, 1);
		return pre;
	}
	//取出[l, r]区间的线段树节点
	void _query(int o, int l, int r) {
		if (!o) return;
		if (l <= 1 && t[o].valid <= r) {
			segRtVec[++*segRtVec] = t[o].segRt;
			return;
		} else {
			if (l <= t[ls(o)].valid)
			    _query(ls(o), l, r);	
			if (r > t[ls(o)].valid + !t[o].del) 
				_query(rs(o), l - t[ls(o)].valid - !t[o].del, r - t[ls(o)].valid - !t[o].del);
			if (!t[o].del && l <= t[ls(o)].valid + 1 && r >= t[ls(o)].valid + 1)
				valVec[++*valVec] = t[o].v;
		}
	}
	int query(int l, int r, int k) {
		*segRtVec = 0; *valVec = 0;
		_query(rt, l, r);
		return seg.query(0, vLimit, k);
	}
}scapegoatTree;

//int decode(int x, int lst) { return x ^ lst; }
int decode(int x, int lst) { return x; }

int main() {
	vLimit = 70000;
	while (scanf("%d", &n) != EOF) {
		for (int i = 1; i <= n; ++i) scanf("%d", a + i);
		scapegoatTree.init();
		seg.init();
		m = n;
		for (int i = 1; i <= n; ++i) scapegoatTree.insert(scapegoatTree.rt, i, a[i]);
		scanf("%d", &q);
		int lst = 0;
		while (q--) {
			static char op[2];
			static int l, r, k, x, val;
			scanf("%s", op);
			if (op[0] == 'Q') {
				scanf("%d%d%d", &l, &r, &k);
				l = decode(l, lst);
				r = decode(r, lst);
				k = decode(k, lst);
				lst = scapegoatTree.query(l, r, k);
				printf("%d\n", lst);
			} else if (op[0] == 'M') {
				scanf("%d%d", &x, &val);
				x = decode(x, lst);
				val = decode(val, lst);
				scapegoatTree.modify(scapegoatTree.rt, x, val);
			} else if (op[0] == 'I') {
				scanf("%d%d", &x, &val);
				x = decode(x, lst);
				val = decode(val, lst);
				scapegoatTree.insert(scapegoatTree.rt, x, val);
			}
		//	vector <int> v, _v;
		//	scapegoatTree.dfs(scapegoatTree.rt, v, _v); 
		//	for (auto &it : _v) cout << it << " ";
		//	cout << endl;
		}
		return 0;
	}
	return 0;
}
