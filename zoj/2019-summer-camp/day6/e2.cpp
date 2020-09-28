#include <bits/stdc++.h>
using namespace std;

#define N 5010
int n, m, t, a[N], b[N], H[N << 1];
// 2 表示是第一个数
// 3 表示当前数等于之前那个数
// 0 表示当前数小于之前那个数
// 1 表示当前数大于之前那个数 
int g[N][4], f[4];      

struct SEG {
	struct node {
		int Max, ls, rs;
		node () {
			Max = 0;
			ls = rs = -1;  
		}
		node (int Max, int ls, int rs) : Max(Max), ls(ls), rs(rs) {}
		void up(node other) {
			Max = max(Max, other.Max);
		}
	}t[N * 10];
	int tot, rt;
	void init() {
		tot = 0;
		rt = -1;
		t[0] = node();
	}
	void update(int &now, int l, int r, int pos, int v) {
		if (now == -1) {
			now = ++tot; 
			t[now] = node();
		}
		if (l == r) {
			t[now].Max = max(t[now].Max, v);
			return;
		}
		int mid = (l + r) >> 1;
		if (pos <= mid) update(t[now].ls, l, mid, pos, v);
		else update(t[now].rs, mid + 1, r, pos, v);
		int ls = t[now].ls, rs = t[now].rs;
		if (ls != -1) t[now].up(t[ls]);
		if (rs != -1) t[now].up(t[rs]);
	}
	int query(int now, int l, int r, int ql, int qr) {
		if (ql > qr || now == -1) return 0;
		if (l >= ql && r <= qr) return t[now].Max;
		int mid = (l + r) >> 1;
		int res = 0;
		if (ql <= mid) res = max(res, query(t[now].ls, l, mid, ql, qr));
		if (qr > mid) res = max(res, query(t[now].rs, mid + 1, r, ql, qr));
		return res;
	}
}seg[2];

int get(int x) {
	return lower_bound(H + 1, H + 1 + t, x) - H;
}

int main() {
	scanf("%d", &n);
	t = 0;
	for (int i = 1; i <= n; ++i) {
		scanf("%d", a + i);
	}
	scanf("%d", &m);
	for (int i = 1; i <= m; ++i) {
		scanf("%d", b + i);
		H[++t] = b[i];
	}
	sort(H + 1, H + 1 + t);
	t = unique(H + 1, H + 1 + t) - H - 1;
	int tmp = 0;
	for (int i = 1; i <= n; ++i) {
		int pos = get(a[i]);
		if (H[pos] == a[i]) {
			a[++tmp] = pos;
		}	
	}
	n = tmp;
	for (int i = 1; i <= m; ++i) b[i] = get(b[i]); 
	int res = 0; 
	for (int i = 1; i <= n; ++i) {
		seg[0].init();
		seg[1].init();
		for (int j = 1; j <= m; ++j) {
			for (int k = 0; k < 2; ++k) {
				f[k] = g[j][k];
			}
			if (a[i] == b[j]) {
				g[j][2] = 1;
				// 0 小于  1 大于
				for (int k = 0, x, l, r; k < 2; ++k) {
					switch(k) {
						case 0 :
							l = b[j] + 1, r = t;
							break;
						case 1 :
							l = 1, r = b[j] - 1;
							break;
					}
					x = seg[k].query(seg[k].rt, 1, t, l, r);
					g[j][k ^ 1] = max(g[j][k ^ 1], x + 1);
					if (g[j][3] < 2) {
						if (seg[k].query(seg[k].rt, 1, t, b[j], b[j])) {
							g[j][3] = 2;
						}
					}
				}
			}
			for (int k = 0; k < 4; ++k) {
				res = max(res, g[j][k]);
			}
			for (int k = 0; k < 2; ++k) {
				if (f[k] > 0) {
					int x = f[k];
					if (f[2] > 0) {
						x = max(x, f[2]);
					}
					seg[k].update(seg[k].rt, 1, t, b[j], x);
				}
			}
		}
	}	
	printf("%d\n", res);
	return 0;
}
