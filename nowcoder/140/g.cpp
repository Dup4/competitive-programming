#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 500010
int n, a[N], b[N];
ll T;
struct node {
	ll x; int a;
	node() {}
	node (ll x, int a) : x(x), a(a) {}
	bool operator < (const node &other) const {
		return x < other.x; 
	}
};

int main() {
	while (scanf("%d%lld", &n, &T) != EOF) {
		for (int i = 1; i <= n; ++i) {
			scanf("%d", x + i);
		}
		for (int i = 1; i <= n; ++i) {
			scanf("%d", a + i);
		}
		if (n == 1) {
			printf("%d\n", a[1]);
			continue;
		}
		vector <ll> lazy(2, 0), num(2, 0);
		ll res = 0;
		for (int i = 2; i <= n; ++i) {
			pq[1].emplace(x[i] - x[1], a[i]);
			pq[1].emplace
		}
		
				
	}
	return 0;
}
