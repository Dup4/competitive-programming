#include <bits/stdc++.h>
using namespace std;

int main() {
	int _T; scanf("%d", &_T);
	while (_T--) {
		int a, b, c;
		scanf("%d%d%d", &a, &b, &c);
	//	int res = max((a + b + c + 2) / 3, min(a, c));
	//	printf("%d\n", res);
		if (a < c) swap(a, c);
		int A[3] = {a / 2, a - a / 2, c};
		while (b) {
			sort(A, A + 3);
			++A[0];
			--b;
		}
		printf("%d\n", max(A[0], max(A[1], A[2])));
	}
	return 0;
}
