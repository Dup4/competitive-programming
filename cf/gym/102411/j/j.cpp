#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N = 510;

int n;
char a[N][N];
int res[N][N];

int main() {
	while (scanf("%d", &n) != EOF) {
		memset(res, 0, sizeof res);
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= n; ++j) {
				scanf(" %c", &a[i][j]);
			}
		}
		for (int i = 1; i <= n; ++i) {
			for (int j = i + 1; j <= n; ++j) {
				int sum = 0;
				for (int k = i + 1; k < j; ++k) {
					if (res[i][k]) sum += a[k][j] - '0';
				}
				if ((sum + 1) % 10 == a[i][j] - '0') res[i][j] = 1;
			}
		}
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= n; ++j) {
				printf("%d", res[i][j]);
			}
			puts("");
		}
	}
	return 0;
}
