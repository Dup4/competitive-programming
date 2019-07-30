#include <bits/stdc++.h>
using namespace std;
#define debug(...) { printf("#  "); printf(__VA_ARGS__); puts(""); }
#define pii pair <int, int>
#define fi first
#define se second
const int N = 1e6 + 10;
int n, q;
pii a[N];
int b[N], res[N];
vector <vector<int>> vec;

int main() {
	while (scanf("%d", &n) != EOF) {
		for (int i = 1; i <= n; ++i) scanf("%d", &a[i].fi), a[i].se = 0, res[i] = a[i].fi;
		scanf("%d", &q);
		vec.clear(); vec.resize(q + 10);
		int op, p, x;
		for (int i = 1; i <= q; ++i) {
			scanf("%d", &op);
			if (op == 1) {
				scanf("%d%d", &p, &x);
				a[p] = pii(x, i);
				res[p] = x;
			} else {
				scanf("%d", &x); 
				b[i] = x; 
			}
		}
		for (int i = 1; i <= n; ++i) {
			vec[a[i].se].push_back(i);
		}
		int Max = 0;
		for (int i = q; i >= 0; --i) {
			Max = max(Max, b[i]);
			for (auto it : vec[i]) {
				res[it] = max(res[it], Max); 
			}
		}
		for (int i = 1; i <= n; ++i) printf("%d%c", res[i], " \n"[i == n]);
	}
	return 0;
}
