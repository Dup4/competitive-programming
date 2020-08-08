#include <bits/stdc++.h>
using namespace std;
constexpr int N = 1e2 + 10, mod = 1e9 + 7, Mod = 666; 
char s[N];
int a[N], bit[N];
int f[55][668][2][2], n;

inline void chadd(int &x, int y) { x += y; if (x >= mod) x -= mod; }

int dfs(int pos, int S, int limit, int flag) {
	int &res = f[pos][S][limit][flag]; 
	if (res != -1 && limit == 0) return res;
	res = 0;
	if (pos == 0) {
		if (S == 0 && flag == 1) res = 1;
		return res;
	}
	int up = limit ? a[pos] : 9; 
	for (int i = 0; i <= up; ++i) {
		chadd(res, dfs(pos - 1, (S + i * bit[pos - 1] % Mod - i + Mod) % Mod, limit && (i == up), flag ^ (i == 6)));
	}
	return res;
}

int main() {
	bit[0] = 1;
	for (int i = 1; i < 60; ++i) bit[i] = 1ll * bit[i - 1] * 10 % Mod;
	memset(f, -1, sizeof f);
	int _T; cin >> _T;
	while (_T--) {
		scanf("%s", s + 1);
		n = strlen(s + 1);
		reverse(s + 1, s + 1 + n);
		for (int i = 1; i <= n; ++i) a[i] = s[i] - '0';
		printf("%d\n", dfs(n, 0, 1, 0));
	}
	return 0;
}
