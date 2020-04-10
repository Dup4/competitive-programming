#include <bits/stdc++.h>
using namespace std;
#define dbg(x...) do { cout << "\033[32;1m" << #x << " -> "; err(x); } while (0) 
void err() { cout << "\033[39;0m" << endl; } 
template <class T, class... Ts> void err(const T& arg, const Ts&... args) { cout << arg << ' '; err(args...); }
typedef long long ll;
const int N = 4e5 + 10, M = 2e3 + 100;
int n, m; ll ans[N];

struct SEG {
	struct node {
		int cnt;
		ll sum, lazy; 
		node() { sum = lazy = 0; }
		void up(ll x) {
			sum += x * cnt;
			lazy += x;	
		}
		node operator + (const node &other) const {
			node res = node();
			res.cnt = cnt + other.cnt;
			res.sum = sum + other.sum;
			return res;
		}
	}t[M << 2];
	void down(int id) {
		ll &lazy = t[id].lazy;
		t[id << 1].up(lazy);
		t[id << 1 | 1].up(lazy);
		lazy = 0;
	}
	void build(int id, int l, int r) {
		t[id] = node();
		if (l == r) {
			t[id].cnt = 1;
			t[id].sum = 0;
			return;
		}
		int mid = (l + r) >> 1;
		build(id << 1, l, mid);
		build(id << 1 | 1, mid + 1, r);
		t[id] = t[id << 1] + t[id << 1 | 1];
	}
	void update(int id, int l, int r, int ql, int qr, ll v) {
		if (l >= ql && r <= qr) {
			t[id].up(v);
			return;
		}
		int mid = (l + r) >> 1;
		down(id);
		if (ql <= mid) update(id << 1, l, mid, ql, qr, v);
		if (qr > mid) update(id << 1 | 1, mid + 1, r, ql, qr, v);
		t[id] = t[id << 1] + t[id << 1 | 1];
	}
	ll query(int id, int l, int r, int ql, int qr) {
		if (l >= ql && r <= qr) return t[id].sum;
		int mid = (l + r) >> 1;
		down(id);
		ll res = 0;
		if (ql <= mid) res += query(id << 1, l, mid, ql, qr);
		if (qr > mid) res += query(id << 1 | 1, mid + 1, r, ql, qr);
		return res;
	}
}seg[2];

namespace CDQ {	
	struct node {
		int tp, opt, x, y, z1, z2, id, v;
		node() {}
		node(int tp, int opt, int x, int y, int z1, int z2, int id, int v) : tp(tp), opt(opt), x(x), y(y), z1(z1), z2(z2), id(id), v(v) {}
		bool operator < (const node &other) const { return x < other.x; } 
	}t[N], t1[N];
	bool cmp1(const node &a, const node &b) {
		if (a.y == b.y)
			return a.x < b.x;
		return a.y < b.y;
	}
	int tot, tot1;
	void init() { tot = 0; }
	void addQuery(int tp, int opt, int x, int y, int z1, int z2, int id) { t[++tot] = node(tp, opt, x, y, z1, z2, id, 0); }
	void addModify(int tp, int opt, int x, int y, int z1, int z2, int v) { t[++tot] = node(tp, opt, x, y, z1, z2, 0, v); }
	void calc() {
		for (int i = 1; i <= tot1; ++i) {
			if (t1[i].tp == 0) {
				seg[0].update(1, 1, m, t1[i].z1, t1[i].z2, -1ll * (t1[i].y - 1) * t1[i].v * t1[i].opt);
				seg[1].update(1, 1, m, t1[i].z1, t1[i].z2, t1[i].v * t1[i].opt);
			} else {
				ans[t1[i].id] += 1ll * t1[i].y * seg[1].query(1, 1, m, t1[i].z1, t1[i].z2) * t1[i].opt + 
								 seg[0].query(1, 1, m, t1[i].z1, t1[i].z2) * t1[i].opt;
			}
		}
		for (int i = 1; i <= tot1; ++i) {
			if (t1[i].tp == 0) {
				seg[0].update(1, 1, m, t1[i].z1, t1[i].z2, -1ll * (t1[i].y - 1) * t1[i].v * t1[i].opt * -1);
				seg[1].update(1, 1, m, t1[i].z1, t1[i].z2, t1[i].v * t1[i].opt * -1);
			}
		}
	}
	void solve(int l, int r) {
		if (l == r) return;
		int mid = (l + r) >> 1;
		solve(l, mid); solve(mid + 1, r);
		tot1 = 0;
		for (int i = l; i <= mid; ++i) {
			if (t[i].tp == 0)
				t1[++tot1] = t[i];
		}
		for (int i = mid + 1; i <= r; ++i) {
			if (t[i].tp == 1)
				t1[++tot1] = t[i];
		}
		sort(t1 + 1, t1 + 1 + tot1, cmp1);
		calc();
	}
	void gao() {
		memset(ans, 0, sizeof (ans[0]) * (tot + 5));
		seg[0].build(1, 1, m);
		seg[1].build(1, 1, m);
		solve(1, tot);
	}
}


int main() {
	scanf("%d%d", &n, &m);
	int op, x[2], y[2], v;
	CDQ::init();
	int q = 0, _q = 0;
	while (scanf("%d", &op) != EOF) {
		++q;
		scanf("%d%d%d%d", x, y, x + 1, y + 1);
		if (op == 1) {
			scanf("%d", &v);
			CDQ::addModify(0, 1, q, x[0], y[0], y[1], v);	
			CDQ::addModify(0, -1, q, x[1] + 1, y[0], y[1], v);
		} else {
			++_q;
			CDQ::addQuery(1, -1, q, x[0] - 1, y[0], y[1], _q);
			CDQ::addQuery(1, 1, q, x[1], y[0], y[1], _q);
		}
	}
	CDQ::gao();
	for (int i = 1; i <= _q; ++i)
		printf("%lld\n", ans[i]);
	return 0;
}
