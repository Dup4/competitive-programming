#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define dbg(x...) do { cout << "\033[32;1m" << #x << " -> "; err(x); } while (0) 
void err() { cout << "\033[39;0m" << endl; } 
template <class T, class... Ts> void err(const T& arg, const Ts&... args) { cout << arg << ' '; err(args...); }
const int N = 2e5 + 10, INF = 0x3f3f3f3f;
int n, a[N], b[N], c[N], d[N]; ll res; 
vector <vector<int>> fac;

inline ll f(ll x) { return x * (x + 1) / 2; }

struct SEG {
	static const int INF = -0x3f3f3f3f;
	static bool cmp(int x, int y) { return x > y; }
	static int get(int x, int y) { return cmp(x, y) ? y : x; }
	struct TAG {
		int v[2], cnt;
		TAG() {}
		void init() { v[0] = v[1] = -INF, cnt = 0;  } 
		TAG operator + (const TAG &other) const {
			TAG res; res.init();
			if (v[0] == other.v[0]) {
				res.v[0] = v[0];
				res.cnt = cnt + other.cnt;
				res.v[1] = get(v[1], other.v[1]);
			} else {
				if (cmp(v[0], other.v[0])) {
					res = other;
					res.v[1] = get(other.v[1], v[0]);
				} else {
					res = *this;
					res.v[1] = get(v[1], other.v[0]);
				}
			}	
			return res;
		}
	};
	struct node {
		ll sum; int lazy; 
	   	TAG tag; 
		node() { tag.init(); sum = 0; lazy = INF; }
		void up(int _lazy) {
		    if (cmp(_lazy, tag.v[0]) == 0) return; 
			sum += 1ll * tag.cnt * (_lazy - tag.v[0]); 
			tag.v[0] = _lazy;
			lazy = _lazy;
		}
		node operator + (const node &other) const {
			node res = node();
			res.sum = sum + other.sum; 
			res.tag = tag + other.tag;
			return res;
		}
	}t[N << 2], res; 
	void build(int id, int l, int r) {
		t[id] = node();
		if (l == r) {
			t[id].tag.cnt = 1;
			t[id].tag.v[0] = 0;
			t[id].sum = 0; 
			return;
		}
		int mid = (l + r) >> 1;
		build(id << 1, l, mid);
		build(id << 1 | 1, mid + 1, r);
		t[id] = t[id << 1] + t[id << 1 | 1];
	}
	void pushdown(int id) {
		int &lazy = t[id].lazy;
		if (lazy == INF) return;
		t[id << 1].up(lazy);
		t[id << 1 | 1].up(lazy);
		lazy = INF;
	}
	void update(int id, int l, int r, int ql, int qr, int x) {
		if (cmp(x, t[id].tag.v[0]) == 0) return; 
		if (l == r) {
			x = cmp(x, t[id].tag.v[0]) ? x : t[id].tag.v[0];
			t[id].sum = x;
			t[id].tag.v[0] = x;
			t[id].tag.v[1] = -INF;
			return;
		} 
		if (l >= ql && r <= qr && cmp(x, t[id].tag.v[0]) && cmp(t[id].tag.v[1], x)) {
			t[id].up(x);
			return;
		}
		int mid = (l + r) >> 1;
		pushdown(id); 
		if (ql <= mid) update(id << 1, l, mid, ql, qr, x);
		if (qr > mid) update(id << 1 | 1, mid + 1, r, ql, qr, x);
		t[id] = t[id << 1] + t[id << 1 | 1];
	}
	void query(int id, int l, int r, int ql, int qr) {
		if (l >= ql && r <= qr) {
			res = res + t[id];
			return;
		}
		int mid = (l + r) >> 1;
		pushdown(id);
		if (ql <= mid) query(id << 1, l, mid, ql, qr);
		if (qr > mid) query(id << 1 | 1, mid + 1, r, ql, qr);
	}
}seg;

ll gao(int l, int mid, int r) {
	seg.build(1, mid, r); 
	memset(b, -1, sizeof b);
	memset(c, -1, sizeof c); 
	d[r + 1] = 0;
	for (int i = 1; i < l; ++i) {
		for (auto &it : fac[a[i]]) {
			if (b[it] != -1) { 
				d[r + 1] = max(d[r + 1], it); 
			} 
			b[it] = i;
		}
	}
	for (int i = r; i >= mid; --i) {
		d[i] = d[i + 1];
		seg.update(1, mid, r, i, i, d[i]); 
		for (auto &it : fac[a[i]]) {
			if (b[it] != -1 || c[it] != -1) {
				d[i] = max(d[i], it);
			} 
			if (c[it] == -1) c[it] = i;
		}
	}
	ll res = 0;
	for (int i = l; i <= mid; ++i) {
		res += seg.t[1].sum;
//		dbg(i, seg.t[1].sum);
		for (auto &it : fac[a[i]]) { 
			if (b[it] != -1) {
				seg.update(1, mid, r, mid, r, it); 
			} else if (c[it] != -1) {
				//dbg(i, it, mid, c[it] - 1);
				seg.update(1, mid, r, mid, c[it] - 1, it);  
			}
			b[it] = i;
		}
	}
	return res;
}

int main() {
	fac.clear(); fac.resize(N);
	for (int i = 1; i < N; ++i) { 
		for (int j = i; j < N; j += i) {
			fac[j].push_back(i); 
		}
	}
	int _T;
	scanf("%d", &_T);
	while (_T--) {
		scanf("%d", &n);
		for (int i = 1; i <= n; ++i) scanf("%d", a + i); 
		if (n == 1) {
			puts("0");
			continue;
		}
		memset(b, -1, sizeof b);
		int Max = 1, x = 1, y = 2;
		for (int i = 1; i <= n; ++i) {
			for (auto &it : fac[a[i]]) {
				if (b[it] != -1) {
					if (it > Max) {
						Max = it;
						x = b[it];
						y = i;
					}
				}
				b[it] = i; 
			}
		}
		if (Max == 1) {
			printf("%lld\n", f(n) - 3);
		} else {
			res = 1ll * Max * (f(x - 1) + f(y - x - 1) + f(n - y));
	//		dbg(res);
			res += gao(1, x, n);
//			dbg(gao(1, x, n));
			res += gao(x + 1, y, n);
	//		dbg(gao(x + 1, y, n));
			printf("%lld\n", res);
		}
	}
	return 0;
}
