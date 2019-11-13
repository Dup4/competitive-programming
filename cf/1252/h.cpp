#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 2e5 + 10;
int n, ce; 
struct E {
	ll x, y; int id;
	bool operator < (const E &other) const {
		return x < other.x;
	}
}e[N];

int main() {
	while (scanf("%d", &n) != EOF) {
		ce = 0;
		for (int i = 1, x, y; i <= n; ++i) {
			scanf("%d%d", &x, &y);
			e[++ce] = {x, y, i};
			e[++ce] = {y, x, i};
		}
		sort(e + 1, e + 1 + ce);
		priority_queue <E> pq; 
		ll res = 0;
		for (int i = ce; i >= 1; --i) {
			res = max(res, e[i].x * e[i].y);
			ll now = e[i].x;
			pq.push({e[i].y, e[i].x, e[i].id});
			while (pq.size() > 1) {
				E t1 = pq.top(); pq.pop();
				E t2 = pq.top(); pq.pop();
				if (t1.id == t2.id) {
					pq.push(t1);
				} else {
					pq.push(t1);
					pq.push(t2);
					break;
				}	
			}
			if (pq.size() > 1) {
				E t1 = pq.top(); pq.pop();
				E t2 = pq.top(); pq.pop();
				res = max(res, now * t2.x * 2);
				pq.push(t1);
				pq.push(t2);
			}
		}
		printf("%.1f\n", res * 1.0 / 2);
	}
	return 0;
}
