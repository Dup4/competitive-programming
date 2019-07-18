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
		ll p = 1e9, q = 1;  
		for (int i = 1; i <= 1000; ++i) {
			ll qq = i * i;
			ll pp = solve(i);
			if (pp * q < qq * p) {
				p = pp;
				q = qq;
			}
		}
		q *= m * m;
		ll G = gcd(p, q);
		p /= G;
		q /= G;
		if (q == 1) printf("%lld\n", p);
		else printf("%lld/%lld\n", p, q);
	}
	return 0;
}
