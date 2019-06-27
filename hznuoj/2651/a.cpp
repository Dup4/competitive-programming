#include <bits/stdc++.h>
using namespace std;

#define N 100010
int n, k, a[N];

bool ok() {
	for (int i = 1; i <= n; ++i) {
		if (a[i] != 100) {
			return false;
		}
	}
	return true; 
}

int main() {
	while (scanf("%d%d", &n, &k) != EOF) {
		for (int i = 1; i <= n; ++i) {
			scanf("%d", a + i);
		}
		while (k--) {
			for (int i = 1; i <= n; ++i) { 
				a[i] = 10 * ceil(sqrt(a[i]));
			}
		}
		for (int i = 1; i <= n; ++i) {
			printf("%d%c", a[i], " \n"[i == n]);
		}
	}
	return 0;
}
