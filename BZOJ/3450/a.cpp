#include <bits/stdc++.h>
using namespace std;

typedef double db;
const int N = 3e5 + 10;
int n;
char s[N];
db f[N], ans; 

int main() {
	scanf("%d%s", &n, s + 1);
	memset(f, 0, sizeof f); ans = 0;
	for (int i = 1; i <= n; ++i) {
		if (s[i] == 'o') {
			ans += f[i - 1] * 2 + 1;
			f[i] = f[i - 1] + 1;
		} else if (s[i] == 'x') {
			f[i] = 0;
		} else {
			ans += (f[i - 1] * 2 + 1) / 2;
			f[i] = (f[i - 1] + 1) / 2;
		}
	}
	printf("%.4f\n", ans);
	return 0;
}
