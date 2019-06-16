#include <bits/stdc++.h>
using namespace std;

//1 m
//2 s
//3 p
//4 z
#define pii pair <int, int>
#define fi first
#define se second 
int a[5][10];
char s[10], fmp[5]; int mp[220];
void get() {
	int id = s[1] - '0';
	int tp = mp[(int)s[2]];
	++a[tp][id];
}
bool F;
void DFS(int x, int y) {
	if (x == 4 && y == 1) {
		F = 1;
		return;
	}
	if (x > 4 || y > 1) {
		return;
	}
	for (int i = 1; i <= 3; ++i) {
		for (int j = 1; j <= 9; ++j) {
			if (a[i][j] >= 3) {
				a[i][j] -= 3;
				DFS(x + 1, y);
				a[i][j] += 3;
				if (F) return;
			}
			if (j >= 3 && a[i][j] >= 1 && a[i][j - 1] >= 1 && a[i][j - 2] >= 1) {
				--a[i][j]; --a[i][j - 1]; --a[i][j - 2];
				DFS(x + 1, y);
				++a[i][j]; ++a[i][j - 1]; ++a[i][j - 2];
				if (F) return;
			}
			if (a[i][j] >= 2) {
				a[i][j] -= 2;
				DFS(x, y + 1);
				a[i][j] += 2;
				if (F) return;
			}
		}
	}
	for (int j = 1; j <= 7; ++j) {
		if (a[4][j] >= 2) {
			a[4][j] -= 2;
			DFS(x, y + 1);
			a[4][j] += 2;
			if (F) return;
		}
		if (a[4][j] >= 3) {
			a[4][j] -= 3;
			DFS(x + 1, y);
			a[4][j] += 3;
			if (F) return;
		}
	}
	
}

int main() {
	mp['m'] = 1; fmp[1] = 'm';
	mp['s'] = 2; fmp[2] = 's';
	mp['p'] = 3; fmp[3] = 'p';
	mp['z'] = 4; fmp[4] = 'z';
	while (scanf("%s", s + 1) != EOF) {
		memset(a, 0, sizeof a);
		get();
		for (int i = 1; i <= 12; ++i) {
			scanf("%s", s + 1);
			get(); 
		}
		vector <pii> res;
		for (int i = 1; i <= 3; ++i) {
			for (int j = 1; j <= 9; ++j) {
				++a[i][j];
				if (a[i][j] <= 4) {
					F = 0; DFS(0, 0);
					if (F) {
						res.push_back(pii(i, j));
					}
				}
				--a[i][j];
			}
		}
		for (int i = 1; i <= 7; ++i) {
			++a[4][i];
			if (a[4][i] <= 4) {
				F = 0; DFS(0, 0);
				if (F) {
					res.push_back(pii(4, i));
				}
			}
			--a[4][i];
		}
		for (auto it : res) {
			printf("%d%c\n", it.se, fmp[it.fi]);
		}
	}
	return 0;
}
