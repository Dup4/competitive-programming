#include <bits/stdc++.h>
using namespace std;

int n, t;

int main() {
	while (scanf("%d%d", &n, &t) != EOF) {
		int Min = 1e9, pos = -1;
		for (int i = 1, s, d; i <= n; ++i) {
			scanf("%d%d", &s, &d);
			int need = d * ((max(0, t - s) + (d - 1)) / d) + s; 
			if (need < Min) {
				Min = need;
				pos = i;
			}
		}
		printf("%d\n", pos);
	}
	return 0;
}
