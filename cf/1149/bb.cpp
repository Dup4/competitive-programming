#include <bits/stdc++.h>
using namespace std;

#define N 100010
#define M 251
#define SZE(s) (int(s.size()))
int n, q;
char s[N];
int t[N][30];
int id[30]; 
string str[3];
int f[M][M][M];

void update(int &x, int v) {
	if (x == -1 || x > v) {
		x = v;
	}
}
void update(int x, int y, int z) {
	f[x][y][z] = n + 1;
	if (x && f[x - 1][y][z] != n + 1) {
		update(f[x][y][z], t[f[x - 1][y][z]][str[0][x - 1] - 'a']);
	}
	if (y && f[x][y - 1][z] != n + 1) {
		update(f[x][y][z], t[f[x][y - 1][z]][str[1][y - 1] - 'a']);
	}
	if (z && f[x][y][z - 1] != n + 1) {
		update(f[x][y][z], t[f[x][y][z - 1]][str[2][z - 1] - 'a']);
	}
}

int main() {
	while (scanf("%d%d", &n, &q) != EOF) {
		memset(f, -1, sizeof f);
		f[0][0][0] = 0;
		scanf("%s", s + 1);
		for (int i = 0; i < 26; ++i) {
				id[i] = n + 1;
			}
		for (int i = n; i >= 0; --i) {
			for (int j = 0; j < 26; ++j) {
					t[i][j] = id[j];   
			}
			if (i) {
				id[s[i] - 'a'] = i;
			}
		}
		for (int i = 0; i < 3; ++i) {
			str[i] = "";
		}
		int pos; char op[10], ts[10];
		while (q--) {
			scanf("%s%d", op, &pos);
			--pos;
			switch(op[0]) {
				case '+' :
					scanf("%s", ts);
					str[pos] += ts[0];
					int len[3];
					for (int i = 0; i < 3; ++i) {
						len[i] = SZE(str[i]);
					}
					switch (pos) {
						case 0 :
							for (int i = 0; i <= len[1]; ++i) {
								for (int j = 0; j <= len[2]; ++j) {
									update(len[0], i, j);
								}
							}
							break;
						case 1 :
							for (int i = 0; i <= len[0]; ++i) {
								for (int j = 0; j <= len[2]; ++j) {
									update(i, len[1], j);
								}
							}
							break;
						case 2 :
							for (int i = 0; i <= len[0]; ++i) {
								for (int j = 0; j <= len[1]; ++j) {
									update(i, j, len[2]);
								}
							}
							break;
						default :
							assert(0);
					}
					break;
				case '-' :
					str[pos].pop_back();
					break;
				default : 
					assert(0);
			}
			puts(f[SZE(str[0])][SZE(str[1])][SZE(str[2])] <= n ? "YES" : "NO");
		}
	}
	return 0;
}

