#include <bits/stdc++.h>
using namespace std;

int n, k;

int f(int n, int k, int Max) { 
//	cout << n << " " << k << " " << Max << endl;
	if (k == 1) {
		if (n >= 1 && n <= Max) return 1;
		else return 0;
	} 
	int res = 0;
	for (int i = 1; i <= Max; ++i) {
		res += f(n - i, k - 1, min({Max, i, n - i}));
	}
	return res;
}

int main() {
	scanf("%d%d", &n, &k);
	int res = 0;
	for (int i = 1; i <= k; ++i) res += f(n, i, n); 
	printf("%d\n", res);
	return 0;
}
