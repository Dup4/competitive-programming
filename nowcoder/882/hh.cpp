#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 1100
#define pii pair <int, int>
#define fi first
#define se second
int n, m, G[N][N], a[N];
pii b[N];

struct Cartesian_Tree {
	struct node {
		int id, val, fa;
		int son[2];
		node() {}
		node (int id, int val, int fa) : id(id), val(val), fa(fa) {
			son[0] = son[1] = 0;
		}
	}t[N];
	int root;
	void init() {
		t[0] = node(0, 0, 0);
	}
	void build(int n, int *a) {
		for (int i = 1; i <= n; ++i) {
			t[i] = node(i, a[i], 0);
		}
		for (int i = 1; i <= n; ++i) {
			int k = i - 1;
			while (t[k].val > t[i].val) {
				k = t[k].fa;
			}
			
			t[i].son[0] = t[k].son[1];
			t[k].son[1] = i;
			t[i].fa = k;
			t[t[i].son[0]].fa = i;
		}
		root = t[0].son[1];
	}
	int DFS(int u) {
		if (!u) return 0;
		int lsze = DFS(t[u].son[0]);
		int rsze = DFS(t[u].son[1]);
		b[t[u].id] = pii(lsze, rsze);
		return lsze + rsze + 1;
	}
}T;

ll f(ll l, ll r) {
	if (l > r) return 0;
	return (r + l) * (r - l + 1) / 2;
}

//计算总个数
ll gettot(int n, int *a, pii * b) {
	ll res = 0;
	for (int i = 1; i <= n; ++i) {
		if (a[i] > 0) {
			ll l = b[i].fi, r = b[i].se;
			res += (l + 1) * (r + 1);		
		}
	}
	return res;
}

//计算面积<=x的个数
ll getMin(int x, int n, int *a, pii *b) {
	ll res = 0;
	for (int i = 1; i <= n; ++i) {
		if (!a[i]) continue;
		ll len = x / a[i];
		ll l = b[i].fi, r = b[i].se;
		if (len <= 0) continue;
		if (len - r <= 0) {
			res += f(max(1ll, len - l), len);
		} else {
			res += 1ll * min(len - r, 1ll * l + 1) * (r + 1);
			if (len <= l + r + 1) {
				res += f(max(1ll, len - l), r);
			}
		}
	}
	return res;
}	

//计算面积>=x的个数
ll getMax(int x, int n, int *a, pii *b) {
	ll res = 0;
	for (int i = 1; i <= n; ++i) {
		ll len = x / a[i];
		ll l = b[i].fi, r = b[i].se;
		if (len <= 0) continue;
		
	}
}


ll check(int x) {
	ll res = 0; 
	//对每一行处理出向上的最大高度，就转换成直方图的形式再用笛卡尔树直接计算即可
	for (int i = 1; i <= m; ++i) a[i] = 0;
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			if (G[i][j]) ++a[j];
			else a[j] = 0;
		}
		T.init();
		T.build(m, a);
		T.DFS(T.root);
		res += getMax(x, m, a, b);
	}
}

//求第k大全1矩形
int solve(ll k) {
	int l = 1, r = n * m, res = -1;
	while (r - l >= 0) {
		int mid = (l + r) >> 1;
		if (check(mid) <= k) {
			r = mid - 1;
			res = mid; 
		} else {
			l = mid + 1; 
		}
	}
	return res;
}

int main() {
	while (scanf("%d%d", &n, &m) != EOF) {
		for (int i = 1; i <= n; ++i) 
			for (int j = 1; j <= m; ++j)
				scanf("%1d", G[i] + j);
		printf("%d\n", solve(2));
	}	
	return 0;
}

