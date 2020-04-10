#include <bits/stdc++.h>
using namespace std;
typedef int db;
const int N = 2e5 + 10;
const int DIM = 2;
const int K = 2;

struct Point {
	db x[DIM]; int v;  
	bool In(db *Min, db *Max) {
		for (int i = 0; i < K; ++i) {
			if (x[i] < Min[i] || x[i] > Max[i])
				return 0;
		}
		return 1;
	}
}s[N]; int cntS; 

struct KDTree {
	static constexpr double alpha = 0.75;
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
		int sze, sum;
		bool In(db *_Min, db *_Max) {
			for (int i = 0; i < K; ++i) {
				if (_Min[i] > Min[i] || _Max[i] < Max[i])
					return 0;
			}
			return 1;
		}
		bool Out(db *_Min, db *_Max) {
			for (int i = 0; i < K; ++i) {
				if (_Max[i] < Min[i] || _Min[i] > Max[i])
					return 1;
			}
			return 0;
		}
	}t[N]; 
	int root, g[N];
	void init() { root = 0; }
	void print(int o) {
	    if (!o) return;
	    print(t[o].ls);
	    g[++*g] = o;
	    print(t[o].rs);
	}
	void pushup(int o) {
	    t[o].sze = t[t[o].ls].sze + t[t[o].rs].sze + 1;
	    t[o].sum = t[t[o].ls].sum + t[t[o].rs].sum + s[o].v; 
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
	int query(int o, db *Min, db *Max) {
		if (!o || t[o].Out(Min, Max)) return 0;
		if (t[o].In(Min, Max)) return t[o].sum;
	    int res = 0;
		if (s[o].In(Min, Max)) res += s[o].v;
	    return query(t[o].ls, Min, Max) + query(t[o].rs, Min, Max) + res;
	}
}kdTree;

int main() {
	int n, op, ans = 0;
	db Min[DIM], Max[DIM];	
    scanf("%d", &n);
    while (scanf("%d", &op) != EOF) {
        if (op == 1) {
			++cntS;
            scanf("%d%d%d", &s[cntS].x[0], &s[cntS].x[1], &s[cntS].v);
            s[cntS].x[0] ^= ans;
            s[cntS].x[1] ^= ans;
            s[cntS].v ^= ans;
            kdTree.insert(kdTree.root, cntS);
        }
        if (op == 2) {
			for (int i = 0; i < K; ++i) scanf("%d", Min + i), Min[i] ^= ans;
			for (int i = 0; i < K; ++i) scanf("%d", Max + i), Max[i] ^= ans;
            printf("%d\n", ans = kdTree.query(kdTree.root, Min, Max));
        }
        if (op == 3) break;
    }
	return 0;
}
