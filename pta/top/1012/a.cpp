#include <bits/stdc++.h>
using namespace std;
using pII = pair<int, int>;
#define fi first
#define se second
const int N = 20;
char G[N][N];
int n, num;
pII obs[N];



int main() {
	scanf("%d%d", &n, &num);
	for (int i = 0; i < num; ++i) scanf("%d%d", &obs[i].fi, &obs[i].se);
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			if (i == 1 || j == 1 || i == n || j == n) {
				G[i][j] = '#';
			}
			for (int k = 0; k < num; ++k) {
				if (i == obs[k].fi && j == obs[k].se) {
					G[i][j] = '@';
				}
			}
		}
	}



	return 0;
}
