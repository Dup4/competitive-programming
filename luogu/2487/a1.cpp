#include <bits/stdc++.h>
using namespace std;
#define dbg(x...) do { cout << "\033[32;1m" << #x << " -> "; err(x); } while (0) 
void err() { cout << "\033[39;0m" << endl; } 
template <class T, class... Ts> void err(const T& arg, const Ts&... args) { cout << arg << ' '; err(args...); }
typedef double db;
typedef pair<int, db> pID;
#define fi first
#define se second
const int N = 5e4 + 10;
int n;

pID op(pID a, pID b) {
	if (a.fi > b.fi) return a;
	if (a.fi < b.fi) return b;
	return pID(a.fi, a.se + b.se);
}

struct Hash {
	vector <int> a;
	int& operator[](int x) { return a[x - 1]; }
	int size() { return a.size(); }
	void init() { a.clear(); }
	void add(int x) { a.push_back(x); }
	void gao() { sort(a.begin(), a.end()); a.erase(unique(a.begin(), a.end()), a.end()); }
	int get(int x) { return lower_bound(a.begin(), a.end(), x) - a.begin() + 1; }	
}hy, hz;

struct SEG {
	pID t[N << 2];
	void build(int id, int l, int r) {
		t[id] = pID(0, 1); 
		if (l == r) return;
		int mid = (l + r) >> 1;
		build(id << 1, l, mid);
		build(id << 1 | 1, mid + 1, r);
	}
	void update(int id, int l, int r, int pos, pID v) {
		if (l == r) {
			if (v == pID(-1, -1)) t[id] = pID(0, 1);
			else t[id] = op(t[id], v); 
			return;
		}
		int mid = (l + r) >> 1;
		if (pos <= mid) update(id << 1, l, mid, pos, v);
		else update(id << 1 | 1, mid + 1, r, pos, v);
		t[id] = op(t[id << 1], t[id << 1 | 1]);
	}
	pID query(int id, int l, int r, int ql, int qr) {
		if (l >= ql && r <= qr) return t[id];
		int mid = (l + r) >> 1;
		pID res = pID(0, 1);
		if (ql <= mid) res = op(res, query(id << 1, l, mid, ql, qr));
		if (qr > mid) res = op(res, query(id << 1 | 1, mid + 1, r, ql, qr));
		return res;
	}
}seg;

struct E { int x, y, z; }e[N];

struct CDQ {
	struct node {
		int x, y, z;
		bool operator < (const node &other) const { return x < other.x; }
	}t[N], t1[N]; 
	static bool cmp(const node &a, const node &b) {
		if (a.y == b.y)
			return a.x < b.x;
		return a.y < b.y;
	}
	int tot;
	void init() { tot = 0; }
    void addNode(int x, int y, int z) { t[++tot] = {x, y, z}; }	
	pID f[N]; 
	void solve(int l, int r) {
		if (l == r) {
			if (f[l].fi <= 1)
				f[l] = pID(1, 1);
			return;
		}
		int mid = (l + r) >> 1;
		solve(l, mid);
		for (int i = l; i <= r; ++i) t1[i] = t[i];
		sort(t1 + l, t1 + r + 1, cmp);
		for (int i = l; i <= r; ++i) {
			if (t1[i].x <= mid) { 
				seg.update(1, 1, hz.size(), t1[i].z, f[t1[i].x]); 
			} else {
				pID tmp = seg.query(1, 1, hz.size(), 1, t1[i].z);
				++tmp.fi;
				f[t1[i].x] = op(f[t1[i].x], tmp);
			}
		}
		for (int i = l; i <= r; ++i) {
			if (t1[i].x <= mid) {
				seg.update(1, 1, hz.size(), t1[i].z, pID(-1, -1));
			}
		}
		solve(mid + 1, r);
	}
	void gao() {
		seg.build(1, 1, hz.size());
		memset(f, 0, sizeof (f[0]) * (tot + 5));
		sort(t + 1, t + 1 + tot);
		solve(1, tot);
	}
}cdqF, cdqG;

int main() {
	while (scanf("%d", &n) != EOF) {
		hy.init(); hz.init(); 
		for (int i = 1; i <= n; ++i) {
			e[i].x = i;
			scanf("%d%d", &e[i].y, &e[i].z);
			hy.add(e[i].y);
			hz.add(e[i].z);
		}
		hy.gao(); hz.gao();
		for (int i = 1; i <= n; ++i) {
			e[i].y = hy.get(e[i].y);
			e[i].z = hz.get(e[i].z);
		}
		cdqF.init();
		for (int i = 1; i <= n; ++i) {
			cdqF.addNode(e[i].x, hy.size() - e[i].y + 1, hz.size() - e[i].z + 1);
		}
		cdqF.gao();
		cdqG.init();
		for (int i = 1; i <= n; ++i) {
			cdqG.addNode(n - e[i].x + 1, e[i].y, e[i].z);
		}
		cdqG.gao();
		pID res = pID(0, 0);
		for (int i = 1; i <= n; ++i) res = op(res, cdqF.f[i]);
		printf("%d\n", res.fi);
		for (int i = 1; i <= n; ++i) {
			int j = n - i + 1;
			pID _f = cdqF.f[i], _g = cdqG.f[j];
			db ans = 0; 
			if (_f.fi + _g.fi - 1 == res.fi) {
				ans = _f.se * _g.se / res.se;
			}
			printf("%.5f%c", ans, " \n"[i == n]);
		}
	}
	return 0;
}

