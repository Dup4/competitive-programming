#include <bits/stdc++.h>
using namespace std;

int main() {
	int n, k;
	char *fi = "Adrien";
	char *se = "Austin";
	while (scanf("%d%d", &n, &k) != EOF) {
		if (n == 0 || (n % 2 == 0 && k == 1)) {
			puts(se);
		} else {
			puts(fi);
		}
	}
	return 0;
}
