#include <bits/stdc++.h>
using namespace std;
const int N = 3e5 + 10;
vector <list<int>> li;
int n, q;

int main() {
	int _T; scanf("%d", &_T);
	while (_T--) {
		scanf("%d%d", &n, &q);
		li.clear(); li.resize(n + 1);
		for (int i = 1, op, s, v, t; i <= q; ++i) {
			scanf("%d%d", &op, &s);
			if (op == 1) {
				scanf("%d", &v);
				li[s].push_front(v);
			} else if (op == 2) {
				if (li[s].empty()) puts("EMPTY");
				else {
					printf("%d\n", li[s].front());
					li[s].pop_front();
				}
			} else if (op == 3) {
				scanf("%d", &t);
				li[t].reverse();
				li[t].reverse();
				li[s].splice(li[s].begin(), li[t]);
				
			}
		}
	}
	return 0;
}
