#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 10;
int n, a[N];

int main() {
	while (scanf("%d", &n) != EOF) {
		int l, r;
		if (n & 1) {
			l = n + 1, r = n; 
			a[++r] = n;
			for (int i = n - 1; i >= 1; i -= 2) {
				a[++r] = i;
				a[--l] = i - 1;
			}
		} else {
			l = n + 1, r = n;
			for (int i = n; i >= 1; i -= 2) {
				a[++r] = i;
				a[--l] = i - 1;
			}
		}
		for (int i = l; i <= r; ++i)
			printf("%d%c", a[i], " \n"[i == r]);
	}
	return 0;
}
