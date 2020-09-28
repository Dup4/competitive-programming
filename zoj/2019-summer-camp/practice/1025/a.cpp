#include <bits/stdc++.h>
using namespace std;

#define db double
#define N 1000010
const db PI = acos(-1.0);
int n, r[N], d[N];
db f[N];

int main() {
	while (scanf("%d", &n) != EOF) {
		for (int i = 1; i <= n; ++i) {
			scanf("%d", r + i);
		}
		d[1] = 0;
		for (int i = 2; i <= n; ++i) {
			scanf("%d", d + i);
		}
		f[1] = 1; 
		db res = 0;
		for (int i = 1; i < n; ++i) {
			db r1 = r[i], r2 = r[i + 1], dis = d[i + 1] - d[i];
			if (r1 > r2) swap(r1, r2);  
			db d1 = r1 * dis / (r1 + r2);
			db d2 = r1 * dis / (r2 - r1);
			db a1 = acos(r1 / d1);
			db a2 = acos(r1 / d2);
			if (r[i] < r[i + 1]) {
				f[i + 1] = f[i] * (PI - a1 - a2) / (PI * 2); 	
			} else {
				f[i + 1] = f[i] * (fabs(a1 - a2)) / (PI * 2); 
			}
			res += (i - 1) * (f[i] - f[i + 1]);
		}
		res += f[n] * (n - 1);
		printf("%.16f\n", res);
	}
	return 0;
}
