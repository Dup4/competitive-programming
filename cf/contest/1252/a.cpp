#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
int n, a[N], b[N];

int main() {
	while (scanf("%d", &n) != EOF) {
		for (int i = 1; i <= n; ++i) scanf("%d", a + i);
		for (int i = 1; i <= n; ++i) b[i] = n - i + 1;
		for (int i = 1; i <= n; ++i)
			printf("%d%c", b[a[i]], " \n"[i == n]);
	}
	return 0;
}
