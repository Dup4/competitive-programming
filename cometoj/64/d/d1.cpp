#include <bits/stdc++.h>
#include <bits/extc++.h>
using namespace std;
using namespace __gnu_pbds;
using ll = long long;
#define dbg(x...) do { cout << "\033[32;1m" << #x << " -> "; err(x); } while (0) 
void err() { cout << "\033[39;0m" << endl; } 
template <class T, class... Ts> void err(const T& arg, const Ts&... args) { cout << arg << ' '; err(args...); }
const int N = 5e5 + 10; 
int n, m, q, rt, res, a[N], fa[N], deep[N];
int base[N], fbase[N], Ha[N], mod = 1e9 + 7;
vector <vector<int>> G;
gp_hash_table <int, int> mp;

inline void chadd(int &x, int y) {
	x += y;
	while (x >= mod) x -= mod;
	while (x < 0) x += mod;
}

ll qpow(ll base, int n) {
	ll res = 1;
	while (n) {
		if (n & 1) res = res * base % mod;
		base = base * base % mod;
		n >>= 1;
	}	
	return res;
}

struct SEG {
	struct node {
		int l, r, lazy;
		node() { l = r = lazy = 0; }
		void up(int _lazy) {
			chadd(l, _lazy);
			chadd(r, _lazy);
			chadd(lazy, _lazy); 
		}
		node operator + (const node &other) const {
			node res = node();
			res.l = l;
			res.r = other.r;
			return res;
		}
	}t[N << 3];
	void build(int id, int l, int r) {
		t[id] = node();
		if (l == r) return;
		int mid = (l + r) >> 1;
		build(id << 1, l, mid);
		build(id << 1 | 1, mid + 1, r);
	}
	void down(int id) {
		int &lazy = t[id].lazy;
		if (!lazy) return;
		t[id << 1].up(lazy);
		t[id << 1 | 1].up(lazy);
		lazy = 0;
	}
	void update(int id, int l, int r, int ql, int qr, int v) {
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
	int query(int id, int l, int r, int pos) {
		if (l == r) return t[id].l;
		int mid = (l + r) >> 1;
		down(id);
		if (pos <= mid) return query(id << 1, l, mid, pos);
		else return query(id << 1 | 1, mid + 1, r, pos);
	}
	void query(int id, int l, int r, int ql, int qr, int x, int del) {
		if (l >= ql && r <= qr) {
			int Hashl = (Ha[x] + 1ll * (t[id].l - del + mod) % mod * fbase[ql - 1] % mod * base[deep[x]] % mod) % mod;
			if (mp[Hashl] == 0) return;
	//		if (mp.count(Hashl) == 0) return; 
			int Hashr = (Ha[x] + 1ll * (t[id].r - del + mod) % mod * fbase[ql - 1] % mod * base[deep[x]] % mod) % mod;
			if (mp[Hashr] != 0) {
		//	if (mp.count(Hashr) != 0) {
				res = mp[Hashr];
				return;
			}
		}
		int mid = (l + r) >> 1;
		down(id);
		if (ql <= mid) query(id << 1, l, mid, ql, qr, x, del);
		if (qr > mid) query(id << 1 | 1, mid + 1, r, ql, qr, x, del);
	}
}seg;

void dfs(int u, int _Ha) {
	mp[_Ha] = u; Ha[u] = _Ha;
	for (int i = 0, sze = G[u].size(); i < sze; ++i) {
		int rk = i + 1, v = G[u][i];
		deep[v] = deep[u] + 1;
		dfs(v, (_Ha + 1ll * rk * base[deep[v]] % mod) % mod); 
	}
}

//int get(int l, int r) {
//	if (l > r) return 0;
//	return 1ll * bit.query(l, r) * fbase[l - 1] % mod;
//}
//
//int query(int x, int l, int r) {
//	int el = 0, er = r - l + 1, res = x;
//	while (er - el >= 0) {
//		int mid = (el + er) >> 1;
//		int Hash = (Ha[x] + 1ll * get(l, l + mid - 1) * base[deep[x]] % mod) % mod;
//		if (mp.count(Hash) != 0) {
//			res = mp[Hash]; 
//			el = mid + 1;
//		} else {
//			er = mid - 1;
//		}
//	}
//	return res;
//}

int main() {
	base[0] = 1;
	fbase[0] = 1;
	for (int i = 1; i < N; ++i) {
		base[i] = 1ll * base[i - 1] * 19260817 % mod;
		fbase[i] = qpow(base[i], mod - 2);
	}
	scanf("%d%d%d", &n, &m, &q);
	rt = -1;
	G.clear(); G.resize(n + 1);
	mp.clear();
	for (int i = 1; i <= n; ++i) {
		scanf("%d", fa + i);
		if (fa[i] == 0) rt = i;
		else {
			G[fa[i]].push_back(i);
		}
	} 
	deep[rt] = 0;
	dfs(rt, 0);
	seg.build(1, 1, m);
	for (int i = 1; i <= m; ++i) {
		scanf("%d", a + i);
		seg.update(1, 1, m, i, m, 1ll * a[i] * base[i] % mod);
	}
	for (int _q = 1, op, x, l, r, t, k; _q <= q; ++_q) {
		scanf("%d", &op);
		if (op == 1) {
			scanf("%d%d%d", &x, &l, &r);
			res = x;
			int del = 0;
			if (l > 1) del = seg.query(1, 1, m, l - 1);
			seg.query(1, 1, m, l, r, x, del);
			printf("%d\n", res);
		} else {
			scanf("%d%d", &t, &k);
			seg.update(1, 1, m, t, m, (mod - 1ll * a[t] * base[t] % mod) % mod);
			a[t] = k;
			seg.update(1, 1, m, t, m, 1ll * a[t] * base[t] % mod);
		}
	}
	return 0;
}
