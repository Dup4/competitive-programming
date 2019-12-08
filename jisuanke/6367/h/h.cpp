#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define dbg(x...) do { cout << "\033[32;1m" << #x << " -> "; err(x); } while (0)
void err() { cout << "\033[39;0m" << endl; }
template<class T, class... Ts> void err(const T& arg, const Ts&... args) { cout << arg << " "; err(args...); }
const int N = 2e5 + 10;
int n, m, q, a[N], L[510][510], R[510][510], cl, cr;
inline int lowbit(int x) { return x & -x; }
struct SEG {
	struct node {
		int ls, rs;
		ll sum;
		void init() { ls = rs = sum = 0; }
	}t[N * 80];
	int rt[N], tot;
	ll res;
	int newnode() {
		++tot;
		t[tot].init();
		return tot;
	}
	void init() { memset(rt, 0, sizeof rt); tot = 0; }
	void update(int &rt, int l, int r, int pos, int v) {
		if (!rt) rt = newnode();
		t[rt].sum += v;
		if (l == r) return;
		int mid = (l + r) >> 1;
		if (pos <= mid) update(t[rt].ls, l, mid, pos, v);
		else update(t[rt].rs, mid + 1, r, pos, v);
	}
	void update(int x, int pos, int v) {
		for (; x <= n; x += lowbit(x)) {
			update(rt[x], 1, m, pos, v); 
		}
	}
	void query(int dep, int l, int r, int ql, int qr) {
	    if (ql > qr) return;
		if (l >= ql && r <= qr) {
			for (int i = 1; i <= cl; ++i) res -= t[L[dep][i]].sum;
			for (int i = 1; i <= cr; ++i) res += t[R[dep][i]].sum;
			return;
		}	
		int mid = (l + r) >> 1;
		if (ql <= mid) {
			for (int i = 1; i <= cl; ++i) L[dep + 1][i] = t[L[dep][i]].ls;
			for (int i = 1; i <= cr; ++i) R[dep + 1][i] = t[R[dep][i]].ls;
			query(dep + 1, l, mid, ql, qr);
		} 
		if (qr > mid) {
			for (int i = 1; i <= cl; ++i) L[dep + 1][i] = t[L[dep][i]].rs;
			for (int i = 1; i <= cr; ++i) R[dep + 1][i] = t[R[dep][i]].rs;
			query(dep + 1, mid + 1, r, ql, qr);
		}
	}
}seg;

int main() {
	m = 2e5;
	while (scanf("%d%d", &n, &q) != EOF) {
		for (int i = 1; i <= n; ++i) scanf("%d", a + i);
		seg.init();
		for (int i = 1; i <= n; ++i) {
			seg.update(i, a[i], a[i]); 
		}
		int op, x, y;
		for (int i = 1; i <= q; ++i) {
			scanf("%d%d%d", &op, &x, &y);
			if (op == 1) {
				seg.update(x, a[x], -a[x]);
				a[x] = y;
				seg.update(x, a[x], a[x]); 
			} else {
				--x;
				cl = cr = 0;
				for (int j = x; j; j -= lowbit(j)) {
					L[0][++cl] = seg.rt[j];
				}
				for (int j = y; j; j -= lowbit(j)) {
					R[0][++cr] = seg.rt[j];
				}
				ll l = -1, r = 0;
				while (1) {
					seg.res = 0;
					seg.query(0, 1, m, min(1ll * m + 1, l + 2), min(1ll * m, r + 1));
					ll tot = seg.res;
				//	dbg(i, tot, l + 2, r + 1);
					if (tot == 0) break;
					l = r;
					r += tot;
				}
				printf("%lld\n", r + 1);
			}
		}
	}
	return 0;
}
