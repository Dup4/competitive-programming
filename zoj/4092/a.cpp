#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 2010
int n, m, a, b, res;
ll k;
char s[N], G[N][N];
int Move[][2] = {
	{0, 1},
	{0,-1},
	{1, 0},
	{-1, 0},
	{0, 0},
};

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		res = 0; 
		scanf("%d%d", &n, &m);
		scanf("%d%d%lld", &a, &b, &k);
		scanf("%s", s + 1);
		for (int i = 1; i <= n; ++i) {
			scanf("%s", G[i] + 1);
		}
		k = min(k, 1000000ll);
		for (int i = 1; i <= k; ++i) {
			int t = 1, x = 1;
			for (int j = 0; j < 5; ++j) {
				x += t * (G[a + Move[j][0]][b + Move[j][1]] - '0');
				t *= 3;
			}
			if (s[x] == 'I') {
				continue;
			} else if (s[x] == 'P') {
				if (G[a][b] == '2') {
					++res;
					G[a][b] = '0';
				}
			} else if (s[x] == 'U') {
				int na = a - 1, nb = b;
				if (G[na][nb] != '1') {
					a = na, b = nb;
				}
			} else if (s[x] == 'D') {
				int na = a + 1, nb = b;
				if (G[na][nb] != '1') {
					a = na, b = nb;
				}
			} else if (s[x] == 'L') {
				int na = a, nb = b - 1;
				if (G[na][nb] != '1') {
					a = na, b = nb;
				}
			} else {
				int na = a, nb = b + 1;
				if (G[na][nb] != '1') {
					a = na, b = nb;
				}
			}
		}			
		printf("%d\n", res);
	}
	return 0;
}
