#include <bits/stdc++.h>
using namespace std;

#define db double
#define N 50010
int n, q;

#define ll long long
struct SEG {
	struct node {
		bool F;
		db k, b;
		node() {
			F = 0;
			k = b = 0;
		}
	}t[N << 2];
	void update(int id, int l, int r, db k, db b) {
		if (t[id].F == 0) {
			t[id].F = 1;
			t[id].k = k;
			t[id].b = b;
			return;
		}
		int mid = (l + r) >> 1;
		db &K = t[id].k, &B = t[id].b;
		db l1 = l * k + b, r1 = r * k + b;
		db l2 = l * K + B, r2 = r * K + B;
		if (l1 <= l2 && r1 <= r2) return;
		if (l1 > l2 && r1 > r2) {
			K = k;
			B = b;
			return;
		}
		//计算交点
		db x = (b - B) / (K - k);
		if (l1 > l2) {
			if (x > mid) {
				update(id << 1 | 1, mid + 1, r, K, B);
				K = k;
				B = b;
			} else {
				update(id << 1, l, mid, k, b); 
			}
		} else {
			if (x > mid) {
				update(id << 1 | 1, mid + 1, r, k, b);
			} else {
				update(id << 1, l, mid, K, B);
				K = k;
				B = b;
			}
		}
	}
	db query(int id, int l, int r, int x) {
		if (l == r) {
			return t[id].k * x + t[id].b;
		}
		int mid = (l + r) >> 1;
		db res = t[id].k * x + t[id].b;
		if (x <= mid) res = max(res, query(id << 1, l, mid, x));
		else res = max(res, query(id << 1 | 1, mid + 1, r, x));
		return res;
	}
}seg;

int main() {
	n = 50000;
	while (scanf("%d", &q) != EOF) {
		char op[20]; db k, b; int x;
		for (int _q = 1; _q <= q; ++_q) {
			scanf("%s", op + 1);
			switch(op[1]) {
				case 'P' :
					scanf("%lf%lf", &b, &k);
					seg.update(1, 1, n, k, b - k);
					break;
				case 'Q' :
					scanf("%d\n", &x);
					printf("%lld\n", (ll)(seg.query(1, 1, n, x) / 100));
					break;
			}
		}	
	}
	return 0;
}

