#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 500010
int n, m;

ll res;
struct SEG {
	struct node {
		ll Max, sum; 
		int cnt;
		node () {
			Max = sum = 0;
			cnt = 0;
		}
		void add(int x) {
			if (x > Max) { 
				res += 1ll * cnt * x - sum;
				sum = 1ll * cnt * Max;
				Max = x;  
			}
		}
		node operator + (const node &other) const {
			node res = node();
			res.cnt = cnt + other.cnt;
			res.Max = max(Max, other.Max);    
			res.sum = sum + other.sum;
		}
	}t[N << 2];
	void build(int id, int l, int r) {
		if (l == r) {
			t[id] = node();
			t[id].Max = l;
			t[id].sum = l;
			t[id].cnt = 1;  
			return;
		}
		int mid = (l + r) >> 1;
		build(id << 1, l, mid);
		build(id << 1 | 1, mid + 1, r);
		t[id] = t[id << 1] + t[id << 1 | 1];
	}
	void pushdown(int id) {
		int Max = t[id].Max; 
		t[id << 1].add(Max);
		t[id << 1 | 1].add(Max);
	}
	void update(int id, int l, int r, int ql, int qr) {
		if (l >= ql && r <= qr && qr < t[id].Max) {  
			t[id].add(qr);
			return;
		}
		if (l == r) {
			return;
		}
		int mid = (l + r) >> 1;
		pushdown(id);
		if (ql <= mid) update(id << 1, l, mid, ql, qr);
		if (qr > mid) update(id << 1 | 1, mid + 1, r, ql, qr);
		t[id] = t[id << 1] + t[id << 1 | 1];
	} 
}seg;

int main() {
	while (scanf("%d%d", &n, &m) != EOF) {
		seg.build(1, 1, n);
		for (int i = 1, l, r; i <= m; ++i) {
			scanf("%d%d", &l, &r);
			res = 0;
			seg.update(1, 1, n, l, r);
			printf("%lld\n", res);
		}
	}
	return 0;
}
