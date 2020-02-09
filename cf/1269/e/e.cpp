#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define dbg(x...) do { cout << "\033[32;1m" << #x << " -> "; err(x); } while (0) 
void err() { cout << "\033[39;0m" << endl; } 
template <class T, class... Ts> void err(const T& arg, const Ts&... args) { cout << arg << ' '; err(args...); }
const int N = 2e5 + 10;
int n, a[N], b[N]; ll f[N]; 
ll calc(ll x) {
	return x * (x + 1) / 2;
}

struct SEG {
	struct node {
		int num; ll sum;
		node() { num = sum = 0; }
		node operator + (const node &other) const {
			node res = node();
			res.num = num + other.num;
			res.sum = sum + other.sum;
			return res;
		}
	}t[N << 2], res;
	void build(int id, int l, int r) { 
		t[id] = node();
		if (l == r) return;
		int mid = (l + r) >> 1;
		build(id << 1, l, mid);
		build(id << 1 | 1, mid + 1, r);
	}
	void update(int id, int l, int r, int pos) {
		if (l == r) {
			t[id].num = 1;
			t[id].sum = pos;
			return;
		}
		int mid = (l + r) >> 1;
		if (pos <= mid) update(id << 1, l, mid, pos);
		else update(id << 1 | 1, mid + 1, r, pos);
		t[id] = t[id << 1] + t[id << 1 | 1];
	}
	void query(int id, int l, int r, int ql, int qr) {
		if (ql > qr) return;
		if (l >= ql && r <= qr) {
			res = res + t[id];
			return;
		}
		int mid = (l + r) >> 1;
		if (ql <= mid) query(id << 1, l, mid, ql, qr);
		if (qr > mid) query(id << 1 | 1, mid + 1, r, ql, qr);
	}
	int query1(int id, int l, int r, int k) {
		if (l == r) return l;
		int mid = (l + r) >> 1;
		if (t[id << 1].num >= k) return query1(id << 1, l, mid, k);
		else return query1(id << 1 | 1, mid + 1, r, k - t[id << 1].num);
	}
}seg;

int main() {
	while (scanf("%d", &n) != EOF) {
		for (int i = 1; i <= n; ++i) {
			scanf("%d", a + i);
			b[a[i]] = i;
		}
		memset(f, 0, sizeof f);
		seg.build(1, 1, n);
		f[0] = 0;
		for (int i = 1; i <= n; ++i) {
			f[i] = f[i - 1];
			seg.res = SEG::node();
			seg.query(1, 1, n, b[i] + 1, n); 
			f[i] += seg.res.num;
			seg.update(1, 1, n, b[i]);
		}
		seg.build(1, 1, n);
		for (int i = 1; i <= n; ++i) {
			seg.update(1, 1, n, b[i]);	
			if (i > 1) {
				int pos = seg.query1(1, 1, n, (i + 1) / 2);
				seg.res = SEG::node();
				seg.query(1, 1, n, 1, pos - 1);
				f[i] -= seg.res.sum;
				f[i] += 1ll * seg.res.num * pos;
				f[i] -= calc(seg.res.num);
				seg.res = SEG::node();
				seg.query(1, 1, n, pos + 1, n);
				f[i] += seg.res.sum;
				f[i] -= 1ll * seg.res.num * pos;
				f[i] -= calc(seg.res.num);
			}
		}
		for (int i = 1; i <= n; ++i)
			printf("%lld%c", f[i], " \n"[i == n]);
	}
	return 0;
}
