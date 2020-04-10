#include <bits/stdc++.h>
using namespace std;
#define dbg(x...) do { cout << "\033[32;1m" << #x << " -> "; err(x); } while (0) 
void err() { cout << "\033[39;0m" << endl; } 
template <class T, class... Ts> void err(const T& arg, const Ts&... args) { cout << arg << ' '; err(args...); }
typedef long long ll;
const int N = 2e5 + 10;
int n, q, a[N];

struct ScapegoatTree {
	#define ls(o) t[o].ls
	#define rs(o) t[o].rs
	const double alpha = 0.70;
	struct node {
		int ls, rs, sz, valid;
		bool del;
		ll v, sum, lazy; 
		node() {}
		void init(int x) { ls = rs = 0; sum = v = x; lazy = 0; sz = valid = 1; del = 0; } 
		void up(ll _lazy) {
			v += _lazy;
			sum += _lazy * valid;
			lazy += _lazy;
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
		t[o].sum = t[ls(o)].sum + t[rs(o)].sum + !t[o].del * t[o].v;
	}
	void pushdown(int o) {
		ll &lazy = t[o].lazy;
		if (ls(o)) t[ls(o)].up(lazy);
		if (rs(o)) t[rs(o)].up(lazy);
		lazy = 0;
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
		dfs(o, v);
		o = build(v, 0, (int)v.size());
	}
	//在第id个位置插入x
	void insert(int &o, int id, int x) {
		if (!o) {
			o = newnode(x);
			return;
		}
		pushdown(o);
		t[o].sz++; t[o].valid++; t[o].sum += x; 
		if (id <= t[ls(o)].valid + !t[o].del)
			insert(ls(o), id, x);
		else 
			insert(rs(o), id - t[ls(o)].valid - !t[o].del, x);
		if (bad(o)) reBuild(o);
		return;
	}
	void update(int o, int l, int r, int x) {
		if (!o) return;
		pushdown(o);
		if (l <= 1 && t[o].valid <= r) {
			t[o].up(x); 
		} else {
			if (l <= t[ls(o)].valid) 
				update(ls(o), l, r, x);
			if (r > t[ls(o)].valid + !t[o].del)
				update(rs(o), l - t[ls(o)].valid - !t[o].del, r - t[ls(o)].valid - !t[o].del, x);
			if (!t[o].del && l <= t[ls(o)].valid + 1 && r >= t[ls(o)].valid + 1)  
				t[o].v += x;
			pushup(o);
		}
	}
	ll query(int o, int l, int r) {
		if (!o) return 0;
		pushdown(o);
		if (l <= 1 && t[o].valid <= r) {
			return t[o].sum;
		} else {
			ll ans = 0;
			if (l <= t[ls(o)].valid) 
				ans += query(ls(o), l, r);
			if (r > t[ls(o)].valid + !t[o].del) 
				ans += query(rs(o), l - t[ls(o)].valid - !t[o].del, r - t[ls(o)].valid - !t[o].del);
			if (!t[o].del && l <= t[ls(o)].valid + 1 && r >= t[ls(o)].valid + 1)
				ans += t[o].v;
			return ans;
		}
	}
}scapegoatTree;

int main() {
	int n;
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) scanf("%d", a + i);
	scapegoatTree.init();
	for (int i = 1; i <= n; ++i) scapegoatTree.insert(scapegoatTree.rt, i, a[i]);
	scanf("%d", &q);
	while(q--) {
		int opt, l, r, v, pos;
		scanf("%d", &opt);
		if (opt == 1) {
			scanf("%d", &pos);
			scapegoatTree.insert(scapegoatTree.rt, pos, 0);
		} else if (opt == 2) {
			scanf("%d%d%d", &l, &r, &v);
			scapegoatTree.update(scapegoatTree.rt, l, r, v);
		} else {
			scanf("%d%d", &l, &r);
			printf("%lld\n", scapegoatTree.query(scapegoatTree.rt, l, r));
		}
	}
	return 0;
}
