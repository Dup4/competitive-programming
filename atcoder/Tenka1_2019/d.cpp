#include <bits/stdc++.h>
using namespace std;

#define N 310
const int p = 998244353; 
int n, a[N];
int f[N * N], g[N * N];
int bit2[N], bit3[N];

int main() {
	bit2[0] = 1; bit3[0] = 1;
	for (int i = 1;  i < N; ++i) { 
		bit2[i] = (bit2[i - 1] << 1) % p; 
		bit3[i] = (bit3[i - 1] * 3) % p; 
	}
	while (scanf("%d", &n) != EOF) {
		int sum = 0, mid;
		for (int i = 1; i <= n; ++i) {
			scanf("%d", a + i);
			sum += a[i];	
		}
		mid = sum / 2;  
		memset(f, 0, sizeof f);  
		f[0] = 1;   
		for (int i = 1; i <= n; ++i) {
			for (int j = sum - a[i]; j >= 0; --j) {
				f[j + a[i]] = (f[j + a[i]] + f[j] * 2 % p) % p;  
			}		 
		}
		
		int res = 0; 
		for (int i = 0; i <= mid; ++i) {      
			res = (res + f[i]) % p;
		}
		if (sum % 2 == 0) {
			g[0] = 1;
			for (int i = 1; i <= n; ++i) {
				for (int j = sum - a[i]; j >= 0; --j) {
					g[j + a[i]] = (g[j + a[i]] + g[j]) % p;
				}
			}
			res = (res - g[mid] + p) % p;    
		}
		printf("%d\n", (bit3[n] - (res * 3) % p + p) % p); 
	}
	return 0;
}
