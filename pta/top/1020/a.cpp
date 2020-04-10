#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e6 + 10;
int n;
char s[N];
int pos[220];
ll f[N][4];

int main() {
	while (scanf("%s", s + 1) != EOF) {
		memset(pos, -1, sizeof pos);
		n = strlen(s + 1);
		f[0][0] = 1;
		for (int i = 1; i <= n; ++i) {
			int d = pos[s[i]];
			pos[s[i]] = i;
			f[i][0] = f[i][1] = 1;
			for (int j = 1; j < 4; ++j) {
				f[i][j] += f[i - 1][j];
				f[i][j + 1] = f[i - 1][j];
				if (d != -1 && j - i + d >= 0)
					f[i][j] -= f[d - 1][j - i + d];
			}
		}
		printf("%lld\n", f[n][0] + f[n][1] + f[n][2]);
	}
	return 0;
}

