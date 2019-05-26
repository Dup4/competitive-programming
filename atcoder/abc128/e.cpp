#include <bits/stdc++.h>
using namespace std;

#define N 200010
#define pii pair <int, int>
#define fi first
#define se second
int n, q;
struct node {
	int s, t, x;
	void scan() {
		scanf("%d%d%d", &s, &t, &x); 
		s -= x;
		t -= x; 
	}
	bool operator < (const node &other) const {
		return x < other.x; 
	}
}qrr[N];
set <pii> se;
int res[N];

int main() {
	while (scanf("%d%d", &n, &q) != EOF) {
		memset(res, -1, sizeof res);
		se.clear(); 
		for (int i = 1; i <= n; ++i) {
			qrr[i].scan();
		}
		sort(qrr + 1, qrr + 1 + n);
		for (int i = 1, d; i <= q; ++i) {
			scanf("%d", &d);
			se.insert(pii(d, i)); 
		}
		for (int i = 1; i <= n; ++i) {
			if (qrr[i].t <= 0) {
				continue;
			}
			while (!se.empty()) {
				auto pos = se.lower_bound(pii(qrr[i].s, -1));
				if (pos == se.end()) {
					break;
				}
				if ((*pos).fi < qrr[i].t) {
					res[(*pos).se] = qrr[i].x;
					se.erase(pos);
				} else {
					break;
				}
			}
		}
		for (int i = 1; i <= q; ++i) {
			printf("%d\n", res[i]); 
		}
	}
	return 0;
}
