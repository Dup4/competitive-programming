#include <bits/stdc++.h>
using namespace std;

int main() {
	int _T; scanf("%d", &_T);
	while (_T--) {
		int n; scanf("%d", &n);
		if (n < 6) puts("-1");
		else if (n % 2 == 0) printf("%d %d\n", 2, n - 2);
		else printf("%d %d\n", 3, n - 3);
	}
	return 0;
}
