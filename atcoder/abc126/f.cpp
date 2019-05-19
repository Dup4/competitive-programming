#include <bits/stdc++.h>
using namespace std;

#define N 500010
int a[N];

int main() {
	int n, m, k;
	while (scanf("%d%d", &n, &k) != EOF) {
		m = (1 << n) - 1;
		n = 1 << (n + 1);
		if (k == 0) {
			for (int i = 0; i <= m; ++i) {
				printf("%d %d%c", i, i, " \n"[i == m]);
			}
		} else {
			int tot = 0;
			for (int i = 0; i <= m; ++i) {
				a[i] = i;
				tot ^= i;
			}
			if (tot == 0 && k <= m) {
				swap(a[0], a[k]);
				for (int i = 0; i <= m; ++i) {
					printf("%d ", a[i]);
				}
				reverse(a + 1, a + 1 + m);
				for (int i = 0; i <= m; ++i) {
					printf("%d%c", a[i], " \n"[i == m]);
				}
			} else {
				puts("-1");
			}			
		}
	}
	return 0;
}
