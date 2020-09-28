#include <bits/stdc++.h>
using namespace std;

const int N = 1e4 + 10;
int n;
struct node {
	int l, r, w; 
	node() {}
	node(int l, int r, int w) : l(l), r(r), w(w) {}
	void scan() {
		scanf("%d%d", &l, &r);
	}
}a[N];

bool cross(int x, int y, int l, int r) {
	int nl = max(x, l);
	int nr = min(y, r);
	return nl <= nr;
}

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		for (int i = 1; i <= n; ++i) a[i].scan();
		node f = node(a[1].l, a[1].r, 0);
		for (int i = 2, l, r; i <= n; ++i) {
			l = a[i].l, r = a[i].r;
			if (cross(l, r, f.l, f.r)) {
				f = node(max(l, f.l), min(r, f.r), f.w); 
			} else {
				if (r < f.l) { 
					int dis = f.l - r;
					if (dis % 2 == 0) {
						f = node(r, r, f.w + dis / 2);
					} else {
						f = node(max(r - 1, l), r, f.w + dis / 2 + 1); 
					}
				} else if (f.r < l) {
					int dis = l - f.r;
					if (dis % 2 == 0) {
						f = node(l, l, f.w + dis / 2);
					} else {
						f = node(l, min(l + 1, r), f.w + dis / 2 + 1);
					}
				}
			}
		}
		printf("%d\n", f.w);
	}
	return 0;
}
