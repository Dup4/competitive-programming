#include <bits/stdc++.h>
using namespace std;

#define N 100010
int n, a[N];

int main() {
	while (scanf("%d", &n) != EOF) {
		multiset <int> se;
		for (int i = 1; i <= n; ++i) scanf("%d", a + i);
		for (int i = 1; i <= n; ++i) {
			if (se.empty()) {
				se.insert(a[i]);
			} else {
				auto pos = se.lower_bound(a[i]);
				if (pos != se.begin()) {
					--pos;
					se.erase(pos);
				}
				se.insert(a[i]);
			}
		}
		printf("%d\n", (int)se.size());
	}
	return 0;
}
