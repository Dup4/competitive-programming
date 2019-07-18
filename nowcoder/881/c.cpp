#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define db double
#define N 10010
int n;
ll m, a[N];
ll gcd(ll a, ll b) {
	return b ? gcd(b, a % b) : a;
}

struct node {
	int id, x;
	ll sum;
	node() {
		id = -1;
		x = sum = 0;
	}
	node(int id, int x, ll sum) : id(id), x(x), sum(sum) {}
	bool operator < (const node &other) const {
		return sum > other.sum; 
	}
};

ll solve(ll M) {
	ll tot = 0;
	priority_queue <node> pq;
	for (int i = 1; i <= n; ++i) {
		tot += a[i] * a[i] * M * M; 
		pq.push(node(i, 0, -2ll * a[i] * M * m + 1ll * m * m));  
	}
	ll T = M;
	while (T--) {
		node tmp = pq.top(); pq.pop();
		tot += tmp.sum;
		++tmp.x;
		tmp.sum = -2ll * a[tmp.id] * M * m + 1ll * m * m + 2ll * tmp.x * m * m;
		pq.push(tmp);	
	}
	return tot;
}

int main() {
	while (scanf("%d%lld", &n, &m) != EOF) {
		for (int i = 1; i <= n; ++i) scanf("%lld", a + i);
		ll l = 1, r = 1e3, res = -1;
		while (r - l >= 0) {
			ll midl = (l + r) >> 1;
			ll midr = (midl + r) >> 1;
			ll sl = solve(midl);
			ll sr = solve(midr);
			if (sl * midr * midr <= sr * midl * midl) {
				res = midl;
				r = midr - 1;
			} else {
				l = midl + 1;
			}
		}
		res = m;
		ll p = solve(res);
		ll G = gcd(p, res);
		p /= G; res /= G;
		if (res == 1) printf("%lld\n", p);
		else printf("%lld/%lld\n", p, res);
	}
	return 0;
}
