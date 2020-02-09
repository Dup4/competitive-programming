#include <bits/stdc++.h>
using namespace std;
#define pII pair<int, int>
#define fi first
#define se second
#define SZ(x) (int(x.size()))
const int N = 1e5 + 10;
int n, m, T, ans[N]; 

struct UFS {
	struct node {
		int fa, sze, loc;
		void init() { fa = 0; sze = 1; loc = 0; }
	}t[N];
	pair<int, node> Back[N]; int T;
	void init(int n) { for (int i = 1; i <= n; ++i) t[i].init(); T = 0; }
	pII find(int x) {
		if (t[x].fa == 0) return pII(x, t[x].loc);
		else {
			pII tmp = find(t[x].fa);
			tmp.se ^= t[x].loc;
			return tmp;
		}
	}
	bool merge(int x, int y) {
		pII fx = find(x), fy = find(y);
		if (fx.fi == fy.fi && fx.se == fy.se) return false;
		if (fx.fi != fy.fi) {
			if (t[fx.fi].sze > t[fy.fi].sze) swap(fx, fy);
			Back[++T] = make_pair(fx.fi, t[fx.fi]);
			Back[++T] = make_pair(fy.fi, t[fy.fi]);
			if (fx.se == fy.se) t[fx.fi].loc ^= 1;
			t[fx.fi].fa = fy.fi;
			t[fy.fi].sze += t[fx.fi].sze;
		}
		return true;
	}
	void rollback(int _T) {
		while (T != _T) {
			t[Back[T].fi] = Back[T].se;
			--T;
		}
	}
}ufs;

struct SEG {
	vector < vector < pII> > t; 
	void init(int n) { t.resize(n * 4 + 10); }
	//以时间轴建线段树
	//考虑一个点存在的时间区间为[ql, qr]，那么每个[l, l]这样的区间就是表示第l次操作后的答案
	void ins(int id, int l, int r, int ql, int qr, pII P) {
		if (l >= ql && r <= qr) {
			t[id].push_back(P);
			return;
		}	
		int mid = (l + r) >> 1;
		if (ql <= mid) ins(id << 1, l, mid, ql, qr, P);
		if (qr > mid) ins(id << 1 | 1, mid + 1, r, ql, qr, P);
	}
	void gao(int id, int l, int r, int ok) {
		int T = ufs.T; 
		for (int i = 0; i < SZ(t[id]); ++i) {
			ok &= ufs.merge(t[id][i].fi, t[id][i].se);
		}
		if (l == r) {
			ans[l] = ok;
		} else {
			int mid = (l + r) >> 1;
			gao(id << 1, l, mid, ok);
			gao(id << 1 | 1, mid + 1, r, ok);
		}
		ufs.rollback(T);
	}
}seg;

int main() {
	while (scanf("%d%d%d", &n, &m, &T) != EOF) {
		seg.init(T); ufs.init(n);
		for (int i = 1, u, v, st, ed; i <= m; ++i) {
			scanf("%d%d%d%d", &u, &v, &st, &ed);
			++st;
			seg.ins(1, 1, T, st, ed, pII(u, v));
		}
		seg.gao(1, 1, T, 1);
		for (int i = 1; i <= T; ++i) puts(ans[i] ? "Yes" : "No");
	}
	return 0;
}
