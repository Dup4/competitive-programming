#include <bits/stdc++.h>
using namespace std;
const int N = 1e4 + 10;
int n, q, a[N];
struct Hash {
	vector <int> a;
	void init() { a.clear(); }
	void add(int x) { a.push_back(x); }
	void gao() { sort(a.begin(), a.end()); a.erase(unique(a.begin(), a.end()), a.end()); }
	int get(int x) { return lower_bound(a.begin(), a.end(), x) - a.begin() + 1; }
}hs;

struct E {
	int op, x, y, z;
	E() {}
	E(int op, int x, int y, int z) : op(op), x(x), y(y), z(z) {}
}e[N]; 

struct SEG {
	struct node {
		
	};
}seg;

int main() {
	while (scanf("%d%d", &n, &q) != EOF) {
		hs.init();
		for (int i = 1; i <= n; ++i) {
			scanf("%d", a + i);
			hs.add(a[i]);
		}
		for (int i = 1, x, y, z; i <= q; ++i) {
			static char op[10];
			scanf("%s", op);
			if (*op == 'Q') {
				scanf("%d%d%d", &x, &y, &z);
				e[i] = E(0, x, y, z);
			} else {
				scanf("%d%d", &x, &y);
				e[i] = E(1, x, y, 0);
				hs.add(y);
			}
		}
		hs.gao();
		for (int i = 1; i <= n; ++i) a[i] = hs.get(a[i]);
		for (int i = 1; i <= q; ++i) if (e[i].op) e[i].y = hs.get(e[i].y);
		
	}
	return 0;
}
