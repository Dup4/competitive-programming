#include <bits/stdc++.h>
using namespace std;

#define N 100010
#define db double
int n;
db l[N], s[N], v[N];
db f[N];

int main() {
	while (scanf("%d", &n) != EOF) {
		for (int i = n; i >= 0; --i) scanf("%lf", l + i);
		for (int i = n; i >= 0; --i) scanf("%lf", s + i);
		for (int i = n; i >= 0; --i) scanf("%lf", v + i);
		f[0] = s[0] / v[0];
		for (int i = 1; i <= n; ++i) {
			f[i] = f[i - 1];
			f[i] = max(f[i], s[i] / v[i]);
			f[i] = max(f[i], f[i - 1] + (l[i - 1] / v[i]) + (s[i] - s[i - 1] - l[i - 1]) / v[i]);
		}
		printf("%.15f\n", f[n]);
	}
	return 0;
}
