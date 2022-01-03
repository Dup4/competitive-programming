#include <bits/stdc++.h>
using namespace std;

int main() {
	int a[3], d;
	while (scanf("%d", a) != EOF) {
		for (int i = 1; i < 3; ++i) {
			scanf("%d", a + i);
		}
		scanf("%d", &d);
		sort(a, a + 3);
		int res = max(0, d - a[1] + a[0]) + max(0, d - a[2] + a[1]);
		printf("%d\n", res);
	}
	return 0;
}
