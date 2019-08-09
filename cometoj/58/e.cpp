#include <bits/stdc++.h>
using namespace std;

int d(int x) {
	for (int i = 2; i <= x; ++i) {
		if (x % i == 0)
			return i;
	}
	return -1;
}
int f[11000];

int main() {
	f[1] = 1;
	for (int i = 2; i <= 10000; ++i) {
		int D = d(i);
		if (i % (D * D) == 0)
			f[i] = D * f[i / D / D];
		else 
			f[i] = f[i / D];
	}
	for (int i = 1; i <= 100; ++i)
		printf("%d %d\n", i, f[i]);
	for (int i = 1; i <= 100; ++i)
		for (int j = 1; j <= 100; ++j)
			if (__gcd(i, j) == 1)
		//		printf("%d %d %d %d\n", i, j, f[i] * f[j], f[i * j]);
	return 0;
}
