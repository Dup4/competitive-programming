#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 300010
#define pli pair <ll, int>
#define fi first
#define se second
int n, k;
ll a[N], sum[N];
struct node {
	ll a; int id;
	node() {}
	node (ll a, int id) : a(a), id(id) {}
	bool operator < (const node &other) const {
		if (a != other.a) {
			return a > other.a;
		}
		return id < other.id;
	}
};

int main() {
	while (scanf("%d%d", &n, &k) != EOF) {
		sum[0] = 0;
		for (int i = 1; i <= n; ++i) {
			scanf("%lld", a + i);
			sum[i] = sum[i - 1] + a[i];
		}
		priority_queue <node> pq; 
		int now = n;
		for (int i = k; i < n; ++i) { 
			pq.push(node(sum[i], i));  
		}
		ll res = 0;
		for (int i = k; i >= 1; --i) {
			pq.push(node(sum[i - 1], i - 1));
			if (i == 1) {
				res += (sum[now] - sum[0]);
				break;
			}
			while (!pq.empty()) {
				node t = pq.top(); pq.pop();
				if (t.id >= now) {
					continue;
				}
				res += 1ll * i * (sum[now] - t.a);
				now = t.id; 
				break;
			}
		}
		printf("%lld\n", res);
	}
	return 0;
}

