#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 400010
ll res[N];
ll small[N];
ll tot[N];  
int n, m, q, c;
struct qnode {
	//0 加点
	//1 加贡献
	//-1 减贡献 
	int op, id, x, y, t, isleft;
	qnode () {}
	qnode (int op, int id, int x, int y, int t) : op(op), id(id), x(x), y(y), t(t) {
		isleft = 0;
	}
	bool operator < (const qnode &other) const {
		if (x != other.x) {
			return x < other.x;
		} 
		if (y != other.y) {
			return y < other.y;
		}
	   	return id < other.id;	
	}
}qrr[N << 1], trr[N << 1]; 

struct BIT {
	ll a[N];
	void init() {
		for (int i = 0; i <= n; ++i) {
			a[i] = 0;
		}
	}
	void update(int x, ll val) {
		for (; x <= n; x += x & -x) {
			a[x] += val;
		}
	}
	ll query(int x) {
		ll res = 0;
		for (; x > 0; x -= x & -x) {
			res += a[x];
		}
		return res;
	}
}bit[2];

void CDQ(int l, int r) {
	if (l == r) return;
	int mid = (l + r) >> 1;
	CDQ(l, mid); CDQ(mid + 1, r);
	for (int i = l; i <= r; ++i) {
		trr[i] = qrr[i];
		trr[i].isleft = i <= mid;
	}
	sort(trr + l, trr + r + 1, [](qnode a, qnode b) {
		if (a.t != b.t) {
			return a.t < b.t;
		}
		if (a.x != b.x) {
			return a.x < b.x; 
		}
		if (a.y != b.y) {
			return a.y < b.y;
		}
		return a.id < b.id;
	});
	for (int i = l; i <= r; ++i) {
		if (trr[i].isleft) { 
			if (trr[i].op == 0) {
				bit[0].update(trr[i].y, 1);
				bit[1].update(trr[i].y, trr[i].t);   
			}
		} else if (trr[i].op) { 
			res[trr[i].id] += 1ll * trr[i].op * (bit[1].query(trr[i].y) + 1ll * (c - trr[i].t - 1) * bit[0].query(trr[i].y));
			small[trr[i].id] += 1ll * trr[i].op * bit[0].query(trr[i].y);
		}
	}
	for (int i = l; i <= r; ++i) {
		if (trr[i].isleft) {
			if (trr[i].op == 0) {
				bit[0].update(trr[i].y, -1);
				bit[1].update(trr[i].y, -trr[i].t);
			}
		}
	}
}


int main() {
	while (scanf("%d%d%d", &n, &q, &c) != EOF) {
		m = 0;
		for (int i = 1, x, y, t; i <= n; ++i) {
			scanf("%d%d%d", &x, &y, &t);
			qrr[++m] = qnode(0, 0, x, y, t);
		}
		for (int i = 1, x[2], y[2], t; i <= q; ++i) {
			res[i] = 0;
			small[i] = 0;
			tot[i] = 0;
			scanf("%d%d%d%d%d", &t, x, y, x + 1, y + 1);
			qrr[++m] = qnode(1, i, x[0] - 1, y[0] - 1, c - t - 1);
			qrr[++m] = qnode(-1, i, x[0] - 1, y[1], c - t - 1);
			qrr[++m] = qnode(-1, i, x[1], y[0] - 1, c - t - 1);
			qrr[++m] = qnode(1, i, x[1], y[1], c - t - 1); 
		}
		bit[0].init();
		sort(qrr + 1, qrr + 1 + m);
		for (int i = 1; i <= m; ++i) {
			if (qrr[i].op == 0) {
				bit[0].update(qrr[i].y, 1); 
			} else {
				tot[qrr[i].id] += 1ll * qrr[i].op * bit[0].query(qrr[i].y);
			}
		}
		bit[0].init(); bit[1].init();
		CDQ(1, m); 
		for (int i = 1; i <= q; ++i) {
			printf("%lld\n", res[i] + 1ll * (tot[i] - small[i]) * c);
		}
	}
	return 0;
}
