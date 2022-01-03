#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pII = pair<int, int>;
#define fi first
#define se second
#define SZ(x) (int(x.size()))
#define dbg(x...) do { cout << "\033[32;1m" << #x << " -> "; err(x); } while (0) 
void err() { cout << "\033[39;0m" << endl; } 
template <class T, class... Ts> void err(const T& arg, const Ts&... args) { cout << arg << ' '; err(args...); }
const int N = 1e5 + 10;
int n, m, a[N]; 

struct E {
	int b, p, id; 
	bool operator < (const E &other) const {
		if (p != other.p) 
			return p < other.p;
		return b < other.b;
	}
}e[N];

struct SEG {
	struct node {
		ll val;
		int pos; 
		node() { val = 0, pos = -1; }
		node operator + (const node& other) const {
			node res = node();
			res.val = val + other.val;
			res.pos = max(pos, other.pos);
			return res;
		}
	}t[N << 2];
	void build(int id, int l, int r) {
		t[id] = node();
		if (l == r) {
			t[id].val = a[l];
			if (t[id].val == 0) t[id].pos = -1;
			else t[id].pos = l;
		//	dbg(id, l, r, t[id].pos, t[id].val);
			return;
		}
		int mid = (l + r) >> 1;
		build(id << 1, l, mid);
		build(id << 1 | 1, mid + 1, r);
		t[id] = t[id << 1] + t[id << 1 | 1];
	}
	void update(int id, int l, int r, int pos, int v) {
		if (l == r) {
			t[id].val += v;
			if (t[id].val == 0) t[id].pos = -1;
			else t[id].pos = l;
			return;
		}
		int mid = (l + r) >> 1;
		if (pos <= mid) update(id << 1, l, mid, pos, v);
		else update(id << 1 | 1, mid + 1, r, pos, v);
		t[id] = t[id << 1] + t[id << 1 | 1];
	}
	ll query(int id, int l, int r, int ql, int qr) {
		if (l >= ql && r <= qr) return t[id].val;
		int mid = (l + r) >> 1;
		ll res = 0;
		if (ql <= mid) res += query(id << 1, l, mid, ql, qr);
		if (qr > mid) res += query(id << 1 | 1, mid + 1, r, ql, qr);
		return res;
	}
	int queryPos(int id, int l, int r, int ql, int qr) {
		if (l >= ql && r <= qr) return t[id].pos;
		int mid = (l + r) >> 1;
		int pos = -1;
		if (ql <= mid) pos = max(pos, queryPos(id << 1, l, mid, ql, qr));
		if (qr > mid) pos = max(pos, queryPos(id << 1 | 1, mid + 1, r, ql, qr));
		return pos;
	}
}seg;

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++i) scanf("%d", a + i);
	for (int i = 1; i <= m; ++i) scanf("%d", &e[i].b);
	for (int i = 1; i <= m; ++i) scanf("%d", &e[i].p);
	vector <pII> vec; 
	for (int i = 1; i <= n; ++i) {
		while (SZ(vec) && a[i] >= vec.back().fi) vec.pop_back();
		vec.push_back(pII(a[i], i));
	}
	reverse(vec.begin(), vec.end()); 
	for (int i = 1; i <= m; ++i) {
		auto pos = lower_bound(vec.begin(), vec.end(), pII(e[i].b, -1));
		if (pos == vec.end()) e[i].id = -1;
		else e[i].id = pos->se;
	//	dbg(i, e[i].id);
	}
	sort(e + 1, e + 1 + m);
	int res = 0;
	seg.build(1, 1, n);
	for (int i = 1; i <= m; ++i) if (e[i].id != -1) {
		int id = e[i].id;
		if (seg.query(1, 1, n, 1, id) >= e[i].p) {
			++res;
			int need = e[i].p;
			while (need > 0) {
				int pos = seg.queryPos(1, 1, n, 1, id);
				if (a[pos] >= need) {
					a[pos] -= need;
					seg.update(1, 1, n, pos, -need);
					need = 0;
				} else {
					need -= a[pos];
					seg.update(1, 1, n, pos, -a[pos]);
					a[pos] = 0;
				}
			}
		}
	}
	printf("%d\n", res);
	return 0;
}
