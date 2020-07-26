#include <bits/stdc++.h>
using namespace std;
using ll = long long;
constexpr int mod = 1e9 + 7;
constexpr int N = 1e3 + 10;
inline void chadd(int &x, int y) { x += y; if (x >= mod) x -= mod; }
int n, pre[330]; int f[N][N]; char s[N];

int main() {
	scanf("%s", s + 1);
    n = strlen(s + 1);
    memset(f, 0, sizeof f);
    memset(pre, -1, sizeof pre);
	f[0][0] = 1;
    for (int i = 1; i <= n; ++i) {
        int ch = s[i] - 'a';
        for (int j = 0; j < i; ++j) {
            if (pre[ch] == -1) {
                chadd(f[i][j + 1], (f[i - 1][j + 1] + f[i - 1][j]) % mod);
            //  if (j == 0) chadd(f[i][j + 1], 1);
            } else {
                chadd(f[i][j + 1], (1ll * f[i - 1][j + 1] + f[i - 1][j] - f[pre[ch] - 1][j] + mod) % mod);
            }
        }
        f[i][0] = 1;
    //  if (pre[ch] == -1) chadd(f[i][1], 1);
        pre[ch] = i;
    }
	int res = 0;
	for (int i = 1; i <= 100; ++i)
		chadd(res, f[n][i]);
	printf("%d\n", res);
	return 0;
}
