#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 200010
int n, l;
struct node {
	int a, b, c, d, e; 
	node() {}
	void scan() {
		scanf("%d%d%d%d%d", &a, &b, &c, &d, &e);
		c = a / c + (a % c ? 1 : 0);
		e = a / e + (a % e ? 1 : 0); 
	}
}a[N];
bool check(ll x) {
	ll len = 0;
	for (int i = 1; i <= n; ++i) {
		if (a[i].c > x) {
			return false;
		}
		if (a[i].e > x) {
			len += a[i].b;	
		} else {
			len += a[i].d;
		}
	}
	return len <= 1ll * l;
}

int main() {
	while (scanf("%d%d", &n, &l) != EOF) {
		int tot = 0;
		ll len = 0;
		for (int i = 1; i <= n; ++i) {
			a[i].scan();
			len += a[i].d; 
			tot = max(tot, a[i].e);
		}
		if (l < len) {
			puts("-1");
		} else {
			int l = 1, r = tot, res = -1;
			while (r - l >= 0) {
				ll mid = (l + r) >> 1;
				if (check(mid)) {
					r = mid - 1;
					res = mid;
				} else {
					l = mid + 1;
				}
			}
			printf("%d\n", res);
		}
	}
	return 0;
}
