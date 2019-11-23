#include <bits/stdc++.h>
using namespace std;
template<class T>inline void read(T &res) {
	char c;T flag=1;
	while((c=getchar())<'0'||c>'9')if(c=='-')flag=-1;res=c-'0';
	while((c=getchar())>='0'&&c<='9')res=res*10+c-'0';res*=flag;
}
const int N = 3e3 + 2, mod = 2333;
int n, m, g[N][N], f[N][N];
int Move[][2] = {
	{1, 0},
	{0, -1},
};
inline bool ok(int x, int y) { 
	if (x < 1 || x > n || y < 1 || y > m) 
		return false; 
	return true;
}

int main() {
	while (scanf("%d%d", &n, &m) != EOF) {
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= m; ++j) {
				read(g[i][j]);
			}
		}
		memset(f, 0, sizeof f);
		f[n][1] = 1;
		for (int i = n; i >= 1; --i) {
			for (int j = 1; j <= m; ++j) {
				if (g[i][j]) {
					f[i][j] = 0;
				} else {
					for (int k = 0; k < 2; ++k) {
						int nx = i + Move[k][0];
						int ny = j + Move[k][1];
						if (ok(nx, ny)) {
							f[i][j] = (f[i][j] + f[nx][ny]) % mod;
						}
					}
				}
			}
		}
	//	for (int i = 1; i <= n; ++i)
	//		for (int j = 1; j <= m; ++j)
	//			printf("%d%c", f[i][j], " \n"[j == m]);
		printf("%d\n", f[1][m]);
	}
	return 0;
}
