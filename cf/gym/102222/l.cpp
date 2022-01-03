#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pii pair <int, int>
#define fi first
#define se second
const int N = 1e5 + 10;
int n, a[N];
map <int, int> last;

struct SEG {
	struct node {
		int Min, sum, lazy;
		node() {
			Min = 0;
			sum = lazy = 0;
		}
		node(int Min, int sum, int lazy) : Min(Min), sum(sum), lazy(lazy) {}
		void add(int x) {
			Min += x;
			lazy += x;
		}
		node operator + (const node &other) const {
			node res = node();
			res.Min = min(Min, other.Min);
			if (res.Min == Min) res.sum += sum;
			if (res.Min == other.Min) res.sum += other.sum;
			return res;
		}
	}t[N << 2], res;
	void build(int id, int l, int r) {
		t[id] = node();
		if (l == r) {
			t[id].sum = 1;
			return;	
		}
		int mid = (l + r) >> 1;
		build(id << 1, l, mid);
		build(id << 1 | 1, mid + 1, r);
		t[id] = t[id << 1] + t[id << 1 | 1];
	}
	void down(int id) {
		int &lazy = t[id].lazy;
		if (lazy) {
			t[id << 1].add(lazy);
			t[id << 1 | 1].add(lazy);
			lazy = 0;
		}
	}
	void update(int id, int l, int r, int ql, int qr, int v) {
		if (l >= ql && r <= qr) {
			t[id].add(v);
			return;
		}
		int mid = (l + r) >> 1;
		down(id);
		if (ql <= mid) update(id << 1, l, mid, ql, qr, v);
		if (qr > mid) update(id << 1 | 1, mid + 1, r, ql, qr, v);
		t[id] = t[id << 1] + t[id << 1 | 1];
	}
	void query(int id, int l, int r, int ql, int qr) {
		if (l >= ql && r <= qr) {
			res = res + t[id];
			return;
		}
		int mid = (l + r) >> 1;
		down(id);
		if (ql <= mid) query(id << 1, l, mid, ql, qr);
		if (qr > mid) query(id << 1 | 1, mid + 1, r, ql, qr);
	}
}seg;

int main() {
	int T; scanf("%d", &T);
	for (int kase = 1; kase <= T; ++kase) {
		printf("Case #%d: ", kase);
		scanf("%d", &n);
		for (int i = 1; i <= n; ++i) scanf("%d", a + i);
		stack <pii> sup, sdown;
		sup.push(pii(0, 0));
	   	sdown.push(pii(1e9, 0));
		ll res = 0;
		seg.build(1, 1, n);
		last.clear();
		for (int i = 1; i <= n; ++i) {
			while (a[i] < sup.top().fi) {
				pii tmp = sup.top(); sup.pop(); 
				seg.update(1, 1, n, sup.top().se + 1, tmp.se, tmp.fi); 
			}
			seg.update(1, 1, n, sup.top().se + 1, i, -a[i]);
			sup.push(pii(a[i], i));
			while (a[i] > sdown.top().fi) {
				pii tmp = sdown.top(); sdown.pop();
				seg.update(1, 1, n, sdown.top().se + 1, tmp.se, -tmp.fi);
			}
			seg.update(1, 1, n, sdown.top().se + 1, i, a[i]);
			sdown.push(pii(a[i], i));
			seg.update(1, 1, n, last[a[i]] + 1, i, -1);
			last[a[i]] = i;
			seg.res = SEG::node();
			seg.query(1, 1, n, 1, i);
			res += (seg.res.Min == -1) * seg.res.sum;
		}	
		printf("%lld\n", res);
	}
	return 0;
}
