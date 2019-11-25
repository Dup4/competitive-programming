#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
int n, b[N];

int main() {
	while (scanf("%d", &n) != EOF) {
		memset(b, 0, sizeof b);
		for (int i = 1, x; i <= n; ++i) {
			scanf("%d", &x);
			if (x >= 1 && x <= 100005) {
				b[x] = 1;
			} 
		}
		for (int i = 1; i <= 100006; ++i) {
			if (b[i] == 0) {
				printf("%d\n", i);
				break;
			}
		}
	}
	return 0;
}
