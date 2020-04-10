#include <bits/stdc++.h>
using namespace std;
typedef int db;
const int N = 1e6 + 10;
const int DIM = 2;
const int K = 2;
const db INF = 0x3f3f3f3f;

struct Point {
	db x[DIM]; 
	void scan() { for (int i = 0; i < K; ++i) scanf("%d", x + i); }
	db dis(const Point &b) const {
		db res = 0;
		for (int i = 0; i < K; ++i)
			res += abs(x[i] - b.x[i]);  
		return res;
	}
}s[N]; int cntS; 

struct KDTree {
	#define alpha 0.725
	struct cmpx {
		int div;
		cmpx(int div = 0) : div(div) {} 
		bool operator () (const int &a, const int &b) {
			return s[a].x[div] < s[b].x[div];
		}
	};
	bool cmp(const int &a, const int &b, const int &div) { return s[a].x[div] <= s[b].x[div]; }
	struct Node {
		int ls, rs, div;
		db Min[DIM], Max[DIM];
		int sze;
	}t[N]; 
	int root, g[N];
	db ans;
	void init() { root = 0; }
	void print(int o) {
	    if (!o) return;
	    print(t[o].ls);
	    g[++*g] = o;
	    print(t[o].rs);
	}
	void pushup(int o) {
	    t[o].sze = t[t[o].ls].sze + t[t[o].rs].sze + 1;
		for (int i = 0; i < K; ++i) {
			t[o].Min[i] = t[o].Max[i] = s[o].x[i];
		}
	    if (t[o].ls) {
			for (int i = 0; i < K; ++i) {
				t[o].Min[i] = min(t[o].Min[i], t[t[o].ls].Min[i]);
				t[o].Max[i] = max(t[o].Max[i], t[t[o].ls].Max[i]);
			}
		}
	    if (t[o].rs) {
			for (int i = 0; i < K; ++i) {
				t[o].Min[i] = min(t[o].Min[i], t[t[o].rs].Min[i]);
				t[o].Max[i] = max(t[o].Max[i], t[t[o].rs].Max[i]);
			}
		}
	}
	int build(int l, int r) {
	    if (l > r) return 0;
	    int mid = (l + r) >> 1;
	    double ave[2] = {0}, vax[2] = {0};
	    for (int i = l; i <= r; i++) 
			for (int j = 0; j < K; ++j)
				ave[j] += s[g[i]].x[j];
		for (int i = 0; i < K; ++i) ave[i] /= (r - l + 1);
	    for (int i = l; i <= r; i++)
			for (int j = 0; j < K; ++j)
				vax[j] += (s[g[i]].x[j] - ave[j]) * (s[g[i]].x[j] - ave[j]);
		int div = 0;
		for (int i = 1; i < K; ++i) {
			if (vax[i] > vax[div])
				div = i;
		}
		nth_element(g + l, g + mid, g + r + 1, cmpx(div));
		int o = g[mid];
		t[o].div = div;
		t[o].ls = build(l, mid - 1);
		t[o].rs = build(mid + 1, r);
	    pushup(o);
	    return o;
	}
	void rebuild(int &o) {
	    *g = 0;
		print(o);
	    o = build(1, *g);
	}
	bool bad(int o) { return alpha * t[o].sze <= (double)max(t[t[o].ls].sze, t[t[o].rs].sze); } 
	void insert(int &o, int v) {
	    if (!o) {
	        o = v;
	        pushup(o);
	        return;
	    }
		if (cmp(v, o, t[o].div))
			insert(t[o].ls, v);
		else
			insert(t[o].rs, v);
	    pushup(o);
	    if (bad(o)) rebuild(o);
	}
	db calc(int o, Point &e) {
		if (!o) return INF;
	    db res = 0;
		for (int i = 0; i < K; ++i) {
			if (t[o].Min[i] > e.x[i])
				res += abs(t[o].Min[i] - e.x[i]);
			if (t[o].Max[i] < e.x[i])
				res += abs(t[o].Max[i] - e.x[i]);
		}
		return res;
	}
	void query(int o, Point &e) {
	    if (!o) return;
		ans = min(ans, e.dis(s[o])); 
		db dl = calc(t[o].ls, e), dr = calc(t[o].rs, e);
		if (dl < dr) {
			if (dl < ans) query(t[o].ls, e);
			if (dr < ans) query(t[o].rs, e);
		} else {
			if (dr < ans) query(t[o].rs, e);
			if (dl < ans) query(t[o].ls, e);
		}
	}
	db query(Point &e) {
		ans = INF;
		query(root, e);
		return ans;
	}
}kdTree;

int main() {
	int n, q, op;
    Point e;
	cntS = 0;
	scanf("%d%d", &n, &q); 
	for (int i = 1; i <= n; ++i) {
		++cntS;
		s[cntS].scan();
		kdTree.g[i] = i;
	}
	kdTree.root = kdTree.build(1, n);
	while (q--) {
		scanf("%d", &op);
		if (op == 1) {
			++cntS; s[cntS].scan();
			kdTree.insert(kdTree.root, cntS);
		} else {
			e.scan();
			printf("%d\n", kdTree.query(e));
		}
	}
	return 0;
}
