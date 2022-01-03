#include <bits/stdc++.h>

using namespace std;

int a[100];

int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		for (int i = 0; i < 10; ++i) scanf("%d", a + i);
		int Min = a[0] + 2;
		for (int i = 1; i < 10; ++i) Min = min(Min, a[i] + 1);
		if (Min == a[0] + 2) {
			printf("1");
			for (int i = 1; i <= a[0] + 1; ++i) printf("0");
			puts("");
		} else {
			for (int i = 1; i < 10; ++i) {
				if (Min == a[i] + 1) {
					for (int j = 1; j <= a[i] + 1; ++j) printf("%d", i);
					puts("");
					break;
				}
			}
		}
	}
	return 0;
}
