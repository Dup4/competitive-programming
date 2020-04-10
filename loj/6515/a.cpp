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
		if (ql > qr || ql < 0 || qr < 0) return -INF;
		if (l >= ql && r <= qr) return t[id];
		int mid = (l + r) >> 1;
		ll res = -INF; 
		if (ql <= mid) res = max(res, query(id << 1, l, mid, ql, qr));
		if (qr > mid) res = max(res, query(id << 1 | 1, mid + 1, r, ql, qr));
		return res;
	}
}seg[2];

multiset <ll> se[2][510];  

void update(int id, ll w, ll v, int opt) {
	w %= p;
	if (opt == 0) {
		se[id][w].erase(se[id][w].lower_bound(v));
	} else {
		se[id][w].insert(v);	
	}
	if (se[id][w].empty()) seg[id].update(1, 0, p, w, -INF);
	else seg[id].update(1, 0, p, w, *(--se[id][w].end()));
} 

struct Queue {
	struct node { ll w, v, f[510]; }; 
	vector <node> vec[2];
	void clear() { vec[0].clear(); vec[1].clear(); } 
	void rebuild() {
		for (int i = 0; i < 2; ++i) {
			for (auto &it : vec[i]) {
				update(i, it.sw % p, it.sv, 0); 
			}
		}
		int need = ((1 + SZ(vec[0]) + SZ(vec[1])) / 2);
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
				vec[i][j].sw = vec[i][j].w;
				vec[i][j].sv = vec[i][j].v;
				if (j) {
					vec[i][j].sw += vec[i][j - 1].sw;
					vec[i][j].sv += vec[i][j - 1].sv;
				}
				update(i, vec[i][j].sw % p, vec[i][j].sv, 1);
			}
		}	
	}
	void push(int id, ll w, ll v) {
		node tmp = {w, v, w, v};
		if (!vec[id].empty()) { 
			tmp.sw += vec[id].end()[-1].sw;
			tmp.sv += vec[id].end()[-1].sv;
		}
		vec[id].push_back(tmp);
		update(id, tmp.sw % p, tmp.sv, 1);
	}
	void push_front(ll w, ll v) { push(0, w, v); }
	void push_back(ll w, ll v) { push(1, w, v); }
	void pop(int id) {
		if (vec[id].empty()) rebuild();
		update(id, vec[id].end()[-1].sw % p, vec[id].end()[-1].sv, 0);
		vec[id].pop_back();
	}
	void pop_front() { pop(0); }
	void pop_back() { pop(1); }
	ll query(int l, int r) {
		ll Max = -INF;
		if (l == 0) Max = 0;
		for (int i = 0; i < p; ++i) {
			ll tmp = seg[0].query(1, 0, p, i, i);
			if (i >= l && i <= r) Max = max(Max, tmp);
			int L = (l - i + p) % p, R = (r - i + p) % p; 
			if (L <= R) {
				Max = max(Max, tmp + seg[1].query(1, 0, p, L, R));
			} else {
				Max = max(Max, tmp + seg[1].query(1, 0, p, 0, R));
				Max = max(Max, tmp + seg[1].query(0, 0, p, L, p));
			}
		}
		if (Max <= -INF) Max = -1;	
		return Max;
	}
}que;

int main() {
	int _ID; scanf("%d", &_ID);
	scanf("%d%d", &m, &p);
	char op[10]; int x, y; 
	seg[0].build(1, 0, p);
	seg[1].build(1, 0, p);
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
