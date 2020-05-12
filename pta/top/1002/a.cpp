#include <bits/stdc++.h>
using namespace std;

const int N = 1100;
int n, f[N];

struct E { 
	int P, L, D; 
	bool operator < (const E &other) const { return D < other.D; }
}e[N];

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		scanf("%d%d%d", &e[i].P, &e[i].L, &e[i].D);
	}
	sort(e + 1, e + 1 + n);
	for (int i = 1; i <= n; ++i) {
		for (int j = e[i].D - e[i].L; j >= 0; --j) {
			f[j + e[i].L] = max(f[j + e[i].L], f[j] + e[i].P); 
		}
	}
	int res = 0;
	for (int i = 0; i <= 1000; ++i) res = max(res, f[i]);
	printf("%d\n", res);
	return 0;
}
