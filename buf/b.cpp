#include <cstdio>
 
int main() {
	int a[] = {0, 2, 2, 1, 2, 2, 2, 1};
    int x, y;
	while (scanf("%d%d", &x, &y) != EOF) {
		int res = 0;
		if (x < y) {
			for (int i = x; i < y; ++i)
				res += a[i];
		} else {
			for (int i = x; i <= 7; ++i) 
				res += a[i];
			for (int i = 1; i < y; ++i)
				res += a[i];
		}
		printf("%d\n", res);
	}
	return 0;
}
