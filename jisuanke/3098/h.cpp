#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 200010
int n, q, a[N], b[N];
ll c[N], d[N];
ll H[N << 1]; int tot;
int res[N]; 
vector <vector<ll>> vec;
struct node {
	ll x, y;
	node() {}
	node (ll x, ll y) : x(x), y(y) {}
}qrr[N];

void FWT(ll *a, int len, int mode) {
	for (int i = 1; i < len; i <<= 1) {
		for (int p = i << 1, j = 0; j < len; j += p) {
			for (int k = 0; k < i; ++k) {
				if (mode == 1) a[i + j + k] = (a[j + k] + a[i + j + k]);
				else a[i + j + k] = (a[i + j + k] - a[j + k]);
			}
		}
	}
}

struct BIT {
	int a[N];
	void init() {
		memset(a, 0, sizeof a);
	}
	void update(int x, int v) {
		for (; x < N; x += x & -x) {
			a[x] += v;
		}
	}
	int query(int x) {
		int res = 0;
		for (; x > 0; x -= x & -x) {
			res += a[x];
		}
		return res;
	}
}bit[2];

int id(ll x) {
	return lower_bound(H + 1, H + 1 + tot, x) - H;
}

int main() {
	int len = 1;
	while (len < 100000) len <<= 1;
	vec.clear(); vec.resize(len + 1);
	vec[0].push_back(0); vec[1].push_back(1);
	for (int i = 2; i <= len; ++i) {
		int it = i;
		vec[i].push_back(it); 
		while (it) {
			it = floor(sqrt(it));
			vec[i].push_back(it);
			if (it == 1) break;
		}
		
	}	
	while (scanf("%d", &n) != EOF) {
		for (int i = 1; i <= n; ++i) scanf("%d", a + i);
		for (int i = 1; i <= n; ++i) scanf("%d", b + i);
		memset(c, 0, sizeof c);
		memset(d, 0, sizeof d);
		for (int i = 1; i <= n; ++i) ++c[a[i]], ++d[b[i]];
		FWT(c, len, 1);
		FWT(d, len, 1);
		for (int i = 0; i < len; ++i) c[i] = c[i] * d[i];
		FWT(c, len, -1);
		for (int i = 0; i < len; ++i) c[i] += c[i - 1];
		scanf("%d", &q);
		tot = 0;
		ll x, y;
		for (int i = 1; i <= q; ++i) {
			scanf("%lld%lld", &x, &y);
			H[++tot] = x;
			H[++tot] = y;
			qrr[i] = node(x, y);
			res[i] = -1;   
		}
		sort(H + 1, H + 1 + tot);
		tot = unique(H + 1, H + 1 + tot) - H - 1;
		bit[0].init(); bit[1].init();
		for (int i = 1; i <= q; ++i) {
			if (qrr[i].x == 0) {
				int del = bit[0].query(id(qrr[i].y)) - bit[1].query(id(qrr[i].y) - 1); 
				int num = lower_bound(c + 1, c + len, qrr[i].y) - c;
				del = min(del, (int)vec[num].size() - 1);
				res[i] = vec[num][del];
			} else {
				bit[0].update(id(qrr[i].x), 1);
				bit[1].update(id(qrr[i].y), 1);
			}
		}
		for (int i = 1; i <= q; ++i) if (res[i] != -1) printf("%d\n", res[i]);
	}
	return 0;
}
