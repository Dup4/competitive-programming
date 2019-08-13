#include <bits/stdc++.h>
using namespace std;

#define N 600010
int n;
int s[N];

int minRep(int *s, int len) {
	int i = 0, j = 1, k = 0;
	while (i < len && j < len && k < len) {
		int t = s[(i + k) % len] - s[(j + k) % len];
		if (!t) ++k;
		else {
			if (t > 0) i += k + 1;
			else if (t < 0) j += k + 1;
			if (i == j) j = i + 1;
			k = 0;
		}
	//	printf("%d %d %d\n", i, j, k);
	}
	return min(i, j);
}

int main() {
	while (scanf("%d", &n) != EOF) {
		for (int i = 0; i < n; ++i) scanf("%d", s + i);
		for (int i = n; i < 2 * n; ++i) s[i] = s[i - n];
		int x = minRep(s, n);
		for (int i = x; i < x + n; ++i)
			printf("%d%c", s[i], " \n"[i == x + n - 1]);
	}
	return 0;
}
