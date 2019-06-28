#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 100010
int n, a[N]; 
struct node {
	ll tot; int cnt;
	node() {}
	node (ll tot, int cnt) : tot(tot), cnt(cnt) {} 
	bool operator < (const node &other) const {
		if (tot == other.tot) {
			return cnt > other.cnt;
		}
		return tot < other.tot;
	}
};

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		for (int i = 1; i <= n; ++i) {
			scanf("%d", a + i);
		}
		//0表示上一次操作是买入
		//1表示上一次操作是卖出 
		priority_queue <node> pq[2];
		node res = node(0, 0);
		pq[0].push(node(-a[1], 1));
		node t1, t2;
		for (int i = 2; i <= n; ++i) {
			pq[0].push(node(-a[i], 1));
			if (!pq[0].empty()) {
				t1 = pq[0].top();
				pq[1].push(node(t1.tot + a[i], t1.cnt + 1));
			}
			if (!pq[1].empty()) {
				t2 = pq[1].top();
				pq[0].push(node(t2.tot - a[i], t2.cnt + 1));
			}
			if (!pq[1].empty()) {
				res = max(res, pq[1].top());
			}
		}
		printf("%lld %d\n", res.tot, res.cnt);
	}
	return 0;
}
