#include <bits/stdc++.h>

using namespace std;

using db = double;

const int N = 1e5 + 10;

int n, k;
db w[N];

int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		scanf("%d %d", &n, &k);
		db sum = 0;
		for (int i = 1; i <= n; ++i) {
			scanf("%lf", w + i);
			sum += w[i];
		}
		for (int i = 1; i <= n; ++i) {
			w[i] += k * w[i] / sum;
		}
		for (int i = 1; i <= n; ++i) {
			printf("%.10f%c", w[i], " \n"[i == n]);
		}
	}
	return 0;
}
