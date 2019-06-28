#include <bits/stdc++.h>
using namespace std;

int main() {
	int n, m, k;
	while (scanf("%d%d%d", &n, &m, &k) != EOF) {
		if (min(m, k) >= n) {
			puts("YES");
		} else {
			puts("NO");
		}
	}
	return 0;
}
