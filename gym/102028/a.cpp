#include <bits/stdc++.h>
using namespace std;

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		int a[4], res = 0;
		for (int i = 0; i < 4; ++i) {
			scanf("%d", a + i);
			res += (a[i] != 0);
		}
		if (res == 0) puts("Typically Otaku");
		else if (res == 1) puts("Eye-opener");
		else if (res == 2) puts("Young Traveller");
		else if (res == 3) puts("Excellent Traveller");
		else puts("Contemporary Xu Xiake");
	}
	return 0;
}
