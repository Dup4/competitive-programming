#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int N = 1100;
int n, m, a[N], b[N], f[32][N];

int main() {
	while (scanf("%d%d", &n, &m) != EOF) {
		a[0] = -1e6; b[0] = 0;
		for (int i = 1; i <= n; ++i) scanf("%d", a + i), b[i] = b[i - 1] + a[i];  
		memset(f, 0x3f, sizeof f);
		f[0][0] = 0; 
		for (int j = 1; j <= m; ++j) {
			for (int k = 1; k <= n; ++k) {
				if (j == 1) {
					int sum = 0;
					for (int l = 1; l <= k; ++l) sum += a[k] - a[l];
					f[j][k] = sum;
				} else {
					for (int l = 1; l < k; ++l) {
						if (l == k - 1) {
							f[j][k] = min(f[j][k], f[j - 1][l]);
							continue;
						}
						int ql = l + 1, qr = k - 1, pos = l + 1;
						while (qr - ql >= 0) {
							int mid = (ql + qr) >> 1;
							int delta = (a[mid] - a[l]) - (a[k] - a[mid]);
							if (delta <= 0) {
								ql = mid + 1;
								pos = mid;
							} else {
								qr = mid - 1;
							}
						}
						int sum = 0;
						if (pos != -1) {
							sum += b[pos] - b[l] - a[l] * (pos - l);
							sum += a[k] * (k - pos) - (b[k] - b[pos]);	
						} 
						f[j][k] = min(f[j][k], f[j - 1][l] + sum);
					}
				}
			}
		} 
		int res = 0x3f3f3f3f;
		for (int i = 1; i <= n; ++i) {
			int sum = 0;
			for (int j = i + 1; j <= n; ++j) {
				sum += a[j] - a[i];
			}
			res = min(res, f[m][i] + sum);
		}
		printf("%d\n", res);
	}
	return 0;
}
