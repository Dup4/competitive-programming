#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e5 + 10;

struct ScapegoatTree {
	#define ls(o) t[o].ls
	#define rs(o) t[o].rs
	const double alpha = 0.7;
	struct node {
		int ls, rs, v, sz, valid;
		bool del;
		node() {}
		void init(int x) { ls = rs = 0; v = x; sz = valid = 1; del = 0; }
	}t[N << 2];
	int tot = 0, rt = 0;
	void init() { rt = 0; tot = 0; }
	int newnode(int x = 0) { ++tot; t[tot].init(x); return tot; } 
	bool bad(int o) {
		return (double)t[ls(o)].sz > alpha * t[o].sz || (double)t[rs(o)].sz > alpha * t[o].sz;
	}
	void pushup(int o) {
		t[o].sz = t[ls(o)].sz + t[rs(o)].sz + !t[o].del;
		t[o].valid = t[ls(o)].valid + t[rs(o)].valid + !t[o].del;
	}
	void dfs(int o, vector<int> &v) {
		if (!o) return;
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
	void insert(int &o, int x) {
		if (!o) {
			o = newnode(x);
			return;
		}
		t[o].sz++; t[o].valid++;
		if (x >= t[o].v) insert(rs(o), x);
		else insert(ls(o), x);
		if (bad(o)) reBuild(o);
		return;
	}
	int getRank(int o, int x) {
		int ans = 1;
		while (o) {
			if (t[o].v >= x) o = ls(o);
			else {
				ans += t[ls(o)].valid + !t[o].del;
				o = rs(o);
			}
		}
		return ans;
	}
	int findKth(int o, int x) {
		while (o) {
			if (!t[o].del && t[ls(o)].valid + 1 == x) { return t[o].v; }
			if (t[ls(o)].valid >= x) o = ls(o); 
			else {
				x -= t[ls(o)].valid + !t[o].del;
				o = rs(o);
			}
		}
		//找不到
		return -1;
	}
	void del(int o, int Rank) {
		if (!t[o].del && Rank == t[ls(o)].valid + 1) {
			t[o].del = 1;
			--t[o].valid;
			return;
		}
		--t[o].valid;
		if (Rank <= t[ls(o)].valid + !t[o].del) del(ls(o), Rank);
		else del(rs(o), Rank - t[ls(o)].valid - !t[o].del);
	}
}scapegoatTree;

int main() {
	int n;
	scanf("%d", &n);
	scapegoatTree.init();
	while(n--) {
		int opt, x;
		scanf("%d%d", &opt, &x);
		if(opt==1) scapegoatTree.insert(scapegoatTree.rt, x);
		if(opt==2) scapegoatTree.del(scapegoatTree.rt, scapegoatTree.getRank(scapegoatTree.rt, x));
		if(opt==3) printf("%d\n", scapegoatTree.getRank(scapegoatTree.rt, x));
		if(opt==4) printf("%d\n", scapegoatTree.findKth(scapegoatTree.rt, x));
		if(opt==5) printf("%d\n", scapegoatTree.findKth(scapegoatTree.rt, scapegoatTree.getRank(scapegoatTree.rt, x) - 1));
		if(opt==6) printf("%d\n", scapegoatTree.findKth(scapegoatTree.rt, scapegoatTree.getRank(scapegoatTree.rt, x + 1)));
	}
	return 0;
}
