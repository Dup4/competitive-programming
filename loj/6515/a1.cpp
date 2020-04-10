#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pII = pair<int, int>;
#define dbg(x...) do { cout << "\033[32;1m" << #x << " -> "; err(x); } while (0) 
void err() { cout << "\033[39;0m" << endl; } 
template <class T, class... Ts> void err(const T& arg, const Ts&... args) { cout << arg << ' '; err(args...); }
#define SZ(x) ((int)x.size()) 
#define fi first
#define se second
const int N = 2e5 + 10;
const ll INF = 1e18;
int m, p;

inline void chmax(ll &x, ll y) { if (x < y) x = y; }

struct SEG {
	ll t[510 << 2];
	void build(int id, int l, int r) {
		t[id] = -INF;
		if (l == r) return;
		int mid = (l + r) >> 1;
		build(id << 1, l, mid);
		build(id << 1 | 1, mid + 1, r);
	}
	void update(int id, int l, int r, int pos, ll v) {
		if (l == r) {
			t[id] = v;
			return;
		}
		int mid = (l + r) >> 1;
		if (pos <= mid) update(id << 1, l, mid, pos, v);
		else update(id << 1 | 1, mid + 1, r, pos, v);
		t[id] = max(t[id << 1], t[id << 1 | 1]);
	}
	ll query(int id, int l, int r, int ql, int qr) {
		if (ql > qr) return -INF;
		if (l >= ql && r <= qr) return t[id];
		int mid = (l + r) >> 1;
		ll res = -INF; 
		if (ql <= mid) res = max(res, query(id << 1, l, mid, ql, qr));
		if (qr > mid) res = max(res, query(id << 1 | 1, mid + 1, r, ql, qr));
		return res;
	}
}seg; 

struct Queue {
	struct node { 
		ll w, v, f[510]; 
		node() { memset(f, -0x3f, sizeof f); }
		node(ll w = 0, ll v = 0) : w(w), v(v) { memset(f, -0x3f, sizeof f); f[w % p] = v; }
	}; 
	vector <node> vec[2];
	void clear() { vec[0].clear(); vec[1].clear(); } 
	void rebuild() {
		int need = ((SZ(vec[0]) + SZ(vec[1])) / 2);
		if (vec[0].empty()) {
			swap(vec[0], vec[1]);
			reverse(vec[0].begin(), vec[0].end()); 
		}
		reverse(vec[0].begin(), vec[0].end());
		while (need--) {
			vec[1].push_back(vec[0].back());
			vec[0].pop_back();
		}
		for (int i = 0; i < 2; ++i) {
			reverse(vec[i].begin(), vec[i].end());
			for (int j = 0; j < SZ(vec[i]); ++j) {
				memset(vec[i][j].f, -0x3f, sizeof vec[i][j].f);
				if (j) {
					for (int k = 0; k < p; ++k) {
						int nx = (vec[i][j].w + k) % p;
						chmax(vec[i][j].f[k], vec[i][j - 1].f[k]);
						chmax(vec[i][j].f[nx], vec[i][j - 1].f[k] + vec[i][j].v);
					}
				}
				chmax(vec[i][j].f[vec[i][j].w % p], vec[i][j].v);
			}
		}	
	}
	void push(int id, ll w, ll v) {
		node tmp = {w, v};
		if (!vec[id].empty()) {
			for (int i = 0; i < p; ++i) {
				int nx = (w + i) % p;
				chmax(tmp.f[i], vec[id].end()[-1].f[i]);
				chmax(tmp.f[nx], vec[id].end()[-1].f[i] + v);
			}	
		}
		vec[id].push_back(tmp);
	}
	void push_front(ll w, ll v) { push(0, w, v); }
	void push_back(ll w, ll v) { push(1, w, v); }
	void pop(int id) {
		if (vec[id].empty()) rebuild();
		if (vec[id].empty()) {
			assert(SZ(vec[id ^ 1]) == 1);
			vec[id ^ 1].pop_back();
		}
		else vec[id].pop_back();
	}
	void pop_front() { pop(0); }
	void pop_back() { pop(1); }
	ll query(int l, int r) {
		ll Max = -INF;
		if (l == 0) Max = 0; 
		seg.build(1, 0, p);
		if (!vec[1].empty()) {
			for (int i = 0; i < p; ++i) {
				seg.update(1, 0, p, i, vec[1].end()[-1].f[i]);
				if (i >= l && i <= r) {
					chmax(Max, vec[1].end()[-1].f[i]); 
				}
			}
		}
		if (!vec[0].empty()) for (int i = 0; i < p; ++i) {
			ll tmp = vec[0].end()[-1].f[i];
			if (i >= l && i <= r) chmax(Max, tmp);
			int L = (l - i + p) % p, R = (r - i + p) % p; 
			if (L <= R) {
				Max = max(Max, tmp + seg.query(1, 0, p, L, R));
			} else {
				Max = max(Max, tmp + seg.query(1, 0, p, 0, R));
				Max = max(Max, tmp + seg.query(1, 0, p, L, p));
			}
		}
		if (Max < 0) Max = -1;	
		return Max;
	}
}que;

int main() {
	int _ID; scanf("%d", &_ID);
	scanf("%d%d", &m, &p);
	char op[10]; int x, y; 
    que.clear();	
	for (int i = 1; i <= m; ++i) {
		scanf("%s", op);
		if (strcmp(op, "IF") == 0) {
			scanf("%d%d", &x, &y); 
			que.push_front(x, y);
		} else if (strcmp(op, "IG") == 0) {
			scanf("%d%d", &x, &y);
			que.push_back(x, y);
		} else if (strcmp(op, "DF") == 0) {
			que.pop_front();
		} else if (strcmp(op, "DG") == 0) {
			que.pop_back();
		} else {
			scanf("%d%d", &x, &y);
			printf("%lld\n", que.query(x, y));
		}
	}
	return 0;
}
