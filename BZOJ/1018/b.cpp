#include <bits/stdc++.h>
using namespace std;

#define N 200010
#define pii pair <int, int>
#define fi first
#define se second
int n, m, q;
map <pii, int> mp;  
pii qrr[N]; int vis[N], res[N];
int pre[N], sz[N], Top;
struct node {
	int x, y, w;
	node () {}
	node (int x, int y, int w) : x(x), y(y), w(w) {}
};
node Sta[N << 1];
int find(int x) {
	if (pre[x] == 0) {
		return x;
	}
	int y = find(pre[x]);
	if (y != pre[x]) {
		Sta[++Top] = node(x, pre[x], -1); 
	}
	return pre[x] = y; 
}

struct SEG {
	vector < vector <pii> > a;
	void init(int n) {
		a.resize(n * 4 + 10);
	}
	void ins(int id, int l, int r, int ql, int qr, pii P) {
		if (l >= ql && r <= qr) {
			a[id].push_back(P);
			return;
		}
		int mid = (l + r) >> 1;
		if (ql <= mid) ins(id << 1, l, mid, ql, qr, P);
		if (qr > mid) ins(id << 1 | 1, mid + 1, r, ql, qr, P);
	}
	void work(int id, int l, int r) {
		int tp = Top;
		for (int i = 0, sze = (int)a[id].size(); i < sze; ++i) {
			pii it = a[id][i];
			int x = find(it.fi), y = find(it.se);
			if (x != y) {
				if (sz[x] > sz[y]) {
					swap(x, y);
				}
				Sta[++Top] = node(x, y, sz[x]);
				sz[y] += sz[x];
				pre[x] = y;
			}
		}
		
		if (l == r) {
			if (vis[l]) {
				int x = qrr[l].fi, y = qrr[l].se;
				if (find(x) == find(y)) {
					res[l] = 1;
				} else {
					res[l] = 0;
				}
			}
		} else {
			int mid = (l + r) >> 1;
			work(id << 1, l, mid);
			work(id << 1 | 1, mid + 1, r);
		}
		while (Top != tp) {
			int x = Sta[Top].x, y = Sta[Top].y, w = Sta[Top].w; --Top;
			if (w == -1) {
				pre[x] = y;
			} else {
				sz[y] -= w;
				pre[x] = 0;
			}
		}
	}
}seg;

void init() {
	mp.clear();
	m = 0; Top = 0;
	memset(vis, 0, sizeof vis);
	seg.init(100000);
	for (int i = 1; i <= n * 2; ++i) {
		pre[i] = 0;
		sz[i] = 1;
	}
	q = 100000;
}
int main() {
	while (scanf("%d", &n) != EOF) {
		init();
		char op[10]; int r[2], c[2], x, y;
		while (1) {
			++m; 
			scanf("%s", op);
			if (op[0] == 'E') {
				break;
			}
			scanf("%d%d%d%d", r, c, r + 1, c + 1);
			x = (r[0] - 1) * n + c[0];
			y = (r[1] - 1) * n + c[1];
			if (x > y) {
				swap(x, y);
			}
			switch(op[0]) {
				case 'O' :
					if (mp.find(pii(x, y)) == mp.end()) {
						mp[pii(x, y)] = m;
					}	
					break;
				case 'C' :
					if (mp.find(pii(x, y)) != mp.end()) {
						seg.ins(1, 1, q, mp[pii(x, y)], m - 1, pii(x, y));	
						mp.erase(pii(x, y));
					}	
					break;
				case 'A' :
					vis[m] = 1;
					qrr[m] = pii(x, y); 
					break;
				default :
					assert(0);
			}
		}
		for (map <pii, int> :: iterator it = mp.begin(); it != mp.end(); ++it) { 
			seg.ins(1, 1, q, (*it).se, q, (*it).fi); 
		}
		seg.work(1, 1, q);
		for (int i = 1; i <= m; ++i) if (vis[i]) {
			puts(res[i] ? "Y" : "N");
		}
	}
	return 0;
}
