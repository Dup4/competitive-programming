#include <bits/stdc++.h>
using namespace std;

#define ll long long
ll a[110000], b[110];
int main() {
	a[1] = 1; b[1] = 1;
	for (int i = 2; i <= 20000; ++i) {
		a[i] = 0;
		for (int j = 1; j < i; ++j) 
			a[i] += 1ll * a[j] * j;
		a[i] %= i; 
	  //  b[i] = b[i - 1] % i;
		//b[i] *= i;	
	//	printf("%d %lld\n", i, a[i]);	
	}
	for (int i = 2; i <= 20000; i += 2)
		printf("%d %lld\n", i, a[i]);
	for (int i = 1; i <= 20000; i += 2)
		printf("%d %lld\n", i, a[i]);
	return 0;
}
