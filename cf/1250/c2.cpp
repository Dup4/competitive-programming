#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pIL = pair<int, ll>;
#define fi first
#define se second
const int N = 2e5 + 10;
const ll INF = 0x3f3f3f3f3f3f3f3f;
int n, m, pl[N], pr[N]; ll k;
vector <vector<pIL>> vec;

struct SEG {
	struct node {
		ll Min, lazy; int pos; 
		node() { Min = INF; pos = 0; } 
		void up(ll x) {
			Min += x;
			lazy += x;
		}
		node operator + (const node &other) const {
			node res = node();
			if (Min <= other.Min) {
				res.Min = Min;
				res.pos = pos;
			} else {
				res.Min = other.Min;
				res.pos = other.pos;
			}
			return res;
		}
	}t[N << 2], res;
	void build(int id, int l, int r) {
		t[id] = node();
		if (l == r) {
			t[id].Min = 0;
			t[id].pos = l;
			return;
		}
		int mid = (l + r) >> 1;
		build(id << 1, l, mid);
		build(id << 1 | 1, mid + 1, r);
		t[id] = t[id << 1] + t[id << 1 | 1];
	}
	void down(int id) {
		ll &lazy = t[id].lazy;
		if (lazy) {
			t[id << 1].up(lazy);
			t[id << 1 | 1].up(lazy);
			lazy = 0;
		}
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
	while (scanf("%d%lld", &n, &k) != EOF) {
		vec.clear(); vec.resize(N);
		m = 2e5;
		for (int i = 1; i <= n; ++i) {
			int l, r; ll p;
			scanf("%d%d%lld", &l, &r, &p);
			pl[i] = l, pr[i] = r;
			vec[r].push_back(pIL(l, p));
		}
		ll p = 0, sum = 0; int L = -1, R = -1; 
		seg.build(1, 1, m);
		for (int i = 1; i <= m; ++i) {
			seg.update(1, 1, m, i, i, -k);
			for (auto &it : vec[i]) {
				sum += it.se;	
				seg.update(1, 1, m, 1, it.fi, it.se);
			}
			seg.res = SEG::node();
			seg.query(1, 1, m, 1, i);
			if (sum + k * i - seg.res.Min > p) {
				p = sum + k * i - seg.res.Min;
				L = seg.res.pos;
				R = i;
			}
		}		
		if (p == 0) puts("0");
		else {
			vector <int> vec;
			for (int i = 1; i <= n; ++i) 
				if (pl[i] >= L && pr[i] <= R)
					vec.push_back(i);
			int sze = vec.size();
			printf("%lld %d %d %d\n", p, L, R, sze);
			for (int i = 0; i < sze; ++i)
				printf("%d%c", vec[i], " \n"[i == sze - 1]);
		}
	}
	return 0;
}
