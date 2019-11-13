#include <cstdio>
#include <cstring>
const int N = 1e5 + 10;
int n, f[N][3];

int main() {
	while (scanf("%d", &n) != EOF) {
		memset(f, 0, sizeof f);
		f[0][0] = 1;
		for (int i = 1; i <= n; ++i) {
			for (int j = 0; j < 3; ++j) {
				f[i][0] += f[i - 1][j]; 
				if (i > 1 && j < 2) {
					f[i][j + 1] += f[i - 2][j];
				}	
			}
		}
		printf("%d\n", f[n][0] + f[n][1] + f[n][2]); 
	}
	return 0;
}
