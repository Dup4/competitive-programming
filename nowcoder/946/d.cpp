#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 100010
const ll p = 1e9 + 7;
template <class T>
void add(T &x, T y) {
	x += y;
	if (x >= p) x -= p;
}
int n, m; ll a[N];
struct node {
	int op, l, r;
	node() {}
	void scan() {
		scanf("%d%d%d", &op, &l, &r);
	}
}q[N];
struct BIT {
	ll a[N];
	void init() {
		memset(a, 0, sizeof a);
	}
	void update(int x, int v) {
		for (; x < N; x += x & -x) {
			add(a[x], 1ll * v);
		}
	}
	ll query(int x) {
		ll res = 0;
		for (; x > 0; x -= x & -x) {
			add(res, a[x]);
		}
		return res;
	}
}bit;

int main() {
	while (scanf("%d%d", &n, &m) != EOF) {
		for (int i = 1; i <= m; ++i) q[i].scan();
		bit.init();
		memset(a, 0, sizeof a);
		for (int i = m, t, l, r; i >= 1; --i) {
			t = bit.query(i) + 1;
			l = q[i].l; r = q[i].r;
			switch(q[i].op) {
				case 1 :
					add(a[l], 1ll * t);
					add(a[r + 1], (p - t) % p);
					break;
				case 2 :
					bit.update(l, t);
					bit.update(r + 1, (p - t) % p);
					break;
			}
		}
		for (int i = 1; i <= n; ++i) {
			add(a[i], a[i - 1]);
			printf("%lld%c", a[i], " \n"[i == n]);
		}
	}
	return 0;
}
