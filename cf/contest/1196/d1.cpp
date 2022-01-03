#include <bits/stdc++.h>
using namespace std;

#define N 2010
int n, k;
char s[N], nx[N];
int res;

void solve(int pre, int pos, int tmp) {
	for (int i = pos; i <= pos + k - 2; ++i) {
		if (s[i] != nx[pre]) {
			++tmp;
		}
		pre = nx[pre];
	}
	res = min(res, tmp);
}

int main() {
	nx['R'] = 'G';
	nx['G'] = 'B';
	nx['B'] = 'R';
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &n, &k);
		scanf("%s", s + 1);
		res = 1e9;
		for (int i = 1; i <= n - k + 1; ++i) {
			solve('R', i + 1, (s[i] != 'R'));
			solve('G', i + 1, (s[i] != 'G'));
			solve('B', i + 1, (s[i] != 'B'));
		}
		printf("%d\n", res);
	}
	return 0;
}
