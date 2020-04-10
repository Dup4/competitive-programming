#include <bits/stdc++.h>
using namespace std;
const int INF = 0x3f3f3f3f;
int n, m;

template <typename CatTreeItem, CatTreeItem base> 
struct CatTree {
	int lev, sz;
	vector <CatTreeItem> v;  
	vector <vector<CatTreeItem>> t;
	//确立两数运算规则
	CatTreeItem op(const CatTreeItem &a, const CatTreeItem &b) { return max(a, b); }
	int log2Up(int n) {  
	    int res = 0;
		while ((1 << res) < n) ++res; 
		return res; 
	}
	void build(int id, int l, int r) {
		if (l == r) return;
		int mid = (l + r) >> 1;
		t[id][mid] = v[mid];
		for (int i = mid - 1; i >= l; --i) t[id][i] = op(t[id][i + 1], v[i]);
		if (mid < r) {
			t[id][mid + 1] = v[mid + 1];
			for (int i = mid + 2; i <= r; ++i) t[id][i] = op(t[id][i - 1], v[i]);
		}
		build(id + 1, l, mid);
		build(id + 1, mid + 1, r);
	}
	//下标从0开始
	CatTree(const vector<CatTreeItem> &a) {
		int n = a.size();
		lev = __builtin_clz(n);
		sz = 1 << (31 - lev);
		if (n != sz) { sz <<= 1; --lev; }
		v = vector<CatTreeItem>(sz, base);
		t = vector <vector<CatTreeItem>>(log2Up(n) + 1, vector <CatTreeItem>(sz, base));
	    for (int i = 0; i < n; ++i) v[i] = a[i];
		build(0, 0, sz - 1);
	}
	CatTreeItem query(int l, int r) {
		if (l == r) return v[l];
		int id = __builtin_clz(l ^ r) - lev - 1;
		return op(t[id][l], t[id][r]); 
	}
};

int main() {
	while(scanf("%d%d", &n, &m) != EOF) {
		vector <int> a(n);
		for (int i = 0, x; i < n; ++i) {
			scanf("%d", &x);
			a[i] = x;
		}
		CatTree <int, -INF> catTree(a);
		int l, r;
		while (m--) {
			scanf("%d%d", &l, &r);
			printf("%d\n", catTree.query(l - 1, r - 1));
		}
	}
	return 0;
}
