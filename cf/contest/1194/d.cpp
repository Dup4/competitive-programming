#include <bits/stdc++.h>
using namespace std;

int main() {
	char *fi = "Alice";
	char *se = "Bob"; 
	int T, n, k; scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &n, &k);
		if (n == 0) puts(se);
		else {
			if (k % 3) {
				if (n % 3 == 0) puts(se);
				else puts(fi);
			} else {
				k /= 3;
				int p = (k - 1) * 3 + 4;
				n = (n - 1) % p + 1;
				if (n <= (k - 1) * 3) {
					if (n % 3 == 0) puts(se);
					else puts(fi);
				} else {
					n -= (k - 1) * 3;
					if (n == 4) puts(se);
					else puts(fi);
				}
			}
		}
	}
	return 0;
}
