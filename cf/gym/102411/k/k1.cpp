#include <bits/stdc++.h>
using namespace std;
#define dbg(x...) do { cout << "\033[32;1m" << #x << " -> "; err(x); } while(0)
void err() { cout << "\033[39;0m" << endl; }
template <class T, class... Ts> void err(const T&arg, const Ts&... args) { cout << arg << " "; err(args...); }
const int N = 1e3 + 10;
const int INF = 0x3f3f3f3f;
int n, m, ax, ay;
char str[N][N], stra[N][N], strb[N][N];
int up[N][N], down[N][N];
int X[N], Y[N];

void gaoA(char str[][N], int l, int r) {
	int MinU = INF, MinD = INF;
	for (int i = l; i <= r; ++i) {
		MinU = min(MinU, up[ax][i]);
		MinD = min(MinD, down[ax][i]);
	}
	for (int i = l; i <= r; ++i) {
		for (int j = 1; j <= MinU; ++j) {
			str[ax - j + 1][i] = 'a';
		}
		for (int j = 1; j <= MinD; ++j) {
			str[ax + j - 1][i] = 'a';
		}
	}
	str[ax][ay] = 'A';
}

void gaoU(char str[][N]) {
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			if (str[i][j] > 'A' && str[i][j] <= 'Z') {
				up[i][j] = i;
				for (int o = 1; ; ++o) {
					if (i - o < 1) break;
					if (str[i - o][j] != '.') break;
					up[i][j] = i - o;
					str[i - o][j] = str[i][j] - 'A' + 'a';
				}
			}	
		}
	}
}

void gaoD(char str[][N]) {
	for (int i = 1; i <= n; ++i) {
		for (int j = m; j >= 1; --j) {
			if (str[i][j] > 'A' && str[i][j] <= 'Z') {
				down[i][j] = i;
				for (int o = 1; ; ++o) {
					if (i + o > n) break;
					if (str[i + o][j] != '.') break;
					down[i][j] = i + o;
					str[i + o][j] = str[i][j] - 'A' + 'a'; 
				}
			}
		}
	}
}

void gaoL(char str[][N]) {
	for (int j = 1; j <= m; ++j) {
		for (int i = 1; i <= n; ++i) {
			if (str[i][j] > 'A' && str[i][j] <= 'Z') {
				for (int o = j - 1; o >= 1; --o) {
					int F = 1;
					for (int k = up[i][j]; k <= down[i][j]; ++k) { 
						if (str[k][o] != '.') {
							F = 0;
							break;
						}
					}
					if (!F) break;
					for (int k = up[i][j]; k <= down[i][j]; ++k) {
						str[k][o] = str[i][j] - 'A' + 'a';
					}
				}
			}
		}
	}
}

void gaoR(char str[][N]) {
	for (int j = m; j >= 1; --j) {
		for (int i = 1; i <= n; ++i) { 
			if (str[i][j] > 'A' && str[i][j] <= 'Z') { 
				for (int o = j + 1; o <= m; ++o) { 
					int F = 1; 
					for (int k = up[i][j]; k <= down[i][j]; ++k) {
						if (str[k][o] != '.') {
							F = 0;
							break;
						}
					}
					if (!F) break;
					for (int k = up[i][j]; k <= down[i][j]; ++k) {
						str[k][o] = str[i][j] - 'A' + 'a';
					}
				}
			}
		}
	}
}


void gaoU1(char str[][N]) {
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			if (str[i][j] > 'A' && str[i][j] <= 'Z') {
				for (int o = i - 1; o >= 1; --o) {
					int F = 1;
					for (int k = up[i][j]; k <= down[i][j]; ++k) {
						if (str[o][k] != '.') {
							F = 0;
							break;
						}
					}
					if (!F) break;
					for (int k = up[i][j]; k <= down[i][j]; ++k) {
						str[o][k] = str[i][j] - 'A' + 'a';
					}
				}
			}
		}
	}
}

void gaoD1(char str[][N]) {
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			if (str[i][j] > 'A' && str[i][j] <= 'Z') {
				for (int o = i + 1; o <= n; ++o) {
					int F = 1;
					for (int k = up[i][j]; k <= down[i][j]; ++k) {
						if (str[o][k] != '.') {
							F = 0;
							break;
						}
					}
					if (!F) break;
					for (int k = up[i][j]; k <= down[i][j]; ++k) {
						str[o][k] = str[i][j] - 'A' + 'a';
					}
				}
			}
		}
	}
}

void gaoL1(char str[][N]) { 
	for (int j = 1; j <= m; ++j) {
		for (int i = 1; i <= n; ++i) {
			if (str[i][j] > 'A' && str[i][j] <= 'Z') {
				up[i][j] = j; 
				for (int o = 1; ; ++o) {
					if (j - o < 1) break; 
					if (str[i][j - o] != '.') break;
					up[i][j] = j - o; 
					str[i][j - o] = str[i][j] - 'A' + 'a';
				}
			}	
		}
	}
}

void gaoR1(char str[][N]) {
	for (int j = m; j >= 1; --j) {
		for (int i = 1; i <= n; ++i) {
			if (str[i][j] > 'A' && str[i][j] <= 'Z') {
				down[i][j] = j;
				for (int o = 1; ; ++o) {
					if (j + o > m) break;
					if (str[i][j + o] != '.') break;
					down[i][j] = j + o;
					str[i][j + o] = str[i][j] - 'A' + 'a';
				}
			}
		}
	}
}

void print(char str[][N]) {
	for (int i = 1; i <= n; ++i) printf("%s\n", str[i] + 1);
}

bool ok(char str[][N]) {
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			if (str[i][j] == '.')
				return false;
		}
	}
	return true;
}

int main() {
	while (scanf("%d %d", &n, &m) != EOF) {
		for (int i = 1; i <= n; ++i) {
			scanf("%s", str[i] + 1);
		}
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= m; ++j) {
				if (str[i][j] == 'A') {
					ax = i, ay = j;
				}
			}
		}
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= m; ++j) {
				if (i == 1) {
					if (str[i][j] == '.' || str[i][j] == 'A') up[i][j] = 1;
					else up[i][j] = 0;
				} else {
					if (str[i][j] == '.' || str[i][j] == 'A') up[i][j] = up[i - 1][j] + 1;
					else up[i][j] = 0;
				}
			}
		}
		for (int i = n; i >= 1; --i) {
			for (int j = 1; j <= m; ++j) {
				if (i == n) {
					if (str[i][j] == '.' || str[i][j] == 'A') down[i][j] = 1;
					else down[i][j] = 0;
				} else {
					if (str[i][j] == '.' || str[i][j] == 'A') down[i][j] = down[i + 1][j] + 1;
					else down[i][j] = 0;
				}
			}
		}
		// get A size
		int Max = -1, Maxl = -1 ,Maxr = -1;
		for (int l = 1; l <= m; ++l) {
			int MinU = INF, MinD = INF;
			for (int r = l; r <= m; ++r) {
				MinU = min(MinU, up[ax][r]);
				MinD = min(MinD, down[ax][r]);
				if (r >= ay && l <= ay) {
					if (Max < (r - l + 1) * (MinU + MinD - 1)) {
						Maxl = l, Maxr = r, Max = (r - l + 1) * (MinU + MinD - 1);
					}
				}
			}
		}
		// color A size
		gaoA(str, Maxl, Maxr);
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= m; ++j) {
				stra[i][j] = str[i][j];
				strb[i][j] = str[i][j];
			}
		}

		gaoU(stra);
		gaoD(stra);
		gaoL(stra);
		gaoR(stra);

		gaoL1(strb);
		gaoR1(strb);
		gaoU1(strb);
		gaoD1(strb);

		if (ok(strb)) print(strb);
		else if (ok(stra)) print(stra);
		else assert(0);
	}
	return 0;
}
