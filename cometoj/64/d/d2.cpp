#include <bits/stdc++.h>
#include <bits/extc++.h>
using namespace std;
using namespace __gnu_pbds;
using ll = long long;
using ull = unsigned long long;
const int N = 5e5 + 10; 
int n, m, q, rt, a[N], fa[N], deep[N];
vector <vector<int>> G;
cc_hash_table <ull, int> mp; 

ull seed = 19260817; 
ull base[N];
struct HashNode { 
	ull val; int len;
	HashNode() { val = 0; len = 0; }
	HashNode(ull val, int len) : val(val), len(len) {}
	HashNode operator + (const HashNode &other) const {
		HashNode res = HashNode();
		res.len = len + other.len;
		res.val = val * base[other.len] + other.val;
		return res;
	}
}Ha[N];

struct SEG {
	HashNode t[N << 2], res;
	int done;
	void build(int id, int l, int r) {
		t[id] = HashNode(0, 1);
		if (l == r) return;
		int mid = (l + r) >> 1;
		build(id << 1, l, mid);
		build(id << 1 | 1, mid + 1, r);
		t[id] = t[id << 1] + t[id << 1 | 1];
	}
	void update(int id, int l, int r, int pos, int v) {
		if (l == r) {
			t[id] = HashNode(v, 1);
			return;
		}
		int mid = (l + r) >> 1;
		if (pos <= mid) update(id << 1, l, mid, pos, v);
		else update(id << 1 | 1, mid + 1, r, pos, v);
		t[id] = t[id << 1] + t[id << 1 | 1];
	}
	void query(int id, int l, int r, int ql, int qr) {
		if (done) return;
		if (l >= ql && r <= qr) {
			if (mp[(res + t[id]).val]) {
				res = res + t[id];
				return;
			}
			if (l == r) done = 1;
		}
		if (l == r) return;
		int mid = (l + r) >> 1;
		if (ql <= mid) query(id << 1, l, mid, ql, qr);
		if (qr > mid) query(id << 1 | 1, mid + 1, r, ql, qr);
	}
}seg;

void dfs(int u) {
	mp[Ha[u].val] = u;
	for (int i = 0, sze = G[u].size(); i < sze; ++i) {
		int rk = i + 1, v = G[u][i];
		deep[v] = deep[u] + 1;
		Ha[v] = Ha[u] + HashNode(rk, 1);
		dfs(v);
	}
}

int main() {
	base[0] = 1;
	for (int i = 1; i < N; ++i) {
		base[i]= base[i - 1] * seed;
	}
	scanf("%d%d%d", &n, &m, &q);
	rt = 1;
	G.clear(); G.resize(n + 10);
	mp.clear();
	for (int i = 1; i <= n; ++i) {
		scanf("%d", fa + i);
		if (fa[i] == 0) rt = i;
		else {
			G[fa[i]].push_back(i);
		}
	} 
	deep[rt] = 0;
	Ha[rt] = HashNode(0, 1);
	dfs(rt);
	seg.build(1, 1, m);
	for (int i = 1; i <= m; ++i) {
		scanf("%d", a + i);
		seg.update(1, 1, m, i, a[i]);
	}
	for (int _q = 1, op, x, l, r, t, k; _q <= q; ++_q) {
		scanf("%d", &op);
		if (op == 1) {
			scanf("%d%d%d", &x, &l, &r);
			seg.done = 0;
			seg.res = Ha[x]; 
			seg.query(1, 1, m, l, r);
			printf("%d\n", mp[seg.res.val]);
		} else {
			scanf("%d%d", &t, &k);
			a[t] = k;
			seg.update(1, 1, m, t, a[t]);
		}
	}
	return 0;
}
