#include <bits/stdc++.h>
using namespace std;

const int N = 5e4 + 10;
const int mod = 1e4 + 7;
int n, m, a[N], b[N], len, f[1010][N];  
inline void add(int &x, int y) {
	x += y;
	while (x >= mod) x -= mod;
	while (x < 0) x += mod;
}
bool check(int len) {
	int sum = 0, res = 0;
	for (int i = 1; i <= n; ++i) {
		if (a[i] > len) return 0;
		if (sum + a[i] > len) {
			++res;
			sum = a[i];
		} else sum += a[i];
	}
	return res <= m;
} 

int main() {
	while (scanf("%d%d", &n, &m) != EOF) {
		int tot = 0, Max = 0; b[0] = 0;
		for (int i = 1; i <= n; ++i) scanf("%d", a + i), tot += a[i], b[i] = b[i - 1] + a[i], Max = max(Max, a[i]); 
		int l = Max, r = tot, len = tot;
		while (r - l >= 0) {
			int mid = (l + r) >> 1;
			if (check(mid)) {
				r = mid - 1;
				len = mid;
			} else 
				l = mid + 1;
		}
		memset(f, 0, sizeof f);
		f[0][0] = 1; f[0][1] = 2; f[1][1] = 1; 
		for (int i = 2; i < n; ++i) {
			int l = 0, r = i - 1, pos = i - 1;
			while (r - l >= 0) {
				int mid = (l + r) >> 1;
				if (b[i] - b[pos] <= len) {
					r = mid - 1;
					pos = mid;
				} else 
					l = mid + 1; 
			} 
			for (int j = 1; j <= m; ++j) {
				add(f[j][i], (f[j - 1][i - 1] - f[j - 1][pos] + mod) % mod);
			//	cout << j << " " << i << " " << pos << " " << f[j][i] << endl;
				add(f[j][i], f[j][i - 1]);
			}
			add(f[0][i], f[0][i - 1]);
		}
		int res = 0; 
		for (int i = n - 1; i >= 1; --i) {
			if (b[n] - b[i] > len) {
				for (int j = 0; j <= m; ++j)
					add(res, (f[j][n - 1] - f[j][i] + mod) % mod);
				break;
			}
		}
		printf("%d %d\n", len, res);
	}
	return 0;
}
