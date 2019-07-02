#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 1000010
int n, a[N], nx[N]; 
int prime[N], tot, check[N];
vector <vector<int>> vec;
void init() {
	memset(check, 0, sizeof check);
	tot = 0;
	for (int i = 2; i < N; ++i) {
		if (!check[i]) {
			prime[++tot] = i;
		}
		for (int j = 1; j <= tot; ++j) {
			if (1ll * i * prime[j] >= N) break;
			check[i * prime[j]] = 1;
			if (i % prime[j] == 0) break;
		}
	}
	vec.clear(); vec.resize(N);
	for (int i = 1; i <= tot; ++i) {
		for (int j = prime[i]; j < N; j += prime[i]) {
			vec[j].push_back(prime[i]);
		}
	}
}
struct SEG {
	struct node {
		ll cnt, sum, lazy;
		node() {
			sum = lazy = 0;
		}
		node (ll sum, ll lazy) : sum(sum), lazy(lazy) {}
		void add(ll x) {
			sum += x * cnt;
			lazy += x;
		}
		node operator + (const node &other) const {
			node res = node();
			res.sum = sum + other.sum;
			res.cnt = cnt + other.cnt;
			return res;
		}
	}t[N << 2];
	void build(int id, int l, int r) {
		t[id] = node();
		t[id].cnt = r - l + 1;
		if (l == r) return;
		int mid = (l + r) >> 1;
		build(id << 1, l, mid);
		build(id << 1 | 1, mid + 1, r);
	}
	void pushdown(int id) {
		ll &lazy = t[id].lazy;
		if (!lazy) return;
		t[id << 1].add(lazy);
		t[id << 1 | 1].add(lazy);
		lazy = 0;
	}
	void update(int id, int l, int r, int ql, int qr, int x) {
		if (l >= ql && r <= qr) {
			t[id].add(x);
			return;
		}
		int mid = (l + r) >> 1;
		pushdown(id);
		if (ql <= mid) update(id << 1, l, mid, ql, qr, x);
		if (qr > mid) update(id << 1 | 1, mid + 1, r, ql, qr, x);
		t[id] = t[id << 1] + t[id << 1 | 1];
	}
}seg;

int main() {
	init();
	while (scanf("%d", &n) != EOF) {
		for (int i = 1; i <= n; ++i) {
			scanf("%d", a + i);
		}
		for (int i = 1; i <= 1000000; ++i) {
			nx[i] = n + 1; 
		}
		ll res = 0;		
		seg.build(1, 1, n);
		for (int i = n; i >= 1; --i) {
			for (auto it : vec[a[i]]) {
				seg.update(1, 1, n, i, nx[it] - 1, 1);
				nx[it] = i;
			}
			res += seg.t[1].sum;
		}
		printf("%lld\n", res);
	}
	return 0;
}
