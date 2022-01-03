#include <bits/stdc++.h>
using namespace std;

#define pii pair <int, int>
#define fi first
#define se second
const int N = 3e5 + 10;
int n, m, tot, q, h[510][510]; 
struct node {
	int x, y, w;
	node() {}
	node(int x, int y, int w) : x(x), y(y), w(w) {}
	bool operator < (const node &other) const {
		return w < other.w;
	}
}a[N];
inline int id(int x, int y) {
	return (x - 1) * m + y;
}
struct SEG {
	struct node {
		int ls, rs, fa, sze;
		node() {
			ls = rs = 0;
			fa = 0;
			sze = 1;
		}
	}t[N * 52];
	int rt[N], tot;
	void init() {
		tot = 0;
		memset(rt, 0, sizeof rt);
		t[0] = node();
	}
	void build(int &id, int l, int r) { 
		id = ++tot;
		if (l == r) {
			t[id] = node();
			t[id].fa = l;
			return;
		}
		int mid = (l + r) >> 1;
		build(t[id].ls, l, mid);
		build(t[id].rs, mid + 1, r);
	}
	void update(int &now, int pre, int l, int r, int pos, int fa) {
		int tmp = ++tot;
		if (l == r) {
			t[tmp] = node();
			t[tmp].fa = fa;
			t[tmp].sze = t[pre].sze;
			now = tmp; 
			return;
		}
		t[tmp].ls = t[pre].ls;
		t[tmp].rs = t[pre].rs;
		int mid = (l + r) >> 1;
		if (pos <= mid) update(t[tmp].ls, t[pre].ls, l, mid, pos, fa);
		else update(t[tmp].rs, t[pre].rs, mid + 1, r, pos, fa);
		now = tmp;
	}
	void add(int &now, int pre, int l, int r, int pos, int sze) {
		int tmp = ++tot;
		if (l == r) {
			t[tmp] = node();
			t[tmp].fa = t[pre].fa;
			t[tmp].sze = t[pre].sze + sze;
			now = tmp;
			return;
		}
		t[tmp].ls = t[pre].ls;
		t[tmp].rs = t[pre].rs;
		int mid = (l + r) >> 1;
		if (pos <= mid) add(t[tmp].ls, t[pre].ls, l, mid, pos, sze);
		else add(t[tmp].rs, t[pre].rs, mid + 1, r, pos, sze);
		now = tmp;
	}
	pii query(int now, int l, int r, int pos) {
		if (l == r) return pii(t[now].fa, t[now].sze);
		int mid = (l + r) >> 1;
		if (pos <= mid) return query(t[now].ls, l, mid, pos);
		else return query(t[now].rs, mid + 1, r, pos);
	}
}seg;

pii find(int k, int x) {
	pii pre = seg.query(seg.rt[k], 1, tot, x);
	if (pre.fi == x) {
		return pre;
	} else {
		return find(k, pre.fi);
	}
}
void join(int k, int x, int y) {
	pii fx = find(k, x), fy = find(k, y);
	if (fx.fi != fy.fi) {
		if (fx.se > fy.se) {
			swap(fx, fy);
		}
		seg.update(seg.rt[k], seg.rt[k], 1, tot, fx.fi, fy.fi);
		seg.add(seg.rt[k], seg.rt[k], 1, tot, fy.fi, fx.se);
	}
}
bool same(int k, int x, int y) {
	pii fx = find(k, x), fy = find(k, y);
//	cout << k << " " << x << " " << fx.fi << " " << y << " " << fy.fi << endl;
	return fx.fi == fy.fi; 
}
int Move[][2] = {
	0, 1,
	0,-1,
	1, 0,
   -1, 0,
};
bool ok(int x, int y) {
	if (x < 1 || x > n || y < 1 || y > m) return 0;
	return 1;
}
void addedge(int k, int x, int y, int w) {
	for (int i = 0; i < 4; ++i) {
		int nx = x + Move[i][0];
		int ny = y + Move[i][1];
		if (ok(nx, ny) && h[nx][ny] <= w) {
			join(k, id(x, y), id(nx, ny));  
		}
	}
}

int main() {
	while (scanf("%d%d%d", &n, &m, &q) != EOF) {
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= m; ++j) {
				scanf("%d", h[i] + j);
				a[id(i, j)] = node(i, j, h[i][j]); 
			}
		}
		tot = n * m;
		a[0].w = 0; 
		sort(a + 1, a + 1 + tot);
	//	for (int i = 1; i <= tot; ++i) printf("%d %d\n", i, a[i].w);
		seg.init(); seg.build(seg.rt[0], 1, tot);
		for (int i = 1; i <= tot; ++i) {
			seg.rt[i] = seg.rt[i - 1];
			addedge(i, a[i].x, a[i].y, a[i].w);
		}
		for (int _q = 1, x1, y1, x2, y2; _q <= q; ++_q) {
			scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
			if (x1 == x2 && y1 == y2) {
				printf("%d\n", h[x1][y1]);
				continue;
			}
			int l = 0, r = tot, res = r;
			while (r - l >= 0) {
				int mid = (l + r) >> 1;
				if (same(mid, id(x1, y1), id(x2, y2))) { 
					res = mid;
					r = mid - 1;
				} else {
					l = mid + 1;
				}
			}
			printf("%d\n", a[res].w);
		}
	}
	return 0;
}
