#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 10;
list <int> A[N], B[N];
int n, q;

int main() {
	while (scanf("%d%d", &n, &q) != EOF) {
		for (int i = 1; i <= n; ++i) {
			A[i].clear();
			B[i].clear();
		}
		for (int i = 1, op, u, v, w, val; i <= q; ++i) {
			scanf("%d%d", &op, &u);
			if (op == 1) {
				scanf("%d%d", &w, &val);
				if (w == 0) {
					A[u].push_front(val);
					B[u].push_back(val);
				} else {
					A[u].push_back(val);
					B[u].push_front(val);
				} 
			} else if (op == 2) {
				scanf("%d", &w);
				if (A[u].empty()) {
					puts("-1");
					continue;
				}
				if (w == 0) {
					printf("%d\n", A[u].front());
					A[u].pop_front();
					B[u].pop_back();
				} else {
					printf("%d\n", A[u].back());
					A[u].pop_back();
					B[u].pop_front();
				}
			} else {
				scanf("%d%d", &v, &w);
				//等价于A[v].reverse();
				if (w == 1) swap(A[v], B[v]);
				//v接在u后面
				A[u].splice(A[u].end(), A[v]);
				B[v].splice(B[v].end(), B[u]);
				swap(B[u], B[v]);
			}
		}
	}
	return 0;
}
