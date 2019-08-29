#include <bits/stdc++.h>
using namespace std;

const int N = 1e3 + 10;
int n, h[N], v[N];
bool ok() {
	for (int i = 1; i <= n; ++i) {
		if (h[i] != v[i]) {
			return h[i] > v[i];
		}
	}
	return 1;
}

int main() {
	while (scanf("%d", &n) != EOF) {
		for (int i = 1; i <= n; ++i) {
			scanf("%d", h + i);
		}
		for (int i = 1; i <= n; ++i) {
			scanf("%d", v + i);
		}
		for (int i = 0; i <= 1000; ++i) {
			if (ok()) {
				cout << i << "\n";
				break;
			}
			for (int j = 1; j <= n; ++j) ++h[j];
		}
	}
	return 0;
}
