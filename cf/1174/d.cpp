#include <bits/stdc++.h>
using namespace std;

#define N 2000010
int n, x, a[N], mp[N];

int main() {
	while (scanf("%d%d", &n, &x) != EOF) {
		int m = 0, pos = 1, limit = (1 << n);   
		memset(mp, 0, sizeof mp);
	   	mp[0] = 1;	
		int sum = 0; 
		while (pos < limit) { 
			if (!mp[pos] && !mp[pos ^ x]) { 
				a[++m] = sum ^ pos;
				sum = pos; 
				mp[sum] = 1;
			}
			++pos;	
		}
		printf("%d\n", m);
		for (int i = 1; i <= m; ++i) {
			printf("%d%c", a[i], " \n"[i == m]);
		}
	}
	return 0;
}
