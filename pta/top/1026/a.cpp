#include <bits/stdc++.h>
using namespace std;

const int N = 1e4 + 10;
int n, pre[N], a[N], b[N], f[N];

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) scanf("%d", a + i);
	for (int i = 1; i <= n; ++i) scanf("%d", b + i), f[i] = a[b[i]], f[i] += f[i - 1];
	memset(pre, 0, sizeof pre);
	int Max = 0, l = -1, r = -1;
	int P = 0;
	for (int i = 1; i <= n; ++i) {
		P = max(P, pre[b[i]]);
		pre[b[i]] = i;
		if (f[i] - f[P] > Max) {
			Max = f[i] - f[P];
			l = P;
			r = i - 1;
		}
	}
	printf("%d %d %d\n", Max, l, r);
	return 0;
}
