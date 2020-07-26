#include <bits/stdc++.h>
using namespace std;
const int N = 5e2 + 10;
const int mod = 1e9 + 7;
int n, r[N][N], b[N][N];

void chadd(int &x, int y) { x += y; if (x >= mod) x -= mod; }
int gaoR(int x, int y);
int gaoB(int x, int y);

//height x internal node y
int gaoR(int x, int y) {
	if (r[x][y] != -1) return r[x][y];
	if (x < 0) return 0;
	r[x][y] = 0;
	for (int i = 1; i < y - 1; ++i) {
		chadd(r[x][y], 1ll * gaoB(x - 1, i) * gaoB(x - 1, y - i - 1) % mod);
	}
	return r[x][y];
} 

int gaoB(int x, int y) {
	if (b[x][y] != -1) return b[x][y];
	if (x <= 0) return 0;
	b[x][y] = 0;
	for (int i = 1; i < y - 1; ++i) {
		chadd(b[x][y], 1ll * (gaoB(x - 1, i) + gaoR(x, i)) * (gaoB(x - 1, y - i - 1) + gaoR(x, y - i - 1)) % mod);
	}
	return b[x][y];
}

int main() {
	scanf("%d", &n);
	memset(r, -1, sizeof r);
	memset(b, -1, sizeof b);
	b[1][1] = 1;
	b[1][2] = 2;
	r[1][1] = 1;
	int res = 0;
	for (int i = 10; i >= 0; --i) {
		chadd(res, gaoB(i, n));
	}
	printf("%d\n", res);
	return 0;
}
