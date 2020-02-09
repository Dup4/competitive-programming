#include <bits/stdc++.h>
#include <bits/extc++.h>
using namespace std;
using namespace __gnu_cxx;
const int N = 1e6 + 10;
int n, q, a[N];
rope<int> *t[N];

int main() {
	while (scanf("%d%d", &n, &q) != EOF) {
		for (int i = 1; i <= n; ++i) scanf("%d", a + i);
		t[0] = new rope<int> (a, a + 1 + n);
		for (int i = 1, back, op, x, y; i <= q; ++i) {
			scanf("%d%d%d", &back, &op, &x);
			t[i] = new rope<int>(*t[back]);
			if (op == 1) {
				scanf("%d", &y);
				t[i]->replace(x, y);
			} else if (op == 2) {
				printf("%d\n", t[i]->at(x));
			}
		}
	}
	return 0;
}
