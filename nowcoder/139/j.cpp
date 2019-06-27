#include <bits/stdc++.h>
using namespace std;

#define N 100010
int n, q, a[N], b[N], c[N], nx[N], ans[N];
struct node {
	int l, r, id;
	node() {}
	void scan(int id) {
		this->id = id;
		scanf("%d%d", &l, &r);
		if (l >= r) {
			l = 1;
			r = 2;  
		}
	}
}qrr[N];

struct BIT {
	int a[N];
	void init() {
		memset(a, 0, sizeof a);
	}
	void update(int x, int v) {
		for (; x > 0; x -= x & -x) {
			a[x] += v;
		}
	}
	int query(int x) {
		int res = 0;
		for (; x < N; x += x & -x) {
			res += a[x];
		}
		return res;
	}
	int query(int l, int r) {
		return query(l) - query(r + 1);
	}
}bit; 

int main() {
	while (scanf("%d%d", &n, &q) != EOF) {
		for (int i = 1; i <= n; ++i) {
			scanf("%d", a + i);
		}
		for (int i = 1; i <= q; ++i) {
			qrr[i].scan(i);
		}
		if (n == 1) {
			for (int i = 1; i <= q; ++i) {
				printf("1\n");
			}
			continue;
		}
		sort(qrr + 1, qrr + 1 + q, [&](node x, node y) {
			return x.l < y.l;		
		});
		memset(b, 0, sizeof b);
		for (int i = 1, j = 1, k = 0; i <= q; ++i) {
			while (j <= n && j <= qrr[i].l) {
				if (b[a[j]] == 0) {
					b[a[j]] = 1;
					++k;
				}
				++j;
			}
			ans[qrr[i].id] = k;
		}
		sort(qrr + 1, qrr + 1 + q, [&](node x, node y){  
			return x.r > y.r; 		
		});
		memset(b, 0, sizeof b);
		for (int i = 1, j = n, k = 0; i <= q; ++i) {
			while (j >= 1 && j >= qrr[i].r) {
				if (b[a[j]] == 0) {
					b[a[j]] = 1;
					++k;
				}
				--j;
			}
			ans[qrr[i].id] += k;
		}
		memset(b, 0, sizeof b); 
		for (int i = 1; i <= n; ++i) {
			nx[i] = n + 1;
		}
		for (int i = n; i >= 1; --i) { 
			c[i] = nx[a[i]]; 
			if (nx[a[i]] == n + 1) {
				nx[a[i]] = i;    
			}
		}
		bit.init();
		sort(qrr + 1, qrr + 1 + q, [&](node x, node y){
			return x.l < y.l;		
		});
		for (int i = 1, j = 1; i <= q; ++i) {
			while (j <= n && j <= qrr[i].l) {
				if (b[a[j]] == 0) {
					bit.update(c[j], -1);
					b[a[j]] = 1;   	
				}
				++j; 
			}
			ans[qrr[i].id] += bit.query(qrr[i].r, n); 
		}
		for (int i = 1; i <= q; ++i) {
			printf("%d\n", ans[i]);
		}
	}
	return 0;
}
