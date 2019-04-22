#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 310
const ll p = 998244353; 
int n, a[N];
ll f[N * N], g[N * N], all;

int main() {
	while (scanf("%d", &n) != EOF) {
		ll sum = 0, mid;
		all = 1;
		for (int i = 1; i <= n; ++i) {
			scanf("%d", a + i);
			sum += a[i];	
			all = (all * 3) % p; 
		}
		mid = sum / 2;  
		memset(f, 0, sizeof f);  
		f[0] = 1;   
		for (int i = 1; i <= n; ++i) {
			for (int j = sum - a[i]; j >= 0; --j) {
				f[j + a[i]] = (f[j + a[i]] + f[j] * 2 % p) % p;  
			}		 
		}
		
		ll res = 0; 
		for (int i = 0; i <= mid; ++i) {      
			printf("%d %lld\n", i, f[i]);
			res = (res + f[i]) % p;
		}
		if (sum % 2 == 0) {
			memset(g, 0, sizeof g);
			g[0] = 1;
			for (int i = 1; i <= n; ++i) {
				for (int j = sum - a[i]; j >= 0; --j) {
					g[j + a[i]] = (g[j + a[i]] + g[j]) % p;
				}
			}
			res = (res - g[mid] + p) % p;    
		}
		cout << res << endl;
		printf("#%lld %lld\n", f[mid], g[mid]);
		printf("%lld\n", (all - (res * 3) % p + p) % p); 
	}
	return 0;
}
