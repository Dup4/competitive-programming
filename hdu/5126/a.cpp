#include <bits/stdc++.h>
using namespace std;
#define dbg(x...) do { cout << "\033[32;1m" << #x << " -> "; err(x); } while (0) 
void err() { cout << "\033[39;0m" << endl; } 
template <class T, class... Ts> void err(const T& arg, const Ts&... args) { cout << arg << ' '; err(args...); }
const int N = 1e5 + 10;
int ans[N];

struct Hash {
	vector <int> a;
	int& operator[](int x) { return a[x - 1]; }
	int size() { return a.size(); }
	void init() { a.clear(); }
	void add(int x) { a.push_back(x); }
	void gao() { sort(a.begin(), a.end()); a.erase(unique(a.begin(), a.end()), a.end()); }
	int get(int x) { return lower_bound(a.begin(), a.end(), x) - a.begin() + 1; }	
}hs;

struct BIT {
	int a[N], n;
	void init(int _n = N - 5) { n = _n; memset(a, 0, sizeof (a[0]) * (n + 5)); }
    void update(int x, int v) { for (; x <= n; x += x & -x) a[x] += v; }
	int query(int x) {
		int res = 0;
		for (; x > 0; x -= x & -x)
			res += a[x];
		return res;
	}	
}bit;

namespace CDQ {
	struct node {
		// 0 加点 -1, 1询问
		int op, x, y, z, id;
		node() {}
		node(int op, int x, int y, int z, int id = 0) : op(op), x(x), y(y), z(z), id(id) {}
	}t[N * 8], t1[N * 8], t2[N * 8]; 
	bool cmp1(const node &a, const node &b) {
		if (a.x == b.x)
			return a.id < b.id;
		return a.x < b.x;	
	}
	bool cmp2(const node &a, const node &b) {
		if (a.y == b.y)
			return a.id < b.id;
		return a.y < b.y;
	}
	int tot, tot1, tot2;
	void init() { hs.init(); tot = 0; }
	void addModify(int x, int y, int z) {
		t[++tot] = node(0, x, y, z);
		hs.add(z);
	}
	void addQuery(int x1, int y1, int z1, int x2, int y2, int z2, int id) {
		t[++tot] = node(1, x2, y2, z2, id);
		t[++tot] = node(-1, x2, y2, z1 - 1, id);
		t[++tot] = node(-1, x2, y1 - 1, z2, id);
		t[++tot] = node(-1, x1 - 1, y2, z2, id);
		t[++tot] = node(1, x2, y1 - 1, z1 - 1, id);
		t[++tot] = node(1, x1 - 1, y2, z1 - 1, id);
		t[++tot] = node(1, x1 - 1, y1 - 1, z2, id);
		t[++tot] = node(-1, x1 - 1, y1 - 1, z1 - 1, id); 
		hs.add(z2); hs.add(z1 - 1);
	}
	void calc() {
		for (int i = 1; i <= tot2; ++i) {
			if (t2[i].op == 0) {
				bit.update(t2[i].z, 1);
			} else {
				ans[t2[i].id] += t2[i].op * bit.query(t2[i].z);
			}
		}
		for (int i = 1; i <= tot2; ++i)
			if (t2[i].op == 0)
				bit.update(t2[i].z, -1);
	}
	void solve2(int l, int r) {
		if (l >= r) return;
		int mid = (l + r) >> 1;
		solve2(l, mid); solve2(mid + 1, r);
		tot2 = 0;
		for (int i = l; i <= mid; ++i) {
			if (t1[i].op == 0) 
				t2[++tot2] = t1[i];
		}
		for (int i = mid + 1; i <= r; ++i) {
			if (t1[i].op)
				t2[++tot2] = t1[i];
		}
		sort(t2 + 1, t2 + 1 + tot2, cmp2);
		calc();
	}
	void solve1(int l, int r) {
		if (l >= r) return;
		int mid = (l + r) >> 1;
		solve1(l, mid); solve1(mid + 1, r);
		tot1 = 0;
		for (int i = l; i <= mid; ++i) {
			if (t[i].op == 0)
				t1[++tot1] = t[i];
		}
		for (int i = mid + 1; i <= r; ++i) {
			if (t[i].op)
				t1[++tot1] = t[i];
		}
		sort(t1 + 1, t1 + 1 + tot1, cmp1); 
		solve2(1, tot1);
	}
	void gao() {
		hs.gao();
		bit.init(hs.size());
		for (int i = 1; i <= tot; ++i)
			t[i].z = hs.get(t[i].z);
		solve1(1, tot);
	}
}

int main() {
	int _T; scanf("%d", &_T);
	while (_T--) {
		int q;
		scanf("%d", &q);
		CDQ::init();	
		int _q = 0;
		for (int i = 1; i <= q; ++i) {
			int op, x[2], y[2], z[2];
			scanf("%d%d%d%d", &op, x, y, z);
			if (op == 1) CDQ::addModify(x[0], y[0], z[0]);
			else {
			   	scanf("%d%d%d", x + 1, y + 1, z + 1);
				CDQ::addQuery(x[0], y[0], z[0], x[1], y[1], z[1], ++_q);
			}
		}
		memset(ans, 0, sizeof (ans[0]) * (_q + 1));
		CDQ::gao();
		for (int i = 1; i <= _q; ++i)
			printf("%d\n", ans[i]);
	}
	return 0;
}
